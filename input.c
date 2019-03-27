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

    printf("s_r%d, s_col%d, e_r%d, e_c%d\n", s_row, s_col, e_row, e_col);

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

    uint8_t start_tile = new_state->board[s_row][s_col];
    // make move
    for (int i = 0; i < abs(s_row - e_row); i++)
        for (int j = 0; j < abs(s_col - e_col); j++)
            new_state->board[i][j] = EMPTY_SPACE;

    new_state->board[e_row][e_col] = start_tile;

    return new_state;
}
