/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * File: difference_heuristic.h
 * Description: Header file for difference heuristic
 */

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <stdint.h>

#include "state.h"

typedef int (*heur_func)(search_type type, uint8_t board[BOARD_SIZE][BOARD_SIZE]);

int num_moves_diff(search_type type, uint8_t board[BOARD_SIZE][BOARD_SIZE]);

#endif /* HEURISTIC_H */
