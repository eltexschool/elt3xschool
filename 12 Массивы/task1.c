#include <stdio.h>

#define N 3

int main() {
	
	int matrix[N][N];
	int value = 1;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			matrix[i][j] = value;
			printf("%d%c", matrix[i][j], (j != (N-1)) ? '\t' : '\n');
			value++;
		}
	}

	return 0;
}