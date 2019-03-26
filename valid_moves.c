/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 24, 19
 * File: valid_moves.c
 * Description: generates the valid moves for a given state based off a colour of stone.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"

/*Helper function to initialize a new state with the same layout as the current state*/
void copy_state(uint8_t temp[BOARD_SIZE][BOARD_SIZE], state_s *cur_state)
{
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
  {
    for (j = 0; j < BOARD_SIZE; j++)
    {
      temp[i][j] = cur_state->board[i][j];
    }
  }
}

/*Determines every possible state for the given move_set. The move_set is an identifier
* for which stone we will be generating the moves for
*/
void valid_moves(state_s *cur_state, search_type move_set)
{
  int i, j;
  int err;
  state_s *child;
  char search_char; //whether we are looking for the available moves for white or black
  //allocate memory
  uint8_t temp_state[BOARD_SIZE][BOARD_SIZE];
  //assign a temporary state with the current state
  copy_state(temp_state, cur_state);

  //Restricted set of possible moves made for initial move
  if (move_set == INIT_BLACK)
  {
    copy_state(temp_state, cur_state);
    temp_state[3][3] = EMPTY_SPACE;
    copy_state(temp_state, cur_state);
    temp_state[4][4] = EMPTY_SPACE;
  }

  if (move_set == INIT_WHITE)
  {
    copy_state(temp_state, cur_state);
    temp_state[3][4] = EMPTY_SPACE;
    copy_state(temp_state, cur_state);
    temp_state[4][3] = EMPTY_SPACE;
  }
  //assign which colour of stone we are evaluating based off of
  if (move_set == SEARCH_BLACK)
  {
    search_char = STONE_BLACK;
  }
  else
  {
    search_char = STONE_WHITE;
  }

  //Search through state for possible moves based off search_char
  copy_state(temp_state, cur_state);
  for (i = 0; i < BOARD_SIZE; i++)
  {
    for (j = 0; j < BOARD_SIZE; j++)
    {
      //Evaluate based on search_char
      if (temp_state[i][j] == search_char)
      {
        //Ensure we dont exceed the bounds of the array
        if ((i + 2 < BOARD_SIZE))
        {
          //ensure the adjacent space is not empty
          if (temp_state[i + 1][j] != EMPTY_SPACE)
          {
            //check target space if its empty
            if (temp_state[i + 2][j] == EMPTY_SPACE)
            {
              //display the resulting move
              temp_state[i + 2][j] = search_char;
              temp_state[i][j] = EMPTY_SPACE; //remove the oppositions stone
              temp_state[i + 1][j] = EMPTY_SPACE;
              child = init_model(cur_state, temp_state);
              copy_state(temp_state, cur_state);
              if (child == NULL)
              {
                perror("Error: failure to init child");
                return;
              }
              err = add_child(cur_state, child);
              if (err == 0)
              {
                perror("Error: failure to add child line127");
                return;
              }
              //check for double move
              if ((i + 4 < BOARD_SIZE))
              {
                if (temp_state[i + 3][j] != EMPTY_SPACE)
                {
                  if (temp_state[i + 4][j] == EMPTY_SPACE)
                  {
                    temp_state[i + 4][j] = search_char;
                    temp_state[i + 2][j] = EMPTY_SPACE;
                    temp_state[i + 3][j] = EMPTY_SPACE;
                    child = init_model(cur_state, temp_state);
                    copy_state(temp_state, cur_state);
                    if (child == NULL)
                    {
                      perror("Error: failure to init child");
                      return;
                    }
                    err = add_child(cur_state, child);
                    if (err == 0)
                    {
                      perror("Error: failure to add child line150");
                      return;
                    }
                  }
                }
              }
            }
          }
          //check up
          if (i - 2 > 0)
          {
            if (temp_state[i - 1][j] != EMPTY_SPACE)
            {
              if (temp_state[i - 2][j] == EMPTY_SPACE)
              {
                copy_state(temp_state, cur_state);
                temp_state[i - 2][j] = search_char;
                temp_state[i][j] = EMPTY_SPACE;
                temp_state[i - 1][j];
                child = init_model(cur_state, temp_state);
                copy_state(temp_state, cur_state);
                if (child == NULL)
                {
                  perror("Error: failure to init child");
                  return;
                }
                err = add_child(cur_state, child);
                if (err == 0)
                {
                  perror("Error: failure to add child line179");
                  return;
                }
                  if ((i - 4 > 0))
                  {
                    if (temp_state[i - 3][j] != EMPTY_SPACE)
                    {
                      if (temp_state[i - 4][j] == EMPTY_SPACE)
                      {
                        temp_state[i - 4][j] = search_char;
                        temp_state[i - 2][j] = EMPTY_SPACE;
                        temp_state[i - 3][j] = EMPTY_SPACE;
                        child = init_model(cur_state, temp_state);
                        copy_state(temp_state, cur_state);
                        if (child == NULL)
                        {
                          perror("Error: failure to init child");
                          return;
                        }
                        err = add_child(cur_state, child);
                        if (err == 0)
                        {
                          perror("Error: failure to add child line201");
                          return;
                        }                      
                      }
                    }
                  }
                }
              }

              //check right
              if (j + 2 < BOARD_SIZE)
              {
                if (temp_state[i][j + 1] != EMPTY_SPACE)
                {
                  if (temp_state[i][j + 2] == EMPTY_SPACE)
                  {
                    temp_state[i][j + 2] = search_char;
                    temp_state[i][j] = EMPTY_SPACE;
                    temp_state[i][j + 1] = EMPTY_SPACE;
                    child = init_model(cur_state, temp_state);
                    copy_state(temp_state, cur_state);
                    if (child == NULL)
                    {
                      perror("Error: failure to init child");
                      return;
                    }
                    err = add_child(cur_state, child);
                    if (err == 0)
                    {
                      perror("Error: failure to add child line230");
                      return;
                    }
                    if ((j + 4 < BOARD_SIZE))
                    {
                      if (temp_state[i][j + 3] != EMPTY_SPACE)
                      {
                        if (temp_state[i][j + 4] == EMPTY_SPACE)
                        {
                          temp_state[i][j + 4] = search_char;
                          temp_state[i][j + 2] = EMPTY_SPACE;
                          temp_state[i][j + 3] = EMPTY_SPACE;
                          child = init_model(cur_state, temp_state);
                          copy_state(temp_state, cur_state);
                          if (child == NULL)
                          {
                            perror("Error: failure to init child");
                            return;
                          }
                          err = add_child(cur_state, child);
                          if (err == 0)
                          {
                            perror("Error: failure to add child line 252");
                            return;
                          }
                        }
                      }
                    }
                  }
                }
              }

              //check left
              if (j - 2 > 0)
              {
                if (temp_state[i][j - 1] != EMPTY_SPACE)
                {
                  if (temp_state[i][j - 2] == EMPTY_SPACE)
                  {
                    temp_state[i][j - 2] = search_char;
                    temp_state[i][j] = EMPTY_SPACE;
                    temp_state[i][j - 1] = EMPTY_SPACE;
                    child = init_model(cur_state, temp_state);
                    copy_state(temp_state, cur_state);
                    if (child == NULL)
                    {
                      perror("Error: failure to init child");
                      return;
                    }
                    err = add_child(cur_state, child);
                    if (err == 0)
                    {
                      perror("Error: failure to add child line282");
                      return;
                    }
                    if ((j - 4 > 0))
                    {
                      if (temp_state[i][j - 3] != EMPTY_SPACE)
                      {
                        if (temp_state[i][j - 4] == EMPTY_SPACE)
                        {
                          temp_state[i][j - 4] = search_char;
                          temp_state[i][j - 2] = EMPTY_SPACE;
                          temp_state[i][j - 3] = EMPTY_SPACE;
                          child = init_model(cur_state, temp_state);
                          copy_state(temp_state, cur_state);
                          if (child == NULL)
                          {
                            perror("Error: failure to init child");
                            return;
                          }
                          err = add_child(cur_state, child);
                          if (err == 0)
                          {
                            perror("Error: failure to add child line304");
                            return;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
