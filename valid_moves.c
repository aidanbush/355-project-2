/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 24, 19
 * File: valid_moves.c
 * Description: generates the valid moves for a given state based off a colour of stone.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "state.h"

/*Helper function to initialize a new state with the same layout as the current state*/
void copy_state(uint8_t temp[BOARD_SIZE][BOARD_SIZE], state_s *cur_state) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < BOARD_SIZE; j++) {
      temp[i][j] = cur_state->board[i][j];
    }
  }
}

/*Determines every possible state for the given move_set. The move_set is an identifier
* for which stone we will be generating the moves for
*/
void valid_moves(state_s *cur_state, search_type move_set) {
  int row, col, dist, err;
  bool found_move = false, multi = false;
  state_s *child;
  char search_char; //whether we are looking for the available moves for white or black
  //allocate memory
  uint8_t temp_state[BOARD_SIZE][BOARD_SIZE];
  //assign a temporary state with the current state
  copy_state(temp_state, cur_state);

  //Restricted set of possible moves made for initial move
  if (move_set == INIT_BLACK) {
    temp_state[3][3] = EMPTY_SPACE;
    child = init_model(cur_state, temp_state);
    if (child == NULL) {
      perror("Error: failure to init child");
      return;
    }
    err = add_child(cur_state, child);
    if (err == 0) {
      perror("Error: failure to add child");
      return;
    }
    copy_state(temp_state, cur_state);
    temp_state[4][4] = EMPTY_SPACE;
    child = init_model(cur_state, temp_state);
    if (child == NULL) {
      perror("Error: failure to init child");
      return;
    }
    err = add_child(cur_state, child);
    if (err == 0) {
      perror("Error: failure to add child");
      return;
    }
    return;
  }

  if (move_set == INIT_WHITE) {
    temp_state[3][4] = EMPTY_SPACE;
    child = init_model(cur_state, temp_state);
    if (child == NULL) {
      perror("Error: failure to init child");
      return;
    }
    err = add_child(cur_state, child);
    if (err == 0) {
      perror("Error: failure to add child");
      return;
    }
    copy_state(temp_state, cur_state);
    temp_state[4][3] = EMPTY_SPACE;
    child = init_model(cur_state, temp_state);
    if (child == NULL) {
      perror("Error: failure to init child");
      return;
    }
    err = add_child(cur_state, child);
    if (err == 0) {
      perror("Error: failure to add child");
      return;
    }
    return;
  }
  //assign which colour of stone we are evaluating based off of
  if (move_set == SEARCH_BLACK) {
    search_char = STONE_BLACK;
  }
  else {
    search_char = STONE_WHITE;
  }

  //Search through state for possible moves based off search_char
  //row
  for (int i = 0; i < BOARD_SIZE; i++)  {
    row = i;
    //col
    for (int j = 0; j < BOARD_SIZE / 2; j++) {
      if (row % 2 == 0) {
        if (search_char == STONE_BLACK) {
          col = j * 2;
        }
          else {
            col = j * 2 + 1;
          }
      }
      else
      {
        if (search_char == STONE_BLACK) {
          col = j * 2 + 1;
        }
        else {
          col = j * 2;
        }
      }

      //down
      dist = 1;
      while ((row + 2 * dist) < BOARD_SIZE) {
        if ((temp_state[row][col] == EMPTY_SPACE && multi == false) ||
            temp_state[row + dist * 2 - 1][col] == EMPTY_SPACE ||
            temp_state[row + dist * 2][col] != EMPTY_SPACE) {
          break;
        }
        temp_state[row + dist * 2][col] = search_char;
        temp_state[row + dist * 2 - 2][col] = EMPTY_SPACE; //remove the oppositions stone
        temp_state[row + dist * 2 - 1][col] = EMPTY_SPACE;
        child = init_model(cur_state, temp_state);
        if (child == NULL) {
          perror("Error: failure to init child");
          return;
        }
        err = add_child(cur_state, child);
        if (err == 0) {
          perror("Error: failure to add child");
          return;
        }
        found_move = true;
        dist++;
        multi = true;
      }
      if (found_move == true) {
        copy_state(temp_state, cur_state);
        found_move = false;
      }

      // up
      multi = false;
      dist = 1;
      while ((row - 2 * dist) > 0) {
        if ((temp_state[row][col] == EMPTY_SPACE && multi == false) ||
            temp_state[row - dist * 2 + 1][col] == EMPTY_SPACE ||
            temp_state[row - dist * 2][col] != EMPTY_SPACE) {
          break;
        }
        temp_state[row - dist * 2][col] = search_char;
        temp_state[row - dist * 2 + 2][col] = EMPTY_SPACE;
        temp_state[row - dist * 2 + 1][col] = EMPTY_SPACE;
        child = init_model(cur_state, temp_state);
        if (child == NULL) {
          perror("Error: failure to init child");
          return;
        }
        err = add_child(cur_state, child);
        if (err == 0) {
          perror("Error: failure to add child");
          return;
        }
        found_move = true;
        dist++;
        multi = true;
      }

      if (found_move == true) {
        copy_state(temp_state, cur_state);
        found_move = false;
      }
      
      // right
      multi = false;
      dist = 1;
      while ((col + 2 * dist) < BOARD_SIZE) {
        if ((temp_state[row][col] == EMPTY_SPACE && multi == false) ||
            temp_state[row][col + dist * 2 - 1] == EMPTY_SPACE ||
            temp_state[row][col + dist * 2] != EMPTY_SPACE) {
          break;
        }
        temp_state[row][col + dist * 2] = search_char;
        temp_state[row][col + dist * 2 - 1] = EMPTY_SPACE;
        temp_state[row][col + dist * 2 - 2] = EMPTY_SPACE;
        child = init_model(cur_state, temp_state);
        if (child == NULL)  {
          perror("Error: failure to init child");
          return;
        }
        err = add_child(cur_state, child);
        if (err == 0) {
          perror("Error: failure to add child");
          return;
        }
        found_move = true;
        dist++;
        multi = true;
      }

      if (found_move == true) {
        copy_state(temp_state, cur_state);
        found_move = false;
      }
      
      // left
      dist = 1;
      multi = false;
      while ((col - 2 * dist) > 0) {
        if ((temp_state[row][col] == EMPTY_SPACE && multi == false) ||
            temp_state[row][col - dist * 2 + 1] == EMPTY_SPACE ||
            temp_state[row][col - dist * 2] != EMPTY_SPACE) {
          break;
        }
        temp_state[row][col - dist * 2] = search_char;
        temp_state[row][col - dist * 2 + 2] = EMPTY_SPACE;
        temp_state[row][col - dist * 2 + 1] = EMPTY_SPACE;
        child = init_model(cur_state, temp_state);
        if (child == NULL) {
          perror("Error: failure to init child");
          return;
        }
        err = add_child(cur_state, child);
        if (err == 0) {
          perror("Error: failure to add child");
          return;
        }
        found_move = true;
        dist++;
        multi = true;
      }
     }
  }
}
