/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 17, 19
 * File: konane.c
 * Description: Main konane solving file.
 */

#include <stdio.h>
#include <stdlib.h>

#include "model.h"

model_s *read_input(char *filename) {
    FILE *file;
    int row = 0, col = 0;
    int ch, last = '\0';
    int err = 0;
    model_s *state;

    // create model
    state = init_model();
    if (state == NULL)
        return NULL;

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
                state->state[row][col++] = STONE_BLACK;
                break;
            case 'W':
                if (col >= BOARD_SIZE)
                    err = 1;
                state->state[row][col++] = STONE_WHITE;
                break;
            case 'O':
                if (col >= BOARD_SIZE)
                    err = 1;
                state->state[row][col++] = EMPTY_SPACE;
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

    if (err) {
        free_model(state);
        state = NULL;
    }

#ifdef _TEST_INPUT
    if (!err) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                printf("%c", state->state[i][j]);
            }
            printf("\n");
        }
    }
#endif /* _TEST_INPUT */

    fclose(file);
    return state;
}

int main(int argc, char **argv) {
    char *filename, *role;
    model_s *start_state;

    filename = argv[1];
    role = argv[2];

    start_state = read_input(filename);

    if (start_state == NULL) {
        fprintf(stderr, "Error parsing text file\n");
        return 1;
    }

    // AB search

    // print move

    free_model(start_state);

    return 0;
}
