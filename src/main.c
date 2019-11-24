#include <stdio.h>
#include <stdlib.h>
#include "SnakeBody.h"

int main()
{
    printf("Hello world!\n");
    SnakeBody * body = createSnake(2);
    enlargeSnake(body);
    destroySnake(body);
    return 0;
}
