#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mtx.h"

int timecheck(void)
{
	int dst;
	clock_t clk;
	size_t *route;
	
	antp_t param = {100, 30, 0.3, 1.5, 1.5};
	
	for (size_t size = 3; size <= 11; size++)
	{
		mtx_t *mtx = create_mtx(size, size);
		if (!mtx)
		{
			printf("Alloc mtx(%zu, %zu) error.. \n", size, size);
			return EXIT_FAILURE;
		}
		
		rand_symmetric_fill(mtx);
		
		printf("size: %zu ", size);
		
		clk = clock();
		for (size_t t = 0; t < REP; t++)
		{
			dst = commis_voyageur_bf(mtx, &route);
			if (dst >= 0)
				free(route);
		}
		clk = clock() - clk;
		printf("bf: %ld ", clk);
		
		clk = clock();
		for (size_t t = 0; t < REP; t++)
		{
			dst = commis_voyageur_ant(mtx, &route, &param);
			if (dst >= 0)
				free(route);
		}
		clk = clock() - clk;
		printf("ant: %ld\n", clk);
		
		destroy_mtx(mtx);
	}
	return EXIT_SUCCESS;
}

int autocheck(void)
{
	size_t n = 10;
	size_t *route;
	int bf_dst, bf_dst1, bf_dst2;
	mtx_t *mtx = create_mtx(n, n), *mtx1 = create_mtx(n, n), *mtx2 = create_mtx(n, n);
	if (!mtx || ! mtx1 || !mtx2)
	{
		printf("Alloc mtx error.. \n");
		destroy_mtx(mtx);
		destroy_mtx(mtx1);
		destroy_mtx(mtx2);
		return EXIT_FAILURE;
	}
	
	rand_symmetric_fill(mtx);
	rand_symmetric_fill(mtx1);
	rand_symmetric_fill(mtx2);
	int dst = commis_voyageur_bf(mtx, &route);
	free(route);
	int dst1 = commis_voyageur_bf(mtx1, &route);
	free(route);
	int dst2 = commis_voyageur_bf(mtx2, &route);
	free(route);
	printf("Bf: ");

	printf("dst: %d\n", dst);
	printf("dst1: %d\n", dst1);
	printf("dst2: %d\n", dst2);

	bf_dst = dst;
	bf_dst1 = dst1;
	bf_dst2 = dst2;
	
	antp_t param;
	
	param.Q = 200;
	
	for (float a = 0.0; a < 6.001; a += 0.4)
	{
		param.ALPHA = a;
		param.BETA = 6.0 - a;
		for (size_t t = 10; t <= 200; t += 60)
		{
			param.ANT_TIME = t;
			for (float p = 0.1; p < 1.0; p += 0.25)
			{
				param.RO = p;
				
				printf("%.1f & %zu & %.1f ", a, t, p);
				dst = commis_voyageur_ant(mtx, &route, &param);
				if (dst >= 0)
				{
					printf("& %d ", dst - bf_dst);
					free(route);
				}
				else
					printf("Can't find route.\n");
				
				dst1 = commis_voyageur_ant(mtx1, &route, &param);
				if (dst1 >= 0)
				{
					printf("& %d ", dst1 - bf_dst1);
					free(route);
				}
				else
					printf("Can't find route.\n");
				
				dst2 = commis_voyageur_ant(mtx2, &route, &param);
				if (dst2 >= 0)
				{
					printf("& %d \\\\\n", dst2 - bf_dst2);
					free(route);
				}
				else
					printf("Can't find route.\n");
			}
		}
	}
	
	destroy_mtx(mtx);
	destroy_mtx(mtx1);
	destroy_mtx(mtx2);
	
	return EXIT_SUCCESS;
}

int manual(void)
{
	int dst;
	size_t n;
	size_t *route;
	
	antp_t param = {100, 10, 0.1, 0.5, 0.5};
	
	if (scanf("%zu", &n) != 1)
	{
		printf("Read error.. \n");
		return EXIT_FAILURE;
	}
	
	mtx_t *mtx = create_mtx(n, n);
	if (!mtx)
	{
		printf("Alloc mtx error.. \n");
		return EXIT_FAILURE;
	}
	
	if (fscanf_mtx(stdin, mtx) != EXIT_SUCCESS)
	{
		destroy_mtx(mtx);
		printf("Read error.. \n");
		return EXIT_FAILURE;
	}
	
	dst = commis_voyageur_bf(mtx, &route);
	printf("Bf:\n");
	if (dst >= 0)
	{
		printf("Found min route:\n");
		for (size_t i = 0; i < n; i++)
			printf("%zu ", route[i]);
		printf("\nDst:\n%d\n", dst);
		
		free(route);
	}
	else
		printf("Can't find route.\n");
	
	dst = commis_voyageur_ant(mtx, &route, &param);
	printf("Ant:\n");
	if (dst >= 0)
	{
		printf("Found min route:\n");
		for (size_t i = 0; i < n; i++)
			printf("%zu ", route[i]);
		printf("\nDst:\n%d\n", dst);
		
		free(route);
	}
	else
		printf("Can't find route.\n");
	
	destroy_mtx(mtx);
	
	return EXIT_SUCCESS;
}

int main(void)
{
	setbuf(stdout, NULL);
	
	int man;
	
	printf("Commis voyageur. manual/correctness/time? (0/1/2)): ");
	if (scanf("%d", &man) != 1)
	{
		printf("Bad input..\n");
		return EXIT_FAILURE;
	}
	
	if (man == 0)
		return manual();
	else if (man == 1)
		return autocheck();
	else if (man == 2)
		return timecheck();
	else
	{
		printf("Unknown mode.\n");
		return EXIT_FAILURE;
	}
}