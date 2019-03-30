/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 22, 19
 * File: model.h
 * Description: Header file for the minmax search.
 */

#include <stddef.h>

#include "minmax.h"
#include "heuristic.h"
#include "state.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


static int max_value(state_s *state, int alpha, int beta, state_s **selected_state) {
    selected_state = NULL;
    if (state == NULL)
        return NEG_INF;

    if (state->children == NULL) { //OR time restriction met
        return num_moves_diff(state->board);
    }

    int v = NEG_INF;
    state_s *best_state = NULL;

    for (int i = 0; i < state->cur_size; i++) {
        v = MAX(v, min_value(state->children[i], alpha, beta, &best_state));
        *selected_state = state->children[i];

        if (v >= beta)
            return v;

        alpha = MAX(alpha, v);
    }
    return v;
}

static int min_value(state_s *state, int alpha, int beta, state_s **selected_state) {
    selected_state = NULL;
    if (state == NULL)
        return POS_INF;

    if (state->children == NULL) { //OR time restriction met
        return num_moves_diff(state->board);
    }

    int v = POS_INF;
    state_s *best_state = NULL;

    for (int i = 0; i < state->cur_size; i++) {
        v = MIN(v, max_value(state->children[i], alpha, beta, &best_state));
        *selected_state = state->children[i];

        if (v <= alpha)
            return v;
        beta = MIN(beta, v);
    }

    return v;
}

state_s *minmax(state_s *state) {
    int v = max_value(state, NEG_INF, POS_INF);

    // return action associated with v
    return NULL;
}
