/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 26, 2019
 * File: remaining_stones_heuristic.c
 * Description: counts the remaining stones for black and white and taking the difference as heuristic value
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "remaining_stones_heuristic.h"
#include "state.h"

int remaining_stones(uint8_t board[BOARD_SIZE][BOARD_SIZE], search_type move_set) {
    int row, col, stones = 0;
    char search_char;
    
    if (move_set == SEARCH_BLACK) {
        search_char = STONE_BLACK;
    }
    else {
        search_char = STONE_WHITE;
    }
    
    // Traverse through the whole board to count everything that matches search_char
    for (row=0; row<BOARD_SIZE; row++) {
        for (col=0; col<BOARD_SIZE; col++) {
            if (board[row][col] == search_char) {
                stones++;
            }
        }
    }
    
    return stones;
}

int remaining_diff(uint8_t board[BOARD_SIZE][BOARD_SIZE]) {
    int black_remaining = remaining_stones(board, SEARCH_BLACK);
    int white_remaining = remaining_stones(board, SEARCH_WHITE);
    
    return (black_remaining - white_remaining);
}

#ifdef _TEST_HEURISTIC
int main() {
    uint8_t board_start[BOARD_SIZE][BOARD_SIZE] = {
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
    };

    uint8_t board_1[BOARD_SIZE][BOARD_SIZE] = {
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'O', 'W', 'O', 'W', 'O', 'W',},
        {'W', 'B', 'W', 'O', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'O', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
        {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W',},
        {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B',},
    };

    uint8_t board_2[BOARD_SIZE][BOARD_SIZE] = {
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',},
    };

    // board_start
    assert(remaining_stones(board_start, SEARCH_BLACK) == 32);
    assert(remaining_stones(board_start, SEARCH_WHITE) == 32);
    
    assert(remaining_diff(board_start) == 0);

    // board_1
    assert(remaining_stones(board_1, SEARCH_BLACK) == 28);
    assert(remaining_stones(board_1, SEARCH_WHITE) == 31);

    assert(remaining_diff(board_1) == (28 - 31));

    // board_2
    assert(remaining_stones(board_2, SEARCH_BLACK) == 0);
    assert(remaining_stones(board_2, SEARCH_WHITE) == 0);

    assert(remaining_diff(board_2) == 0);
}
#endif /* _TEST_HEURISTIC */
