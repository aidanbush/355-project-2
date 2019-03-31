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
#include <unistd.h>
#include <libgen.h>
#include <pthread.h>

#include "state.h"
#include "valid_moves.h"
#include "input.h"
#include "heuristic.h"
#include "manager.h"

extern manager_s manager;
int verbosity;

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
        perror("fopen");
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

int check_game_over(state_s *state) {
    return state->cur_size == 0;
}

void print_usage(char *p_name) {
    printf("Usage: %s [OPTIONS...] Boardfile Player\n"
            "Konane (Hawaiian Checkers) agent.\n\n"
            "Player is either \"B\" or \"W\"\n"
            "Options\n"
            "  -v verbosity (increases with more)\n"
            "  -g specify heuristic:\n"
            "     1 - difference in moves\n"
            "     2 - difference in stones\n"
            "  -h this usage message\n", basename(p_name));
}

void play_game(state_s *cur_state, char player) {
    int depth;
    pthread_t man_thread;
    state_s *new_state = NULL;

    search_type search = get_search_type(cur_state, player);

    // The game loop
    valid_moves(cur_state, search); // Create all children for current state
    while (!check_game_over(cur_state)) {
        manager.top_move = cur_state;
        // start timer
        if (pthread_create(&man_thread, NULL, move_timer, NULL)) {
            perror("pthread_create");
            // free up memory
            return;
        }

        depth = 0;
        while (!manager.stop) {
            // minmax
            depth++;
        }

        // clean up thread
        pthread_join(man_thread, NULL);

        // free space

        // get move

        break;
    }
    free_model(cur_state);

    return;
}

int main(int argc, char **argv) {
    char *filename;
    char player;
    state_s *start_state;
    int c;

    init_manager();

    while ((c = getopt(argc, argv, "g:vh")) != -1) {
        switch (c) {
            case 'v':
                verbosity++;
                break;
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'g':
                set_manager_heuristic(atoi(optarg));
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (argc - optind != 2) {
        print_usage(argv[0]);
        return 1;
    }

    filename = argv[optind];
    player = argv[optind + 1][0];

    start_state = read_input(filename);
    if (start_state == NULL) {
        fprintf(stderr, "Error parsing text file\n");
        return 1;
    }

    play_game(start_state, player);

    return 0;
}
