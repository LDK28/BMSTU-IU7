#include "mtx.h"

mtx_t* create_mtx(size_t n, size_t m)
{
	mtx_t *mtx = calloc(1, sizeof(mtx_t));
	if (!mtx)
		return NULL;
	
	mtx->data = calloc(n, sizeof(int *));
	if (mtx->data)
	{
		for (size_t i = 0; i < n; i++)
		{
			mtx->data[i] = malloc(m * sizeof(int));
			if (!mtx->data[i])
			{
				destroy_mtx(mtx);
				return NULL;
			}
		}
	}
	else
		return NULL;
	
	mtx->n = n, mtx->m = m;
	return mtx;
}

void destroy_mtx(mtx_t *mtx)
{
	if (mtx)
	{
		if (mtx->data)
		{
			for (size_t i = 0; i < mtx->n; i++)
				free(mtx->data[i]);
			free(mtx->data);
		}
		free(mtx);
	}
}

mtxf_t* create_mtxf(size_t n, size_t m)
{
	mtxf_t *mtx = calloc(1, sizeof(mtxf_t));
	if (!mtx)
		return NULL;
	
	mtx->data = calloc(n, sizeof(float *));
	if (mtx->data)
	{
		for (size_t i = 0; i < n; i++)
		{
			mtx->data[i] = malloc(m * sizeof(float));
			if (!mtx->data[i])
			{
				destroy_mtxf(mtx);
				return NULL;
			}
		}
	}
	else
		return NULL;
	
	mtx->n = n, mtx->m = m;
	return mtx;
}

void destroy_mtxf(mtxf_t *mtx)
{
	if (mtx)
	{
		if (mtx->data)
		{
			for (size_t i = 0; i < mtx->n; i++)
				free(mtx->data[i]);
			free(mtx->data);
		}
		free(mtx);
	}
}

void fprintf_mtx(FILE *file, mtx_t *mtx)
{
	for (size_t i = 0; i < mtx->n; i++)
	{
		for (size_t j = 0; j < mtx->m; j++)
			fprintf(file, "%d ", mtx->data[i][j]);
		
		fprintf(file, "\n");
	}
}

int fscanf_mtx(FILE *file, mtx_t *mtx)
{
	for (size_t i = 0; i < mtx->n; i++)
		for (size_t j = 0; j < mtx->m; j++)
		{
			if (fscanf(file, "%d", mtx->data[i] + j) != 1)
				return EXIT_FAILURE;
		}
			
	return EXIT_SUCCESS;
}

