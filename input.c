/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 27, 19
 * File: input.c
 * Description: Receives a move, validate it, then return the new state.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "input.h"
#include "state.h"

int check_opponent_move(state_s *cur_state, char *move, int move_len) {
    uint8_t s_row, s_col;
    uint8_t e_row = DEFAULT_MOVE_POS, e_col = DEFAULT_MOVE_POS;

    // Check if move syntax is correct (either "XX" or "XX-XX")
    if (move_len != 6 && move_len != 3) {
        fprintf(stderr, "Move string len %d\n", move_len);
        return -1;
    }

    s_row = BOARD_SIZE + '0' - move[1];
    s_col = move[0] - 'A';

    if (move_len == 6) {
        e_row = BOARD_SIZE + '0' - move[4];
        e_col = move[3] - 'A';
    }

    // Check if the move is in the list of valid moves
    for (int i = 0; i<cur_state->cur_size; i++) {
        if (cur_state->children[i]->move.start_row == s_row
                && cur_state->children[i]->move.start_col == s_col
                && cur_state->children[i]->move.end_row == e_row
                && cur_state->children[i]->move.end_col == e_col) {
            return i;
        }
        // fprintf(stderr,"CHILD #%d\n", i);
        // print_state(cur_state->children[i]);
    }
    return -1;
}
