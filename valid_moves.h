/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * File: valid_moves.h
 * Description: Header file for valid_moves
 */

#ifndef VALID_MOVES_H
#define VALID_MOVES_H

//prints the state
int print_state(char** cur_state);

//copys the state to a new state
char** copy_state(char** cur_state);

//obtains all the valid_states
char*** valid_moves(char** cur_state, int move_set);

#endif /* VALID_MOVES_H */
