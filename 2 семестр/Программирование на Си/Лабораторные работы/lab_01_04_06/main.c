#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	double x1, y1, x2, y2;
	double xa, ya;
	const double ep = 1e-8;
	
	if (scanf("%lf", &x1) != 1)
		return EXIT_FAILURE;
	if (scanf("%lf", &y1) != 1)
		return EXIT_FAILURE;
	
	if (scanf("%lf", &x2) != 1)
		return EXIT_FAILURE;
	if (scanf("%lf", &y2) != 1)
		return EXIT_FAILURE;
	
	if ((fabs(x2 - x1) < ep) && (fabs(y2 - y1) < ep))
		return EXIT_FAILURE;
	
	if (scanf("%lf", &xa) != 1)
		return EXIT_FAILURE;
	if (scanf("%lf", &ya) != 1)
		return EXIT_FAILURE;
	
	if (fabs(((xa - x1) * (y2 - y1)) - ((ya - y1) * (x2 - x1))) < ep)
	{
		if (((x1 < x2) && (xa < x1 || xa > x2)) || ((x1 > x2) && (xa > x1 || xa < x2)))
		{
			printf("0");
			return EXIT_SUCCESS;
		}
		if (((y1 < y2) && (ya < y1 || ya > y2)) || ((y1 > y2) && (ya > y1 || ya < y2)))
		{
			printf("0");
			return EXIT_SUCCESS;
		}
		printf("1");
	}
	else
		printf("0");
	
	return EXIT_SUCCESS;
}
