/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 11, 19
 * File: model.c
 * Description: Model and state space.
 */

#include <stdlib.h>

#include "model.h"

model_s *init_model(model_s *parent) {
    model_s *model = malloc(sizeof(model_s));
    if (model == NULL)
        return NULL;

    // eval

    model->parent = parent;

    model->num_children = 0;
    model->children = NULL;

    return model;
}

void free_model(model_s *model) {
    if (model == NULL)
        return;

    free(model->children);
    free(model);
}

