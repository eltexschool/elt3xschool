#include <stdio.h>

#define N 5

int main() {

	int matrix[N][N];
	typedef enum {TOP, RIGHT, BOTTOM, LEFT} Direction;
	Direction dir = TOP;
	int top = 0, right = N-1, bottom = N-1, left = 0;
	int r = 0, c = 0;

	for(int i = 0; i < N*N; i++) {
		switch(dir) {
			case TOP:
				matrix[top][c] = i+1;
				c++;
				if(c == right) {
					dir = RIGHT;
					top++;
				}
				break;
			case RIGHT:
				matrix[r][right] = i+1;
				r++;
				if(r == bottom) {
					dir = BOTTOM;
					right--;
				}
				break;
			case BOTTOM:
				matrix[bottom][c] = i+1;
				c--;
				if(c == left) {
					dir = LEFT;
					bottom--;
				}
				break;
			case LEFT:
				matrix[r][left] = i+1;
				r--;
				if(r == top) {
					dir = TOP;
					left++;
				}
				break;
		}
	}

	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			printf("%d%c", matrix[i][j], (j < N-1) ? '\t' : '\n');

	return 0;
}