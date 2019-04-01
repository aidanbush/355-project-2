/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 27, 19
 * File: input.h
 * Description: Header file for input.
 */

#ifndef INPUT_H
#define INPUT_H

#include "state.h"

int check_opponent_move(state_s *cur_state, char *move, int move_len);

#endif /* INPUT_H */