inline static void swp(size_t *a, size_t *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

size_t factorial(size_t n)
{
	if (n < 2)
		return 1;

	size_t res = 1;
	do res *= n; while(--n);
		
	return res;
}

int nperm(size_t *seq, size_t n)
{
	size_t i = n;
	do {
		if (i < 2)
			return EXIT_FAILURE; 
		i--;
	} while (seq[i - 1] > seq[i]);
	
	size_t j;
	for (j = n; j > i && seq[i - 1] > seq[--j];) {}
		
	swp(seq + i - 1, seq + j);
	
	for (j = n; i < --j; i++)
		swp(seq + i, seq + j);
	
	return EXIT_SUCCESS;
}

int cnt_dist(mtx_t *mtx, size_t *route)
{
	int dst = 0, td;
	
	for (size_t i = 0; i < mtx->n - 1; i++)
	{
		td = mtx->data[route[i]][route[i + 1]];
		if (td < 0)
			return -1;
		
		dst += td;
	}
	
	td = mtx->data[0][mtx->n - 1];
	if (td < 0)
		return -1;
	
	dst += td;
	
	return dst;
}

int commis_voyageur_bf(mtx_t *mtx, size_t **route)
{
	*route = malloc(mtx->n * sizeof(size_t));
	size_t *tr = malloc(mtx->n * sizeof(size_t));
	
	for (size_t i = 0; i < mtx->n; i++)
		tr[i] = i;
	
	bool found = false;
	int dst, m;
	
	do {
		dst = cnt_dist(mtx, tr);
		
		if (dst >= 0 && (!found || dst < m))
		{
			found = true;
			m = dst;
			memcpy(*route, tr, mtx->n * sizeof(mtx->n));
		}
	} while (nperm(tr, mtx->n) == EXIT_SUCCESS);
	
	free(tr);
	
	if (!found)
	{
		free(*route);
		return -1;
	}
	
	return m;
}


int commis_voyageur_ant(mtx_t *mtx, size_t **route, antp_t *param)
{
	mtxf_t *dist = create_mtxf(mtx->n, mtx->m);
	mtxf_t *fero = create_mtxf(mtx->n, mtx->m);
	
	ant_t *colony = malloc(mtx->n * sizeof(ant_t));
	float *p = malloc((mtx->n - 1) * sizeof(float));
	*route = malloc(mtx->n * sizeof(size_t));
	
	int L = 0;
	
	for (size_t i = 0; i < mtx->n; i++)
	{
		for (size_t j = 0; j < mtx->m; j++)
		{
			dist->data[i][j] = 1.0 / (float)mtx->data[i][j];
			
			if (mtx->data[i][j] > 0)
			{
				fero->data[i][j] = 1.0;
				L += mtx->data[i][j];
			}
			else
				fero->data[i][j] = 0.0;
		}
		
		colony[i].unvis = malloc((mtx->n - 1) * sizeof(size_t));
		colony[i].route = malloc(mtx->n * sizeof(size_t));
	}
	
	L /= 2;
	
	//start alg
	
	bool found = false;
	
	for (size_t i = 0; i < param->ANT_TIME; i++)
	{
		for (size_t ant = 0; ant < mtx->n; ant++)
		{
			colony[ant].route[0] = colony[ant].cur = ant;
			size_t c = 1;
			for (size_t j = 0; j < mtx->n; j++, c++)
			{
				if (ant == j)
					c--;
				else
					colony[ant].unvis[c - 1] = j;
			}
			
			colony[ant].unv_len = mtx->n - 1;
			size_t route_cnt = 1;
			
			while (colony[ant].unv_len)
			{
				float s = 0.0;
				for (size_t q = 0; q < colony[ant].unv_len; q++)
				{
					size_t ai = colony[ant].cur, aj = colony[ant].unvis[q];
					p[q] = powf(fero->data[ai][aj], param->ALPHA) + powf(dist->data[ai][aj], param->BETA);
					s += p[q];
				}
				float r = (float)rand() / (float)RAND_MAX;
				p[0] /= s;
				for (size_t q = 1; q < colony[ant].unv_len; q++)
				{
					p[q] /= s;
					p[q] += p[q - 1];
				}
				
				size_t q = 0;
				bool select = false;
				while (q < colony[ant].unv_len && !select)
				{
					if (r < p[q])
						select = true;
					q++;
				}

				colony[ant].route[route_cnt] = colony[ant].cur = colony[ant].unvis[q - 1];
				route_cnt++;
				
				
				size_t k;
				for (k = 0; k < colony[ant].unv_len; k++)
					if (k == q - 1)
						break;
				
				for (size_t e = k; e < colony[ant].unv_len - 1; e++)
					colony[ant].unvis[e] = colony[ant].unvis[e + 1]; 
				
				colony[ant].unv_len--;
			}
			
			int dst = cnt_dist(mtx, colony[ant].route);
			if (dst >= 0 && (!found || dst < L))
			{
				found = true;
				L = dst;
				memcpy(*route, colony[ant].route, mtx->n * sizeof(size_t));
			}
			
			colony[ant].dst = dst;
		}
		
		for (size_t i = 0; i < mtx->n; i++)
			for (size_t j = 0; j < mtx->m; j++)
				if (fero->data[i][j] > 0)
				{
					fero->data[i][j] *= 1.0 - param->RO;
					if (fero->data[i][j] < 0.1)
						fero->data[i][j] = 0.1;
				}
		
		int from, to;
		for (size_t ant = 0; ant < mtx->n; ant++)
		{
			for (size_t r = 0; r < mtx->n - 1; r++)
			{
				from = colony[ant].route[r];
				to = colony[ant].route[r + 1];
				
				fero->data[from][to] += param->Q / colony[ant].dst;
			}		

			fero->data[mtx->n - 1][0] += param->Q / colony[ant].dst;
		}
	}
	
	destroy_mtxf(dist);
	destroy_mtxf(fero);
	for (size_t i = 0; i < mtx->n; i++)
	{
		free(colony[i].unvis);
		free(colony[i].route);
	}
	free(colony);
	free(p);
	
	if (!found)
		return -1;
	
	return L;
}

void rand_symmetric_fill(mtx_t *mtx)
{
	for (size_t i = 0; i < mtx->n; i++)
		for (size_t j = i; j < mtx->m; j++)
			mtx->data[j][i] = mtx->data[i][j] = rand() % 100 + 1;
	
	for (size_t i = 0; i < mtx->n; i++)
		mtx->data[i][i] = 0;
}

