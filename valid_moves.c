/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 24, 19
 * File: valid_moves.c
 * Description: generates the valid moves for a given state based off a colour of stone.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "state.h"
#include "valid_moves.h"

#ifdef _TEST_VALID_MOVES
#include "manager.h"
#include "heuristic.h"

extern manager_s manager;
#endif /* _TEST_VALID_MOVES */

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif /* MIN */

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif /* MAX */

/*Helper function to initialize a new state with the same layout as the current state*/
void copy_state(uint8_t temp[BOARD_SIZE][BOARD_SIZE], state_s *cur_state) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            temp[i][j] = cur_state->board[i][j];
        }
    }
}

static void make_move(uint8_t init_board[BOARD_SIZE][BOARD_SIZE],
        uint8_t res_board[BOARD_SIZE][BOARD_SIZE], int s_row, int s_col,
        int e_row, int e_col) {
    move_s move;

    move.start_row = MIN(s_row, e_row);
    move.end_row = MAX(s_row, e_row);
    move.start_col = MIN(s_col, e_col);
    move.end_col = MAX(s_col, e_col);

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            res_board[i][j] = init_board[i][j];

    if (e_row == DEFAULT_MOVE_POS || e_col == DEFAULT_MOVE_POS) {
        res_board[s_row][s_col] = EMPTY_SPACE;
    } else {
        for (int i = move.start_row; i <= move.end_row; i++)
            for (int j = move.start_col; j <= move.end_col; j++)
                res_board[i][j] = EMPTY_SPACE;

        res_board[e_row][e_col] = init_board[s_row][s_col];
    }
}

static int create_child(state_s *parent, search_type move_set, int s_row,
        int s_col, int e_row, int e_col) {
    if (parent == NULL || move_set == INIT_BLACK || move_set == INIT_WHITE) {
        fprintf(stderr, "create_child: error in parameters\n");
        return 0;
    }

    state_s *child;
    uint8_t board[BOARD_SIZE][BOARD_SIZE];
    player_type player;

    if (move_set == SEARCH_BLACK)
        player = PLAYER_BLACK;
    else
        player = PLAYER_WHITE;

    make_move(parent->board, board, s_row, s_col, e_row, e_col);

    child = init_model(parent, board, player);
    if (child == NULL) {
        fprintf(stderr, "create_child: error in init_model\n");
        return 0;
    }

    child->move.start_row = s_row;
    child->move.start_col = s_col;
    child->move.end_row = e_row;
    child->move.end_col = e_col;

    return !add_child(parent, child);
}

/*Determines every possible state for the given move_set. The move_set is an identifier
 * for which stone we will be generating the moves for
 */
