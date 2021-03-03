#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(void)
{
	static int M;
	int *array = NULL;
	int sumOneThread;
	//int sumParallel[4];
	double dst[50];

	long sumParallel = 0;

	printf("Enter capacity of array: ");
	scanf_s("%d", &M);

	array = malloc(M * sizeof(int));

	
	srand(2);
	int randNum = 0;
	for (int i = 0; i < M; i++)
	{
		randNum = rand() % 100;
		printf("%d\n", randNum);
		array[i] = randNum;
	}
	
	//clock_t tic = clock();
	double click1 = omp_get_wtime();
	sumOneThread = sum(array, M);
	double clack1 = omp_get_wtime();
	printf("Time of sum singlethread computation = %f\n", clack1 - click1);
	//clock_t toc = clock();
	//printf("Result of sum in one thread function = %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	printf("Result of sum in one thread function = %d\n", sumOneThread);
	double click = omp_get_wtime();
#pragma omp parallel
	{
		int lsum = 0;
		int i;
#pragma omp for
		for (i = 0; i < M; i++)
		{
			lsum += array[i];
		}
#pragma omp atomic
		sumParallel += lsum;

	}
	double clack = omp_get_wtime();


	printf("Result of sum multithread computation = %d\n", sumParallel);

	printf("Time of sum multithread computation = %f\n", clack-click);





















	
	


}

int sum(int array[], int capacity) {
	int sum = 0;
	for (int i = 0; i < capacity; i++)
	{
		sum += array[i];
	}
	return sum;
}