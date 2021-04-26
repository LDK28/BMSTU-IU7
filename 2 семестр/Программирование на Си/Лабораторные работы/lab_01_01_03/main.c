#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	double v1, v2;
	double t1, t2;
	double v, t;
	
	if ((scanf("%lf", &v1) != 1) || (v1 < 0.0))
		return EXIT_FAILURE;
	
	if (scanf("%lf", &t1) != 1)
		return EXIT_FAILURE;
	
	if ((scanf("%lf", &v2) != 1) || (v2 < 0.0))
		return EXIT_FAILURE;
	
	if (scanf("%lf", &t2) != 1)
		return EXIT_FAILURE;
	
	v = v1 + v2;
	t = (v1 * t1 + v2 * t2) / (v1 + v2);
	
	printf("%.5lf\n%.5lf", v, t);
	return EXIT_SUCCESS;
}
