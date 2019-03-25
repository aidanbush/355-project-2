/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 11, 19
 * File: model.h
 * Description: Header file for model.
 */

#ifndef MODEL_H
#define MODEL_H

#include <stdint.h>
#include <limits.h>

#define BOARD_SIZE      8

#define NEG_INF (INT_MAX)
#define POS_INT (INT_MIN)

#define STONE_BLACK 'B'
#define STONE_WHITE 'W'
#define EMPTY_SPACE 'O'


typedef struct state_s {
    uint8_t board[BOARD_SIZE][BOARD_SIZE];
    int eval;
    int cur_size;
    int max_size;
    struct state_s *parent;
    struct state_s **children;
} state_s;

state_s *init_model();

void free_model(state_s *model);

int add_child(state_s *parent, state_s *child);

#endif /* MODEL_H */
