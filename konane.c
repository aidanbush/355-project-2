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

int main(int argc, char **argv) {
    FILE *fp;
    uint8_t state[BOARD_SIZE][BOARD_SIZE];

    // read input
    // Input syntax: ./konane filename B/W
    if (argc != 3) {
        perror("Error: Invalid command line input.\n");
        return -1;
    }
    else {
        //1. Open file
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("Error: Invalid file name.\n");
            return -2;
        }
        //2. Read file, convert "B" into 0, "W" into 1, "O" into 2, store it in state[][]
        else {
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
        }
        //3. Assign role for agent
        char role = *argv[2];
        // Test print
        printf("Role: %c\n", role);
    }

    // AB search

    // print move

    return 0;
}
