#include "SnakeBody.h"
#include <assert.h>
#include <stdlib.h>


typedef struct element {
    unsigned int x_pos;
    unsigned int y_pos;
    Direction block_direction;
    BodyBlock * previous_block;
    BodyBlock * next_block;
} BodyBlock;

typedef struct body {
    BodyBlock * head;
    BodyBlock * tail;
    unsigned int body_length;
} SnakeBody;



SnakeBody * createSnake(unsigned int startLength) {
    //Check that the body length is not 0
    assert(startLength != 0);
    //Create snake's body
    SnakeBody * body = (SnakeBody *) malloc(sizeof(SnakeBody));
    //Create snake's first body block
    BodyBlock * ptr_block = (BodyBlock *) malloc(sizeof(BodyBlock));
    //We start the game in left of the board thus
    ptr_block->x_pos = startLength-1;
    ptr_block->y_pos = 0;

    ptr_block->previous_block = NULL;
    ptr_block->next_block = NULL;
    ptr_block->block_direction = WEST;
    //Set the first block to the head of the snake
    body->head = ptr_block;
    BodyBlock * next;
    //Create rest of the body
    for (int i = 1; i < startLength; i++) {
        //Create next body block
        next = (BodyBlock *) malloc(sizeof(BodyBlock));
        next->x_pos = (startLength-1) - i;
        next->y_pos = 0;
        next->previous_block = ptr_block;
        ptr_block->next_block = next;
        next->block_direction = WEST;
        ptr_block = next;
    }
    body->tail = ptr_block;
    body->body_length = startLength;
    return body;
}

void enlargeSnake(SnakeBody * body) {
    BodyBlock * newTailBlock = (BodyBlock *) malloc(sizeof(BodyBlock));
    BodyBlock * oldTailBlock = body->tail;
    oldTailBlock->next_block = newTailBlock;
    newTailBlock->previous_block = oldTailBlock;
    switch(oldTailBlock->block_direction) {
        case WEST:
            newTailBlock->block_direction = WEST;
            newTailBlock->x_pos = oldTailBlock->x_pos -1;
            newTailBlock->y_pos = oldTailBlock->y_pos;
            break;
        case EAST:
            newTailBlock->block_direction = EAST;
            newTailBlock->x_pos = oldTailBlock->x_pos +1;
            newTailBlock->y_pos = oldTailBlock->y_pos;
            break;
        case NORTH:
            newTailBlock->block_direction = NORTH;
            newTailBlock->x_pos = oldTailBlock->x_pos;
            newTailBlock->y_pos = oldTailBlock->y_pos -1;
            break;
        case SOUTH:
            newTailBlock->block_direction = SOUTH;
            newTailBlock->x_pos = oldTailBlock->x_pos;
            newTailBlock->y_pos = oldTailBlock->y_pos +1;
            break;
    }
    body->tail = newTailBlock;
}


void update(SnakeBody * body) {

}


void destroySnake(SnakeBody * body) {
    BodyBlock * current_body_block = body->head;
    BodyBlock * next_body_block = current_body_block->next_block;
    free(current_body_block);
    while(next_body_block != NULL) {
        current_body_block = next_body_block;
        next_body_block = next_body_block->next_block;
        free(current_body_block);
    }
    free(body);
}
