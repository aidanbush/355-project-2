/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 24, 19
 * File: difference_heuristic.c
 * Description: counts the available moves for black and white and takes the difference for our heuristic value.
 */

#include <stdint.h>
#include <assert.h>

#include "heuristic.h"
#include "state.h"

int num_moves(uint8_t board[BOARD_SIZE][BOARD_SIZE], int player) {
    int row, col, dist;
    int moves = 0;

    // row
    for (int i = 0; i < BOARD_SIZE / 2; i++) {
        row = i * 2 + player;
        printf("row %d\n", row);
        // col
        for (int j = 0; j < BOARD_SIZE / 2; j++) {
            col = j * 2 + player;
            printf("col %d\n", col);

            // left
            dist = 1;
            while ((col - 2*dist) > 0) {
                if (board[row][col] == EMPTY_SPACE ||
                        board[row][col - dist*2 + 1] == EMPTY_SPACE ||
                        board[row][col - dist*2] != EMPTY_SPACE)
                    break;
                printf("left\n");
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
                printf("right\n");
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
                printf("down\n");
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
                printf("up\n");
                dist++;
                moves++;
            }
        }
    }

    return moves;
}

int num_moves_diff(search_type type, uint8_t board [BOARD_SIZE][BOARD_SIZE]) {
    if (type == INIT_BLACK || type == INIT_WHITE)
        return 0;

    // black:0 white:1
    int moves[2] = {0};
    int row, col;

    for (int player = 0; player < 2; player++) {
        moves[player] = num_moves(board, player);
    }

    return moves[0] - moves[1];
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

    // init black
    assert(num_moves_diff(INIT_BLACK, board_start) == 0);
    // init white
    assert(num_moves_diff(INIT_WHITE, board_start) == 0);

    // board_1
    printf("%d\n", num_moves(board_1, 0));
    printf("%d\n", num_moves(board_1, 1));
    assert(num_moves(board_1, 0) == 12);
    assert(num_moves(board_1, 1) == 3);

    assert(num_moves_diff(SEARCH_BLACK, board_1) == 12 - 3);
    assert(num_moves_diff(SEARCH_WHITE, board_1) == 12 - 3);
}
#endif /* _TEST_HEURISTIC */
