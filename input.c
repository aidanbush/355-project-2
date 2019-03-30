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
#include <stdbool.h>

#include "state.h"
#include "input.h"

bool check_opponent_move(state_s *cur_state, char *move) {
    int s_row, s_col, e_row = 10, e_col = 10;
    int i, len;
    bool valid = false;

    // Check if move syntax is correct (either "XX" or "XX-XX")
    len = strlen(move);
    if (len != 5 && len != 2) {
        printf("Invalid move syntax\n");
        return false;
    }

    s_row = BOARD_SIZE - (move[1] - '0');
    s_col = move[0] - 'A';

    if (len == 5) {
        e_row = BOARD_SIZE - (move[4] - '0');
        e_col = move[3] - 'A';
    }
    // Check if the move is in the list of valid moves
    for (i=0; i<cur_state->cur_size; i++) {
        if (cur_state->children[i]->move.start_row == s_row
        && cur_state->children[i]->move.start_col == s_col
        && cur_state->children[i]->move.end_row == e_row
        && cur_state->children[i]->move.end_col == e_col) {
            valid = true;
            break;
        }
    }

    if (valid) {
        cur_state->successor = i;
        return true;
    }
    
    printf("Invalid move.\n");
    return false;
}
