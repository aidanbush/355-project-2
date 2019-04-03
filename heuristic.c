/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 24, 19
 * File: difference_heuristic.c
 * Description: counts the available moves for black and white and takes the difference for our heuristic value.
 */

#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#include "heuristic.h"
#include "state.h"

#define NEG_BOUND -100
#define POS_BOUND 100

int num_moves(uint8_t board[BOARD_SIZE][BOARD_SIZE], player_type player_color) {
    int row, col, dist;
    int moves = 0;
    int player;
    if (player_color == PLAYER_BLACK)
        player = 0;
    else
        player = 1;
    // row
    for (int i = 0; i < BOARD_SIZE; i++) {
        row = i;
        // col
        for (int j = 0; j < BOARD_SIZE / 2; j++) {
            if (row % 2 == 0)
                col = j * 2 + player;
            else
                col = j * 2 + (player ? 0 : 1);

            // left
            dist = 1;
            while ((col - 2*dist) > 0) {
                if (board[row][col] == EMPTY_SPACE ||
                        board[row][col - dist*2 + 1] == EMPTY_SPACE ||
                        board[row][col - dist*2] != EMPTY_SPACE)
                    break;
                dist++;
                moves++;
            }

            // right
            dist = 1;
            while ((col + 2*dist) < BOARD_SIZE) {
                if (board[row][col] == EMPTY_SPACE ||
                        board[row][col + dist*2 - 1] == EMPTY_SPACE ||
                        board[row][col + dist*2] != EMPTY_SPACE)
                    break;
                dist++;
                moves++;
            }

            // down
            dist = 1;
            while ((row + 2*dist) < BOARD_SIZE) {
                if (board[row][col] == EMPTY_SPACE ||
                        board[row + dist*2 - 1][col] == EMPTY_SPACE ||
                        board[row + dist*2][col] != EMPTY_SPACE)
                    break;
                dist++;
                moves++;
            }

            // up
            dist = 1;
            while ((row - 2*dist) > 0) {
                if (board[row][col] == EMPTY_SPACE ||
                        board[row - dist*2 + 1][col] == EMPTY_SPACE ||
                        board[row - dist*2][col] != EMPTY_SPACE)
                    break;
                dist++;
                moves++;
            }
        }
    }
    return moves;
}

int num_moves_diff(uint8_t board[BOARD_SIZE][BOARD_SIZE]) {

    int black, white, multiplier = 1;
    black = num_moves(board, PLAYER_BLACK);
    white = num_moves(board, PLAYER_WHITE);

    if (black == 0 || white == 0)
        multiplier = 5;

    return (black - white) * multiplier;
}

static int remaining_stones(search_type type, uint8_t board[BOARD_SIZE][BOARD_SIZE]) {
    int start;
    int count = 0;

    if (type == SEARCH_BLACK || type == INIT_BLACK)
        start = 0;
    else
        start = 1;

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = (i + start) % 2; j < BOARD_SIZE; j += 2)
            if (board[i][j] != EMPTY_SPACE)
                count++;

    return count;
}

int num_stones_diff(uint8_t board[BOARD_SIZE][BOARD_SIZE]) {
    return remaining_stones(SEARCH_BLACK, board)
        - remaining_stones(SEARCH_WHITE, board);
}

int combined(uint8_t board[BOARD_SIZE][BOARD_SIZE]) {
    int moves = num_moves_diff(board);
    int stones = num_stones_diff(board);
    return moves * 2 + stones;
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

    // test num_moves_diff
    // init black
    assert(num_moves_diff(INIT_BLACK, board_start) == 0);
    // init white
    assert(num_moves_diff(INIT_WHITE, board_start) == 0);

    // board_1
    assert(num_moves(board_1, 0) == 12);
    assert(num_moves(board_1, 1) == 3);

    assert(num_moves_diff(SEARCH_BLACK, board_1) == 12 - 3);
    assert(num_moves_diff(SEARCH_WHITE, board_1) == 12 - 3);

    // board_2
    assert(num_moves(board_2, 0) == 0);
    assert(num_moves(board_2, 1) == 0);

    assert(num_moves_diff(SEARCH_BLACK, board_2) == 0);
    assert(num_moves_diff(SEARCH_WHITE, board_2) == 0);

    // test num_stones_diff
    // board_start
    assert(remaining_stones(SEARCH_BLACK, board_start) == 32);
    assert(remaining_stones(SEARCH_WHITE, board_start) == 32);

    assert(num_stones_diff(SEARCH_BLACK, board_start) == 0);

    // board_1
    assert(remaining_stones(SEARCH_BLACK, board_1) == 28);
    assert(remaining_stones(SEARCH_WHITE, board_1) == 31);

    assert(num_stones_diff(SEARCH_BLACK, board_1) == (28 - 31));

    // board_2
    assert(remaining_stones(SEARCH_BLACK, board_2) == 0);
    assert(remaining_stones(SEARCH_WHITE, board_2) == 0);

    assert(num_stones_diff(SEARCH_BLACK, board_2) == 0);
}
#endif /* _TEST_HEURISTIC */
