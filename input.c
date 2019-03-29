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

#include "state.h"
#include "input.h"

state_s *parse_move(state_s *cur_state, char *move) {
    int s_row, s_col, e_row = 10, e_col = 10;
    int i;
    bool valid = false;

    // Check if move syntax is correct (either "XX" or "XX-XX")
    if (strlen(move) != 5 && strlen(move) != 2) {
        printf("Invalid move syntax");
        return NULL;
    }

    s_row = move[1] - '0' - 1;
    s_col = move[0] - 'A';

    if (strlen(move) == 5) {
        e_row = move[4] - '0' - 1;
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
        return cur_state->children[i];
    }
    
    return NULL;
}
