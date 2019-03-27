/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 11, 19
 * File: model.c
 * Description: Model and state space.
 */

#include <stdlib.h>

#ifdef _TEST_MODEL
#include <assert.h>
#endif /* _TEST_MODEL */

#include "state.h"

#define DEFAULT_CHILD_SIZE  24

state_s *init_model(state_s *parent, uint8_t current[BOARD_SIZE][BOARD_SIZE]) {
    state_s *model = malloc(sizeof(state_s));
    if (model == NULL)
        return NULL;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            model->board[i][j] = current[i][j];
        }
    }
    model->eval = 0;// eval

    // move
    model->move.row = -1;
    model->move.col = -1;
    model->move.direction = MOVE_NONE;
    model->move.hops = 0;

    // set player
    model->player = PLAYER_NONE;
    // set num moves
    model->num_moves = -1;

    model->parent = parent;

    model->cur_size = 0;
    model->max_size = 0;
    model->children = NULL;

    return model;
}

/*Helper function to print a given state*/
void print_state(uint8_t state[BOARD_SIZE][BOARD_SIZE]) {
  int i, j;
  printf("\n   ");
  for (i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", i);
  }
  printf("\n   ");
  for (i = 0; i < BOARD_SIZE; i++) {
    printf("- ");
  }
  printf("\n");
  for (i = 0; i < BOARD_SIZE; i++) {
    printf("%d |", i);
    for (j = 0; j < BOARD_SIZE; j++) {
      printf("%c ", state[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void free_model(state_s *model) {
    if (model == NULL)
        return;

    if (model->children != NULL)
        for (int i = 0; i < model->cur_size; i++)
            free_model(model->children[i]);

    free(model->children);
    free(model);
}

static int resize_children(state_s *model) {
    int new_size;
    state_s **tmp;

    if (model->max_size == 0) {
        new_size = DEFAULT_CHILD_SIZE;
        model->children = malloc(sizeof(state_s*) * new_size);
        if (model->children == NULL)
            return 0;

    } else {
        new_size = model->max_size * 2;
        tmp = realloc(model->children, sizeof(state_s*) * new_size);
        if (tmp == NULL)
            return 0;

        model->children = tmp;
    }

    for (int i = model->cur_size; i < new_size; i++)
        model->children[i] = NULL;

    model->max_size = new_size;
    return 1;
}

int add_child(state_s *parent, state_s *child) {
    if (parent == NULL || child == NULL)
        return 0;

    // check resize
    if (parent->cur_size >= parent->max_size)
        if (!resize_children(parent))
            return 0;

    parent->children[parent->cur_size] = child;
    parent->cur_size++;

    return 1;
}

// tests
#ifdef _TEST_MODEL
int main() {
    state_s *model = init_model(NULL);
    state_s *child;

    assert(model->cur_size == 0);
    assert(model->max_size == 0);
    assert(model->parent == NULL);
    assert(model->children == NULL);

    for (int i = 0; i < DEFAULT_CHILD_SIZE*3/2; i++) {
        child = init_model(model);

        assert(add_child(model, child) == 1);
        assert(child == model->children[model->cur_size - 1]);
    }

    free_model(model);
    return 0;
}
#endif /* _TEST_MODEL */
