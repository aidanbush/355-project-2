/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 26, 2019
 * File: remaining_stones_heuristic.h
 * Description: Header file for remaining stones heuristic
 */

#ifndef REMAINING_STONES_HEURISTIC_H
#define REMAINING_STONES_HEURISTIC_H

#include <stdint.h>

#include "state.h"

typedef enum {
    INIT_BLACK,
    INIT_WHITE,
    SEARCH_BLACK,
    SEARCH_WHITE,
} search_type;

int remaining_stones(uint8_t board[BOARD_SIZE][BOARD_SIZE], search_type move_set);

int remaining_diff(uint8_t board[BOARD_SIZE][BOARD_SIZE]);

#endif
