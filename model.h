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

#define BOARD_SIZE      8
#define SQUARE_BLACK    0
#define SQUARE_WHITE    1
#define SQUARE_EMPTY    2

typedef struct model_s {
    uint8_t state[BOARD_SIZE][BOARD_SIZE];
    int eval;
    int cur_children;
    int children_size;
    struct model_s *parent;
    struct model_s **children;
} model_s;

model_s *init_model();

void free_model(model_s *model);

#endif /* MODEL_H */
