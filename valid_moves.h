/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * File: valid_moves.h
 * Description: Header file for valid_moves
 */

#ifndef VALID_MOVES_H
#define VALID_MOVES_H

//prints the state
void print_state(uint8_t state[BOARD_SIZE][BOARD_SIZE]);

//copys the state to a new state
void copy_state(uint8_t temp[BOARD_SIZE][BOARD_SIZE], state_s *cur_state);

//obtains all the valid_states
void valid_moves(state_s *cur_state, search_type move_set);

#endif /* VALID_MOVES_H */
