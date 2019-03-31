/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 22, 19
 * File: model.h
 * Description: Header file for the minmax search.
 */

#ifndef MINMAX_H
#define MINMAX_H

#include "state.h"

int max_value(state_s *state, int alpha, int beta, state_s **selected_state, int depth);

int min_value(state_s *state, int alpha, int beta, state_s **selected_state, int depth);

state_s *minmax(state_s *state, int depth);

#endif /* MINMAX_H */
