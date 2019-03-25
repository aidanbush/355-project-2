/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 11, 19
 * File: model.h
 * Description: Header file for model.
 */

#ifndef MODEL_H
#define MODEL_H

#include <stdint.h>
#include <limits.h>

#define BOARD_SIZE  8

#define NEG_INF (INT_MAX)
#define POS_INT (INT_MIN)

typedef struct model_s {
    uint16_t state[BOARD_SIZE];
    int eval;
    int num_children;
    struct model_s *parent;
    struct model_s **children;
} model_s;

model_s *init_model();

void free_model(model_s *model);

#endif /* MODEL_H */
