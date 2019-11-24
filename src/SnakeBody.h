#ifndef SNAKEBODY_H_INCLUDED
#define SNAKEBODY_H_INCLUDED

typedef struct body SnakeBody;

typedef struct element BodyBlock;

typedef enum {
    EAST = 0, WEST = 1, NORTH = 2, SOUTH = 3
} Direction;

SnakeBody * createSnake(unsigned int startLength);

void destroySnake(SnakeBody * body);

void update(SnakeBody * body);

void enlargeSnake(SnakeBody * body);

void updateCoordsDirection(BodyBlock * block);

void printSnake(SnakeBody * body);

int isSnake(SnakeBody * body, int x, int y);

unsigned int size(SnakeBody * body);
#endif // SNAKEBODY_H_INCLUDED
