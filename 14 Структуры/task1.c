#include <stdio.h>

#define N 2

struct Test {
	char a;
	int b;
}__attribute__((packed));

int main() {

	struct Test test;

	char str[10] = {'A', 0, 0, 0, 0, 'B', 0, 0, 0, 0};

	struct Test* ptr = (struct Test*)str;

	for(int i = 0; i < N; i++) {
		printf("%c\t%d\n", ptr->a, ptr->b);
		ptr++;
	}

	return 0;
}