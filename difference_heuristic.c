/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 24, 19
 * File: difference_heuristic.c
 * Description: counts the available moves for black and white and takes the difference for our heuristic value.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 8
#define MAX_COL 8
#define STONE_BLACK 'B'
#define STONE_WHITE 'W'
#define EMPTY_SPACE 'O'

typedef enum
{
    INIT_BLACK,
    INIT_WHITE,
    SEARCH_BLACK,
    SEARCH_WHITE,
} search_type;

int difference(char **cur_state, search_type move_set)
{
    int i, j, count = 0;
    char search_char;

    //decide which stone we are counting the moves for
    if (move_set == SEARCH_BLACK)
    {
        search_char = STONE_BLACK;
    }
    else
    {
        search_char = STONE_WHITE;
    }

    //Search through state for possible moves based off search_char
    for (i = 0; i < MAX_ROW; i++)
    {
        for (j = 0; j < MAX_COL; j++)
        {
            //Evaluate if we find our search character
            if (cur_state[i][j] == search_char)
            {
                //make sure we dont check outside of the array bounds
                //check down
                if ((i + 2 < MAX_ROW))
                {
                    //check adjacent to the piece to make sure it isnt empty
                    if (cur_state[i + 1][j] != EMPTY_SPACE)
                    {
                        //check if target space is empty
                        if (cur_state[i + 2][j] == EMPTY_SPACE)
                        {
                            count++;
                            //similar logic for a double move
                            if ((i + 4 < MAX_ROW))
                            {
                                if (cur_state[i + 3][j] != EMPTY_SPACE)
                                {
                                    if (cur_state[i + 4][j] == EMPTY_SPACE)
                                    {
                                        count++;
                                    }
                                }
                            }
                        }
                    }
                }
                //check up
                if (i - 2 > 0)
                {
                    if (cur_state[i - 1][j] != EMPTY_SPACE)
                    {
                        if (cur_state[i - 2][j] == EMPTY_SPACE)
                        {
                            count++;
                            if ((i - 4 > 0))
                            {
                                if (cur_state[i - 3][j] != EMPTY_SPACE)
                                {
                                    if (cur_state[i - 4][j] == EMPTY_SPACE)
                                    {
                                        count++;
                                    }
                                }
                            }
                        }
                    }
                }

                //check right
                if (j + 2 < MAX_COL)
                {
                    if (cur_state[i][j + 1] != EMPTY_SPACE)
                    {
                        if (cur_state[i][j + 2] == EMPTY_SPACE)
                        {
                            count++;
                            if ((j + 4 < MAX_COL))
                            {
                                if (cur_state[i][j + 3] != EMPTY_SPACE)
                                {
                                    if (cur_state[i][j + 4] == EMPTY_SPACE)
                                    {
                                        count++;
                                    }
                                }
                            }
                        }
                    }
                }

                //check left
                if (j - 2 > 0)
                {
                    if (cur_state[i][j - 1] != EMPTY_SPACE)
                    {
                        if (cur_state[i][j - 2] == EMPTY_SPACE)
                        {
                            count++;
                            if (j - 4 > 0)
                            {
                                if (cur_state[i][j - 3] != EMPTY_SPACE)
                                {
                                    if (cur_state[i][j - 4] == EMPTY_SPACE)
                                    {
                                        count++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //after counting white we need to subtract it from the count for black
    if (move_set == SEARCH_WHITE)
    {
        return difference(cur_state, SEARCH_BLACK) - count;
    }
    else
    {
        return count;
    }
}