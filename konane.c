/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 17, 19
 * File: konane.c
 * Description: Main konane solving file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "state.h"
#include "valid_moves.h"
#include "input.h"

state_s *read_input(char *filename) {
    FILE *file;
    int row = 0, col = 0;
    int ch, last = '\0';
    int err = 0;
    state_s *state;
    uint8_t temp_state[BOARD_SIZE][BOARD_SIZE];

    // open file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error: Invalid file name.\n");
        return NULL;
    }

    while ((ch = getc(file)) != EOF && !err) {
        switch (ch) {
            case 'B':
                if (col >= BOARD_SIZE)
                    err = 1;
                temp_state[row][col++] = STONE_BLACK;
                break;
            case 'W':
                if (col >= BOARD_SIZE)
                    err = 1;
                temp_state[row][col++] = STONE_WHITE;
                break;
            case 'O':
                if (col >= BOARD_SIZE)
                    err = 1;
                temp_state[row][col++] = EMPTY_SPACE;
                break;
            case '\n':
            case '\r':
                if (last != '\r' && last != '\n' && last != '\0') {
                    row++;
                    col = 0;
                }
                break;
            default:
                err = 1;
                fprintf(stderr, "Error invalid character in board file\n");
                break;
        }
        last = ch;
    }
    // create model
    state = init_model(NULL, temp_state);
    if (state == NULL)
        return NULL;

    if (err) {
        free_model(state);
        state = NULL;
    }

#ifdef _TEST_INPUT
    if (!err)
        print_state(state);
#endif /* _TEST_INPUT */

    fclose(file);
    return state;
}

search_type get_search_type(state_s *state, uint8_t stone){
    uint8_t stone_type;
    search_type search;
    int count = 0, row, col;
    if (stone == 'B') {
        search = SEARCH_BLACK;
        stone_type = STONE_BLACK;
    } else {
        search = SEARCH_WHITE;
        stone_type = STONE_WHITE;
    }
    //Will only check rows and columns that belong to the stone type
    for (int i = 0; i < BOARD_SIZE; i++) {
        row = i;
        for (int j = 0; j < BOARD_SIZE / 2; j++) {
            if (row % 2 == 0) {
                if (stone_type == STONE_BLACK) {
                    col = j * 2;
                } else {
                    col = j * 2 + 1;
                }
            } else {
                if (stone_type == STONE_BLACK) {
                col = j * 2 + 1;
                } else {
                col = j * 2;
                }
            }
            /* If we find zero empty spaces for the given color then 
             * we know the init state has been found for the provided 
             * stone type
             */
            if (state->board[row][col] == EMPTY_SPACE)
                count++;
        }
    }
    if (count == 0) {
        if (stone_type == STONE_BLACK)
            return INIT_BLACK;
        else
            return INIT_WHITE;
    }
    else
        return search;
}

bool check_game_over(state_s *state) {
    int moves = state->cur_size;
    return (moves == 0);
}

int main(int argc, char **argv) {
    char *filename;
    char opponent_move[5];
    uint8_t player_type;
    uint8_t opponent_type;
    search_type search;
    state_s *cur_state;

    // Deal with command line arguments
    if (argc < 3) {
        fprintf(stderr,"Too Few Arguments\n");
        return 1;
    }
    filename = argv[1];
    cur_state = read_input(filename);
    player_type = argv[2][0];
    if (player_type == STONE_BLACK) {
        opponent_type = STONE_WHITE;
        cur_state->player = STONE_BLACK;
    }
    else {
        opponent_type = STONE_BLACK;
        cur_state->player = STONE_WHITE;
    }
    
    search = get_search_type(cur_state, player_type);
    
    if (cur_state == NULL) {
        fprintf(stderr, "Error parsing text file\n");
        return 1;
    }

    // The game loop
    valid_moves(cur_state, search); // Create all children for current state
    while (!check_game_over(cur_state)) {
        printf("Current stage:");
        print_state(cur_state);
        printf("-----%c's turn-----\n", cur_state->player);
        
        if (cur_state->player == player_type) {
            // TODO: Run minimax on current state
            //cur_state = cur_state->children[cur_state->successor];
            cur_state = cur_state->children[0];
            cur_state->player = opponent_type;

            printf("Selected move: ");
            print_move(cur_state);

            // Change search type
            if (search == INIT_BLACK)
                search = INIT_WHITE;
            else if (search == INIT_WHITE)
                search = SEARCH_BLACK;
            else if (search == SEARCH_BLACK)
                search = SEARCH_WHITE;
            else if (search == SEARCH_WHITE)
                search = SEARCH_BLACK;
        }
        else {
            printf("Enter move: ");
            scanf("%s", opponent_move);
            while (!check_opponent_move(cur_state, opponent_move)) {
                printf("Enter move again: ");
                scanf("%s", opponent_move);
            }
            cur_state = cur_state->children[cur_state->successor];
            cur_state->player = player_type;

            // Change search type
            if (search == INIT_BLACK)
                search = INIT_WHITE;
            else if (search == INIT_WHITE)
                search = SEARCH_BLACK;
            else if (search == SEARCH_BLACK)
                search = SEARCH_WHITE;
            else if (search == SEARCH_WHITE)
                search = SEARCH_BLACK;
        }
        valid_moves(cur_state, search);
    }
    if (cur_state->player == STONE_BLACK)
        printf("White wins!\n");
    else
        printf("Black wins!\n");

    // Clear memory
    free_model(cur_state);

    return 0;
}
