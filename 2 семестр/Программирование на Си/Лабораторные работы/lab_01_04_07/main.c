#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x, double eps)
{
	double s = 0.0, a = 1.0;
	long k = 2;
	s += a;
	a *= (-1.0) * k * (k + 1) * x / 2;
	while (fabs(a) > eps)
	{
		s += a;
		k += 1;
		a *= -(k + 1) * x / (k - 1);
	}
	return s;
}

int main(void)
{
	double x, eps;
	double inaccuracy_1, inaccuracy_2;
	if (scanf("%lf", &x) != 1)
		return EXIT_FAILURE;
	if (scanf("%lf", &eps) != 1)
		return EXIT_FAILURE;
	
	if (fabs(x) >= 1)
		return EXIT_FAILURE;
	if (eps <= 0)
		return EXIT_FAILURE;
	if (eps >= 1)
		return EXIT_FAILURE;
	
	double s, f;
	s = func(x, eps);
	f = 1.0 / ((1.0 + x) * (1.0 + x) * (1.0 + x));
	
	inaccuracy_1 = fabs(f - s);
	inaccuracy_2 = fabs((f - s) / f);
	
	printf("%.6lf\n", s);
	printf("%.6lf\n", f);
	printf("%.6lf\n", inaccuracy_1);
	printf("%.6lf", inaccuracy_2);
	
	return EXIT_SUCCESS;
}
