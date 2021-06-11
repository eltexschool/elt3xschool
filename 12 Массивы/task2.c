#include <stdio.h>

#define N 5

int main() {

	int array[N];

	for(int i = 0; i < N; i++)
		array[i] = i+1;

	for(int i = N-1; i >= 0; i--)
		printf("%d%c", array[i], (i != 0) ? '\t' : '\n');

	return 0;
}