void valid_moves(state_s *cur_state, search_type move_set) {
    int row, col, dist, err;
    player_type search_char; //whether we are looking for the available moves for white or black

    //Restricted set of possible moves made for initial move
    if (move_set == INIT_BLACK) {
        err = create_child(cur_state, SEARCH_BLACK, 3, 3, DEFAULT_MOVE_POS, DEFAULT_MOVE_POS);
        if (err) {
            fprintf(stderr, "valid_moves(%d): error in creating child\n", __LINE__);
            return;
        }

        err = create_child(cur_state, SEARCH_BLACK, 4, 4, DEFAULT_MOVE_POS, DEFAULT_MOVE_POS);
        if (err) {
            fprintf(stderr, "valid_moves(%d): error in creating child\n", __LINE__);
            return;
        }

        return;
    }

    if (move_set == INIT_WHITE) {
        err = create_child(cur_state, SEARCH_WHITE, 3, 4, DEFAULT_MOVE_POS, DEFAULT_MOVE_POS);
        if (err) {
            fprintf(stderr, "valid_moves(%d): error in creating child\n", __LINE__);
            return;
        }

        err = create_child(cur_state, SEARCH_WHITE, 4, 3, DEFAULT_MOVE_POS, DEFAULT_MOVE_POS);
        if (err) {
            fprintf(stderr, "valid_moves(%d): error in creating child\n", __LINE__);
            return;
        }
        return;
    }
    //assign which colour of stone we are evaluating based off of
    if (move_set == SEARCH_BLACK) {
        search_char = STONE_BLACK;
    } else {
        search_char = STONE_WHITE;
    }

    //Search through state for possible moves based off search_char
    //row
    for (int i = 0; i < BOARD_SIZE; i++)  {
        row = i;
        //col
        for (int j = 0; j < BOARD_SIZE / 2; j++) {
            if (row % 2 == 0) {
                if (search_char == STONE_BLACK) {
                    col = j * 2;
                } else {
                    col = j * 2 + 1;
                }
            } else {
                if (search_char == STONE_BLACK) {
                    col = j * 2 + 1;
                } else {
                    col = j * 2;
                }
            }

            //down
            dist = 1;
            while ((row + 2 * dist) < BOARD_SIZE) {
                if ((cur_state->board[row][col] == EMPTY_SPACE) ||
                        cur_state->board[row + dist *2 - 1][col] == EMPTY_SPACE ||
                        cur_state->board[row + dist *2][col] != EMPTY_SPACE)
                    break;

                err = create_child(cur_state, move_set, row, col, row + dist * 2, col);
                if (err) {
                    fprintf(stderr, "valid_moves(%d): error in creating child\n", __LINE__);
                    return;
                }
                dist++;
            }

            // up
            dist = 1;
            while ((row - 2 * dist) >= 0) {
                if ((cur_state->board[row][col] == EMPTY_SPACE) ||
                        cur_state->board[row - dist *2 + 1][col] == EMPTY_SPACE ||
                        cur_state->board[row - dist *2][col] != EMPTY_SPACE)
                    break;

                err = create_child(cur_state, move_set, row, col, row - dist * 2, col);
                if (err) {
                    fprintf(stderr, "valid_moves(%d): error in creating child\n", __LINE__);
                    return;
                }
                dist++;
            }

            // right
            dist = 1;
            while ((col + 2 * dist) < BOARD_SIZE) {
                if ((cur_state->board[row][col] == EMPTY_SPACE) ||
                        cur_state->board[row][col + dist *2 - 1] == EMPTY_SPACE ||
                        cur_state->board[row][col + dist *2] != EMPTY_SPACE)
                    break;

                err = create_child(cur_state, move_set, row, col, row, col + dist * 2);
                if (err) {
                    fprintf(stderr, "valid_moves(%d): error in creating child\n", __LINE__);
                    return;
                }
                dist++;
            }

            // left
            dist = 1;
            while ((col - 2 * dist) >= 0) {
                if ((cur_state->board[row][col] == EMPTY_SPACE) ||
                        cur_state->board[row][col - dist *2 + 1] == EMPTY_SPACE ||
                        cur_state->board[row][col - dist *2] != EMPTY_SPACE)
                    break;

                err = create_child(cur_state, move_set, row, col, row, col - dist * 2);
                if (err) {
                    fprintf(stderr, "valid_moves(%d): error in creating child\n", __LINE__);
                    return;
                }
                dist++;
            }
        }
    }
}

#ifdef _TEST_VALID_MOVES

int main() {
    state_s *parent;
    init_manager();

    uint8_t board_start[BOARD_SIZE][BOARD_SIZE] = {
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
    };

    uint8_t board_1[BOARD_SIZE][BOARD_SIZE] = {
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'O', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'O', 'O', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
    };

    // board start
    parent = init_model(NULL, board_start, INIT_BLACK);
    if (parent == NULL)
        return 1;

    valid_moves(parent, INIT_BLACK);
    printf("moves\n");
    for (int i = 0; i < parent->cur_size; i++) {
        print_move(parent->children[i]);
        print_state(parent->children[i]);
    }
    free_model_children(parent);

    parent = init_model(NULL, board_start, INIT_WHITE);
    if (parent == NULL)
        return 1;

    valid_moves(parent, INIT_WHITE);
    printf("moves\n");
    for (int i = 0; i < parent->cur_size; i++) {
        print_move(parent->children[i]);
        print_state(parent->children[i]);
    }
    free_model_children(parent);

    // board_1
    parent = init_model(NULL, board_1, SEARCH_BLACK);
    if (parent == NULL)
        return 1;

    valid_moves(parent, SEARCH_BLACK);
    printf("moves\n");
    for (int i = 0; i < parent->cur_size; i++) {
        print_move(parent->children[i]);
        print_state(parent->children[i]);
    }
    free_model_children(parent);

    parent = init_model(NULL, board_1, SEARCH_WHITE);
    if (parent == NULL)
        return 1;

    valid_moves(parent, SEARCH_WHITE);
    printf("moves\n");
    for (int i = 0; i < parent->cur_size; i++) {
        print_move(parent->children[i]);
        print_state(parent->children[i]);
    }
    free_model_children(parent);

    return 0;
}

#endif /* _TEST_VALID_MOVES */
