#include "SnakeBody.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct element {
    int x_pos;
    int y_pos;
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
            newTailBlock->y_pos = oldTailBlock->y_pos +1;
            break;
        case SOUTH:
            newTailBlock->block_direction = SOUTH;
            newTailBlock->x_pos = oldTailBlock->x_pos;
            newTailBlock->y_pos = oldTailBlock->y_pos -1;
            break;
    }
    body->tail = newTailBlock;
    body->body_length = body->body_length +1;
}

unsigned int size(SnakeBody * body) {
    return body->body_length;
}

void update(SnakeBody * body) {
    BodyBlock * currentBlock = body->head;
    updateCoordsDirection(currentBlock);
    BodyBlock * next = currentBlock->next_block;
    while(next != NULL) {
        if (currentBlock->block_direction == next->block_direction) {
            updateCoordsDirection(next);
            currentBlock = next;
            next = next->next_block;
        }
        else {
            next->block_direction = currentBlock->block_direction;
            updateCoordsDirection(next);
            next = next->next_block;
            updateCoordsDirection(next);
            if (next != NULL) {
                currentBlock = next;
                next = next->next_block;
            }
        }
    }
}

void updateCoordsDirection(BodyBlock * block) {
    if (block != NULL) {
        switch(block->block_direction) {
            case WEST:
                block->x_pos = block->x_pos +1;
                break;
            case EAST:
                block->x_pos = block->x_pos -1;
                break;
            case NORTH:
                block->y_pos = block->y_pos -1;
                break;
            case SOUTH:
                block->y_pos = block->y_pos +1;
                break;
        }
    }
}

int isSnake(SnakeBody * body, int x, int y) {
    BodyBlock * currentBlock = body->head;
    while(currentBlock != NULL) {
        if (currentBlock->x_pos == x && currentBlock->y_pos == y) {
            return 1;
        }
        currentBlock = currentBlock->next_block;
    }
    return 0;
}

void printSnake(SnakeBody * body) {
    BodyBlock * currentBlock = body->head;
    char * dir;
    while(currentBlock != NULL) {
        switch(currentBlock->block_direction) {
        case WEST:
                dir = "WEST";
                break;
            case EAST:
                dir = "EAST";
                break;
            case NORTH:
                dir = "NORTH";
                break;
            case SOUTH:
                dir = "SOUTH";
                break;
        }
        if (currentBlock->next_block != NULL) {
            printf("(%d, %d, %s) -> ", currentBlock->x_pos, currentBlock->y_pos, dir);
        }
        else{
            printf("(%d, %d, %s)\n", currentBlock->x_pos, currentBlock->y_pos, dir);
        }
        currentBlock = currentBlock->next_block;
    }
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
