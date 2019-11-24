#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SnakeBody.h"

//typedef struct snakeBoard {
  //  char map[10][10];
//} Board;

int main()
{
    //Board * board = (Board *) malloc(sizeof(Board));
    SnakeBody * body = createSnake(2);

    printf("############\n");
    for (int i = 0; i < 10; i++) {
        char str [12];
        str[0] = '#';
        for (int j = 0; j < 10; j++) {
            if (isSnake(body, j, i)) {
                str[j+1] = '@';
            }
            else {
                str[j+1] = ' ';
            }
        }
        str[11] = '#';
        printf("%s\n", str);
    }
    printf("############\n");

    printf("Snake body length: %d\n", size(body));
    printSnake(body);
    update(body);
    enlargeSnake(body);
    printf("Snake body length: %d\n", size(body));
    printSnake(body);
    destroySnake(body);
    return 0;
}
