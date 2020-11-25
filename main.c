#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 void allocate_2D_array(char*** array, int M, int N) {
    *array = (char**)malloc(sizeof(char*) * M);
    for (int i = 0; i < M; i++) {
        (*array)[i] = (char*)malloc(sizeof(char) * N);
    }
}


void fill_2D_array(char*** array, int M, int N) {
    int a = 0;

    for (int i = 0; i < N; i++) {
        (*array)[0][i] = '-';
        }

    for (int i = 1; i < M - 1; i++) {
        (*array)[i][N-1] = '|';
    }

   for (int i = 0; i < N; i++) {
        (*array)[M-1][i] = '-';
    }

	for (int i = 1; i < M - 1; i++) {
        (*array)[i][0] = '|';
    }

    for (int i = 1; i < M-1; i++)
    {
        for (int j = 1; j < N-1; j++)
        {
            {
            (*array)[i][j] = ' ';
            }
        }
    } 
}

int L(int x, int y, int x1, int y1, int x2, int y2) {
  return (x-x1)*(y2-y1) - (y-y1)*(x2-x1);
}

int get_direction(int x, int y, int x1, int y1, int x2, int y2) {
    int s = abs(L(x+1,y,x1,y1,x2,y2));
    int w = abs(L(x,y+1,x1,y1,x2,y2));
    int sw = abs(L(x+1,y+1,x1,y1,x2,y2));
    if (s <= sw && s < w) {
        return 0;
    }
    if (w <= sw && w < s) {
        return 1;
    }
    if (sw <= s && sw < w) {
        return 2;
    }
    return -1;
}

int draw_line(char*** array, int M, int N, int x1, int y1, int x2, int y2) {
    if (x1 < 1 || x1 > M) return -1;
    if (y1 < 1 || y1 > N) return -1;
    if (x2 < 1 || x2 > M) return -1;
    if (y2 < 1 || y2 > N) return -1;

    if (x1 > x2) return -1;
    if (y1 > y2) return -1;

    (*array)[x1][y1] = '*';
    (*array)[x2][y2] = '*';

    int delta_x = x1 - x2;
    int delta_y = y1 - y2;
    int x=x1;
    int y=y1;
    (*array)[x][y] = '*';
    for(; x<x2; ) {
        for(; y<y2; ) {
            int direction = get_direction(x, y, x1, y1, x2, y2);
            if (direction == 0) {
                ++x;
            }
            if (direction == 1) {
                ++y;
            }
            if (direction == 2) {
                ++x;
                ++y;
            }
            if (x > 0 && x < M && y > 0 && y < N) {
                (*array)[x][y] = '*';
            } else {
                return -1;
            }
        }
    }
    return 0;
}

void draw_2D_array(char*** array, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c", (*array)[i][j]);
        }
        printf("\n");
    }
}

int main (void) {
    int M = 17;
    int N = 17; 
    char** array = NULL;
    allocate_2D_array(&array, M, N);
    fill_2D_array(&array, M, N);
    draw_line(&array,M, N, 2, 5, 9, 14);
    draw_2D_array(&array, M, N);
    free(array);
    array = NULL;
    return 0;
}
