#include <stdio.h>

int main() {

	int a = 270533154;
	char* ptr;

	ptr  = (char*)&a;

	printf("%x\n", a);

	for(int i = 0; i < sizeof(a); i++) {
		printf("%x%c", *ptr, (i < sizeof(a)-1) ? '\t' : '\n');
		ptr++;
	}

	return 0;
}