
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <time.h>



// Обычная реализация
__global__ void matmulsimp(int* M, int* N, int* P, int width) {
	for (int row = 0; row < width; row++) {
		for (int col = 0; col < width; col++) {
			// Multiply the row of A by the column of B to get the row, column of product.
			for (int inner = 0; inner < width; inner++)
				P[row * width + col] += M[row * width + inner] * N[inner * width + col];
		}
	}
}


// Параллельная
__global__ void MatMul(int* M, int* N, int* P, int width)
{
	int x = threadIdx.x;
	int y = threadIdx.y;

	float Pervalue = 0;

	float elem1 = 0.0, elem2 = 0.0, value = 0.0;
	for (int i = 0; i < width; i++)
	{
		elem1 = M[y * width + i]; // Возьмем одну строку матрицы M
		elem2 = N[i * width + x]; // Берем один столбец из N матрицы

		value += elem1 * elem2; // Сумма
	}

	P[y * width + x] = value;
}

int main()
{
	const int ND = 100;
	int a[ND][ND], b[ND][ND], c[ND][ND];
	int *M, *N, *P;

	int width = ND;
	dim3 blockSize(ND, ND);

	cudaEvent_t start, stop;
	float elapsedTime = 0;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// Распределение памяти устройства
	cudaMalloc((void**)&M, ND * ND * sizeof(int));
	cudaMalloc((void**)&N, ND * ND * sizeof(int));
	cudaMalloc((void**)&P, ND * ND * sizeof(int));

	// Инициализация
	for (int i = 0; i < ND; i++)
	{
		for (int j = 0; j < ND; j++)
		{
			a[i][j] = 2;
			b[i][j] = 3;
		}
	}

	int Size = ND * ND;
	// Копирование данных с хоста на устройство
	cudaMemcpy(M, a, Size * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(N, b, Size * sizeof(int), cudaMemcpyHostToDevice);

	cudaEventRecord(start, 0);
	MatMul <<< 1, blockSize >>> (M, N, P, width); // Вызов функции ядра
	cudaThreadSynchronize();
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);

	cudaMemcpy(c, P, Size * sizeof(int), cudaMemcpyDeviceToHost);

	printf("c0 = %f \n", elapsedTime);

	cudaEventRecord(start, 0);
	matmulsimp <<<1, 1>>>(M, N, P, ND);
	cudaThreadSynchronize();
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);


	printf("c0 = %f \n", elapsedTime);

	// Освободить память устройства
	cudaFree(M);
	cudaFree(N);
	cudaFree(P);

	return 0;
}