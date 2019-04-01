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

#define BOARD_SIZE 8

#define NEG_INF (INT_MIN)
#define POS_INF (INT_MAX)

#define STONE_BLACK 'B'
#define STONE_WHITE 'W'
#define EMPTY_SPACE 'O'

#define DEFAULT_MOVE_POS    (BOARD_SIZE)

typedef enum {
    PLAYER_NONE = EMPTY_SPACE,
    PLAYER_BLACK = STONE_BLACK,
    PLAYER_WHITE = STONE_WHITE,
} player_type;

typedef enum {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_NONE,
} direction;

typedef enum {
  INIT_BLACK,
  INIT_WHITE,
  SEARCH_BLACK,
  SEARCH_WHITE,
} search_type;

typedef struct {
    uint8_t start_row;
    uint8_t start_col;
    uint8_t end_row;
    uint8_t end_col;
} move_s;

typedef struct state_s {
    uint8_t board[BOARD_SIZE][BOARD_SIZE];
    int eval;
    move_s move;
    player_type player;
    int num_moves;
    int cur_size; // number of children
    int max_size;
    struct state_s *parent;
    struct state_s **children;
    int successor; // index of selected child state
} state_s;

void print_move(state_s *state);

void print_state(state_s *state);

state_s *init_model(state_s *parent, uint8_t current[BOARD_SIZE][BOARD_SIZE]);

void free_model(state_s *model);

void free_model_children(state_s *state);

void free_all_but_child(state_s *state, int child);

int add_child(state_s *parent, state_s *child);

state_s *best_move(state_s *state);

int duplicate_state(state_s *state_1, state_s *state_2);

uint64_t hash_state(state_s *state);

#endif /* MODEL_H */
