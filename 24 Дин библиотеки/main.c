#include <stdio.h>
#include "mycalc.h"

#define N 2

typedef int (*poperation) (const int num1, const int num2);
typedef enum enum_menu {ADD = 1, SUBTRACT, MULTIPLY, DIVIDE, QUIT} menu;

void clean_buf();

int main()
{
	unsigned menu_choice = QUIT;
	do {
		printf("Enter the number: add(1), subtract(2), multiply(3), divide(4), quit(5)> ");
		scanf("%u", &menu_choice);
		clean_buf();
		if((menu_choice >= ADD) && (menu_choice <= DIVIDE)) {
            char *messages[N] = {"Enter a 1st number> ", "Enter a 2nd number> "};
            int nums[N] = {0};
            for(int i = 0; i < N; i++) {
                printf("%s", messages[i]);
                scanf("%d", &nums[i]);
                clean_buf();
            }
            poperation actions[] = {add, subtract, multiply, divide};
            printf("The result: %d\n", actions[menu_choice-1](nums[0], nums[1]));
		}
	} while((menu_choice > 0) && (menu_choice < QUIT));

	return 0;
}

void clean_buf()
{
	while(getchar() != '\n');
}
