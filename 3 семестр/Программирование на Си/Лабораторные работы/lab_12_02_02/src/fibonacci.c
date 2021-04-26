#include "../inc/fibonacci.h"

int element(int i)
{
	int fib;

	if (i == 0)
		fib = 0;
	if (i == 1)
		fib = 1;
	if (i > 1)
		fib = element(i - 2) + element(i - 1);

	return fib;
}

void fibonacci(int *a, int n)
{
	for (int i = 0; i < n; i++)
		a[i] = element(i);
}

int arr_filter(int *a, int n, int *b)
{
	int flag;
	int k = 1;

	b[0] = a[0];
	for (int i = 1; i < n; i++)
	{
		flag = 0;
		for (int j = 0; j < n; j++)
			if (b[j] == a[i])
				flag = 1;
		if (!flag)
			b[k] = a[i];
		k += 1;
	}

	return k;
}
