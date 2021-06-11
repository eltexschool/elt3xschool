#include <stdio.h>

#define N 3

int main() {

	int matrix[N][N];
	int checkColumn = N-1;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			matrix[i][j] = (j >= checkColumn) ? 1 : 0;
			printf("%d%c", matrix[i][j], (j < N-1) ? '\t' : '\n');
		}
		checkColumn--;
	}

	return 0;
}