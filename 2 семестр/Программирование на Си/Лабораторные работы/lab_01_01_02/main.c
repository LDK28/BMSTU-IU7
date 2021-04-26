#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	double a, b, c;
	double s;
	const double pi = acos(-1);
	const double ep = 1e-8;
	
	if (scanf("%lf", &a) != 1)
		return EXIT_FAILURE;
	
	if (scanf("%lf", &b) != 1)
		return EXIT_FAILURE;
	
	if (scanf("%lf", &c) != 1)
		return EXIT_FAILURE;
	
	if (c >= 180.0 + ep)
		return EXIT_FAILURE;
	if (fabs(c - 90.0) < ep)
		return EXIT_FAILURE;
	
	if ((c > 90.0 + ep) & (a > b))
	{
		double t = a;
		a = b;
		b = t;
	}
	
	if ((c < 90.0 - ep) & (a < b))
	{
		double t = b;
		b = a;
		a = t;
	}
	
	s = (a * a - b * b) * tan(c * pi / 180.0) * 0.25;
	printf("%.5lf", s);
	
	return EXIT_SUCCESS;
}
