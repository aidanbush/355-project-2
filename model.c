/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 11, 19
 * File: model.c
 * Description: Model and state space.
 */

#include <stdlib.h>
#include <assert.h>

#include "model.h"

model_s *init_model(model_s *parent) {
    model_s *model = malloc(sizeof(model_s));
    if (model == NULL)
        return NULL;

    model->eval = 0;// eval

    model->parent = parent;

    model->cur_children = 0;
    model->children_size = 0;
    model->children = NULL;

    return model;
}

void free_model(model_s *model) {
    if (model == NULL)
        return;

    free(model->children);
    free(model);
}

int init_children(model_s *model, int size) {
    if (model == NULL || size == 0 || model->children != NULL)
        return 0;

    model->children = malloc(sizeof(model_s *) * size);
    if (model->children == NULL)
        return 0;

    for (int i = 0; i < size; i++)
        model->children[i] = NULL;

    model->children_size = size;

    return 1;
}

int add_child(model_s *parent, model_s *child) {
    if (parent == NULL || child == NULL)
        return 0;

    if (parent->cur_children +1 >= parent->children_size)
        return 0;

    parent->children[parent->cur_children] = child;
    parent->cur_children++;

    return 1;
}

// tests
int main() {
    model_s *model = init_model(NULL);

    free_model(model);
    return 0;
}
