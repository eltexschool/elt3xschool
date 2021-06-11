#include <stdio.h>

#define N 3

int main() {

	char s[N];
	s[0] = 1;
	while(s[0]) {
		printf("> ");
		fgets(s, N, stdin);
		for(int i = 0; i < N; i++)
			printf("%d%c", s[i], (i < (N-1)) ? '\t' : '\n');
		s[0] -= '0';
		for(int i = 0; i < N; i++)
			printf("%d%c", s[i], (i < (N-1)) ? '\t' : '\n');
		/*if(s[0]) {
			printf("Oooops!\n");
			break;
		}*/
	}


	return 0;
}