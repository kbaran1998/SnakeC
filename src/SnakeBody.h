#ifndef SNAKEBODY_H_INCLUDED
#define SNAKEBODY_H_INCLUDED

typedef struct body SnakeBody;

typedef struct element BodyBlock;

typedef enum {
    EAST, WEST, NORTH, SOUTH
} Direction;

SnakeBody * createSnake(unsigned int startLength);

void destroySnake(SnakeBody * body);

void update(SnakeBody * body);

void enlargeSnake(SnakeBody * body);

#endif // SNAKEBODY_H_INCLUDED
