#ifndef MTX_H
#define MTX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define REP 10

typedef struct 
{
	size_t ANT_TIME, Q;
	float RO, ALPHA, BETA;
} antp_t;

typedef struct 
{
	size_t m, n;
	int **data;
} mtx_t;

typedef struct 
{
	size_t m, n;
	float **data;
} mtxf_t;

mtx_t* create_mtx(size_t n, size_t m);
mtxf_t* create_mtxf(size_t n, size_t m);

void destroy_mtx(mtx_t *mtx);
void destroy_mtxf(mtxf_t *mtx);

void fprintf_mtx(FILE *file, mtx_t *mtx);
int fscanf_mtx(FILE *file, mtx_t *mtx);

void rand_symmetric_fill(mtx_t *mtx);

typedef struct 
{
	size_t cur, unv_len, dst;
	size_t *unvis, *route;
	
} ant_t;

size_t factorial(size_t n);
int nperm(size_t *seq, size_t n);

int commis_voyageur_bf(mtx_t *mtx, size_t **route);
int commis_voyageur_ant(mtx_t *mtx, size_t **route, antp_t *param);

#endif