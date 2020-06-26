#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

const int NUM_THREADS = 8;

int main() {
	int matrix = 150; //Se aumento ulteriormente mi sfora crashando
	long double A[matrix][matrix], B[matrix][matrix], C[matrix][matrix];
	long double scalarProduct[matrix][matrix];
	long double startTime = omp_get_wtime();
	#pragma omp parallel 
	{
		#pragma omp for schedule(dynamic, 1)
		for (int i = 0; i < matrix; i++) {
			for (int j = 0; j < matrix; j++) {
				A[i][j] = (pow(i, 2) * pow(j, 3) + 0.0001) / 5;
				B[i][j] = ((pow(j, 2) * pow(i, 3)) / 3) * 5;
				C[i][j] = A[i][j] + B[i][j];
			}
		}
	}
	#pragma omp critical
		for (int i = 0; i < matrix; i++)
			for (int j = 0; j < matrix; j++)
				scalarProduct[i][j] = C[i][j] * B[i][j];
		
	long double stopTime = omp_get_wtime();
	cout << " Tempo impiegato: " << (stopTime - startTime) * 1000 << " millisecondi." << endl;
}