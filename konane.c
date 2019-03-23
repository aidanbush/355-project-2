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

int read_input(char *filename) {
    FILE *fp;
    uint8_t state[BOARD_SIZE][BOARD_SIZE];

    //1. Open file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error: Invalid file name.\n");
        return -0;
    }
    //2. Read file, convert "B" into 0, "W" into 1, "O" into 2, store it in state[][]
    int row = 0;
    int col = 0;
    char ch = getc(fp);
    while (ch != EOF) {
        if (ch == 'B') {
            state[row][col++] = 0;
        }
        else if (ch == 'W') {
            state[row][col++] = 1;
        }
        else if (ch == 'O') {
            state[row][col++] = 2;
        }
        else if (ch == '\n') {
            row++;
            col = 0;
        }
        ch = getc(fp);
    }
    // Test print
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            printf("%d", state[i][j]);
        }
        printf("\n");
    }
    return 1;
}

int main(int argc, char **argv) {
    // read input
    char *filename, *role;
    filename = argv[1];
    role = argv[2];
    if (!read_input(filename)) {
        fprintf(stderr, "Invalid text file");
        return 0;
    }

    // AB search

    // print move

    return 0;
}