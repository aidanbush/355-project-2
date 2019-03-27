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

int main(int argc, char **argv) {
    char *filename;
    char value[5];
    uint8_t player_type;
    search_type search;
    state_s *start_state;

    filename = argv[1];
    player_type = argv[2][0];
    start_state = read_input(filename);
    search = get_search_type(start_state, player_type);
    if (argc < 3) {
        fprintf(stderr,"Too Few Arguments\n");
        return 1;
    }
    if (start_state == NULL) {
        fprintf(stderr, "Error parsing text file\n");
        return 1;
    }
    valid_moves(start_state, search);
    for (int i = 0; i < start_state->cur_size; i++) {
        printf("Starting State:\n\n");
        print_state(start_state);
        print_move(start_state->children[i]);
        print_state(start_state->children[i]);
    }

    while(strcmp(value,"quit") != 0) {
        printf("Enter Next Move: ");
        scanf("%s", value);
        printf("Desired move: %s\n", value);
    }
    
    // print move
    free_model(start_state);

    return 0;
}
