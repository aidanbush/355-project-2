/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 22, 19
 * File: model.h
 * Description: Header file for the minmax search.
 */

#include <stddef.h>

#include "minmax.h"
#include "state.h"

static int max_value(state_s *state, int alpha, int beta) {
    // if terminal  return utility

    // v = -inf

    // for action, new_state in successors
    //  v = max(v, min_value(state, alpha, beta))
    //  if v >= beta    return v
    //  alpha = max(alpha, v)

    // return v
    return 0;
}

static int min_value(state_s *state, int alpha, int beta) {
    // if terminal  return utility

    // v = +inf

    // for action, new_state in successors
    //  v = min(v, max_value(state, alpha, beta))
    //  if v <= alpha   return v
    //  beta = min(beta, v)

    // return v
    return 0;
}

state_s *minmax(state_s *state) {
    // v = max_value
    // return action associated with v
    return NULL;
}
