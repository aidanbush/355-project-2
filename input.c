/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 27, 19
 * File: input.c
 * Description: handles input from opponent.
 */

#include <stdlib.h>
#include <stdio.h>

#include "state.h"
#include "input.h"

state_s *parse_move(state_s *cur_state, char *move, int len) {
    int s_row, s_col, e_row, e_col;
    state_s *new_state;

    if (len < 4)
        return NULL;
    // error

    new_state = init_model(cur_state, cur_state->board);
    if (new_state == NULL)
        return NULL;

    s_row = move[1] - '0';
    s_col = move[0] - 'A';
    e_row = move[4] - '0';
    e_col = move[3] - 'A';

    if (s_row < 0 || s_row > 8 || s_col < 0 || s_col > 8 || e_row < 0
            || e_row > 8 || e_col < 0 || e_col > 8) {
        fprintf(stderr, "Invalid move, out of range\n");
        free_model(new_state);
        return NULL;
    }

    new_state->move.start_row = s_row;
    new_state->move.start_col = s_col;

    new_state->move.end_row = e_row;
    new_state->move.end_col = e_col;

    if (s_row == e_row && s_col == e_col){
        new_state->board[s_col][s_row] = EMPTY_SPACE;
        return new_state;
    }

    uint8_t start_tile = new_state->board[s_row][s_col];
    // make move
    //printf("%d %d\n",abs(s_row - e_row),abs(s_col - e_col));

    int e1 = e_row;
    int e2 = e_col;

    if (e_row < s_row) {
        int t = s_row;
        s_row = e_row;
        e_row = t;
    }
    if (e_col < s_col) {
        int t = s_col;
        s_col = e_col;
        e_col = t;
    }

    for (int i = s_row; i < e_row + 1; i++) {
        for (int j = s_col; j < e_col + 1; j++) {
            new_state->board[j][i] = EMPTY_SPACE;
            //printf("%d %d\n", i, j);
        }
    }

    new_state->board[e2][e1] = start_tile;

    return new_state;
}
