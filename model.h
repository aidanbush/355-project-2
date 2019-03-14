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

#define BOARD_SIZE  8

typedef struct model_s {
    uint16_t state[BOARD_SIZE];
    int eval;
    struct model_s *parent;
    // children
} model_s;

model_s *init_model();

void free_model(model_s *model);

#endif /* MODEL_H */
