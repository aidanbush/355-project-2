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

#define DEFAULT_CHILD_SIZE  24

model_s *init_model(model_s *parent) {
    model_s *model = malloc(sizeof(model_s));
    if (model == NULL)
        return NULL;

    model->eval = 0;// eval

    model->parent = parent;

    model->cur_size = 0;
    model->max_size = 0;
    model->children = NULL;

    return model;
}

void free_model(model_s *model) {
    if (model == NULL)
        return;

    if (model->children != NULL)
        for (int i = 0; i < model->cur_size; i++)
            free_model(model->children[i]);

    free(model->children);
    free(model);
}

static int resize_children(model_s *model) {
    int new_size;
    model_s **tmp;

    if (model->max_size == 0) {
        new_size = DEFAULT_CHILD_SIZE;
        model->children = malloc(sizeof(model_s*) * new_size);
        if (model->children == NULL)
            return 0;

    } else {
        new_size = model->max_size * 2;
        tmp = realloc(model->children, sizeof(model_s*) * new_size);
        if (tmp == NULL)
            return 0;

        model->children = tmp;
    }

    for (int i = model->cur_size; i < new_size; i++)
        model->children[i] = NULL;

    model->max_size = new_size;
    return 1;
}

int add_child(model_s *parent, model_s *child) {
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
    model_s *model = init_model(NULL);
    model_s *child;

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
