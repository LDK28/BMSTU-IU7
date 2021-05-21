#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define ITERATIONS 100000000

double add_float_time(float a, float b)
{
  float c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
    c = a + b;

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double add_double_time(double a, double b)
{
  double c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
    c = a + b;

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double add_ldouble_time(long double a, long double b)
{
  double c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
    c = a + b;

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double add_asm_float_time(float a, float b)
{
  float c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
  {
    asm("FLDS %1\n"
        "FLDS %2\n"
        "FADDP\n"
        "FSTPS %0\n"
        : "=m" (c)
        : "m" (a), "m" (b)
    );
  }

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double add_asm_double_time(double a, double b)
{
  double c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
  {
    asm("FLDL %1\n"
        "FLDL %2\n"
        "FADDP\n"
        "FSTPL %0\n"
        : "=m" (c)
        : "m" (a), "m" (b)
    );
  }

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double add_asm_ldouble_time(long double a, long double b)
{
  long double c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
  {
    asm("FLDT %1\n"
        "FLDT %2\n"
        "FADDP\n"
        "FSTPT %0\n"
        : "=m" (c)
        : "m" (a), "m" (b)
    );
  }

  time_t stop = clock();

  return (double)(stop - start)/ CLOCKS_PER_SEC;
}

double mul_float_time(float a, float b)
{
  float c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
    c = a * b;

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double mul_double_time(double a, double b)
{
  double c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
    c = a * b;

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double mul_ldouble_time(long double a, long double b)
{
  double c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
    c = a * b;

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double mul_asm_float_time(float a, float b)
{
  float c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
  {
    asm("FLDS %1\n\t"
        "FLDS %2\n\t"
        "FMULP\n\t"
        "FSTPS %0\n\t"
        : "=m" (c)
        : "m" (a), "m" (b)
    );
  }

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double mul_asm_double_time( double a, double b)
{
  double c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
  {
    asm("FLDL %1\n\t"
        "FLDL %2\n\t"
        "FMULP\n\t"
        "FSTPL %0\n\t"
        : "=m" (c)
        : "m" (a), "m" (b)
    );
  }

  time_t stop = clock();

  return (double)(stop - start) / CLOCKS_PER_SEC;
}

double mul_asm_ldouble_time(long double a, long double b)
{
  long double c;

  time_t start = clock();

  for (int i = 0; i < ITERATIONS; i++)
  {
    asm("FLDT %1\n\t"
        "FLDT %2\n\t"
        "FMULP\n\t"
        "FSTPT %0\n\t"
        : "=m" (c)
        : "m" (a), "m" (b)
    );
  }

  time_t stop = clock();

  return (double)(stop - start)/ CLOCKS_PER_SEC;
}
double loaded_pi()
{
    double pi;
    asm("FLDPI\n"
        "FSTPL %0\n"
    : "=m" (pi)
    );
    return pi;
}
int main()
{
  float a, b;
  double ad, bd;
  long double ald, bld;
  ad = ald = a = (double)rand() / RAND_MAX + 1;
  bd = bld = b = (double)rand() / RAND_MAX + 1;

  printf("x---------------x--------------- x----------------x----------------x\n");
  printf("|     ADD       |     float      |     double     |  long double   |\n");
  printf("x---------------x----------------x----------------x----------------x\n");
  printf("|      C        |");
  printf("%16lf|%16lf|%16lf|\n", add_float_time(a, b), add_double_time(ad, bd), add_ldouble_time(ald, bld));
  printf("x----------------x---------------x----------------x----------------x\n");
  printf("|     asm       |");
  printf("%16lf|%16lf|%16lf|\n", add_asm_float_time(a, b), add_asm_double_time(ad, bd), add_asm_ldouble_time(ald, bld));
  printf("x----------------x---------------x----------------x----------------x\n\n");

  printf("x---------------x--------------- x----------------x----------------x\n");
  printf("|      MUL      |     float      |     double     |  long double   |\n");
  printf("x---------------x----------------x----------------x----------------x\n");
  printf("|      C        |");
  printf("%16lf|%16lf|%16lf|\n", mul_float_time(a, b), mul_double_time(ad, bd), mul_ldouble_time(ald, bld));
  printf("x----------------x---------------x----------------x----------------x\n");
  printf("|     asm       |");
  printf("%16lf|%16lf|%16lf|\n", mul_asm_float_time(a, b), mul_asm_double_time(ad, bd), mul_asm_ldouble_time(ald, bld));
  printf("x----------------x---------------x----------------x----------------x\n\n");

  printf("\n3.14: sin(pi) = %lf\n3.141596: sin(pi) = %lf\nloaded: sin(pi) = %lf\n", sin(3.14), sin(3.141596), sin(loaded_pi()));
}