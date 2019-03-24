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
            //Evaluate based on search_char
            if (cur_state[i][j] == search_char)
            {
                //check down
                if ((i + 2 < MAX_ROW))
                {
                    if (cur_state[i + 1][j] != EMPTY_SPACE)
                    {
                        if (cur_state[i + 2][j] == EMPTY_SPACE)
                        {
                            count++;
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
                                        count++
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
                            count++ if ((j - 4 > 0))
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
    if(move_set == SEARCH_WHITE){
        return difference(SEARCH_BLACK) - count;
    }
    else{
        return count;
    }
}