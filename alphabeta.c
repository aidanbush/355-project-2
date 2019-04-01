#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "alphabeta.h"

int alpha_beta(state_s *state, int depth, int alpha, int beta, search_type search,state_s **selected_state) {
	int value;
	state_s *child;
	state_s *best;
	if (depth == 0) {
		return num_moves_diff(state->board);
	}
	if (state->cur_size == 0)
		valid_moves(state, search);

	if (search == SEARCH_BLACK) {
		value = NEG_INF;
		for (int i = 0; i < state->cur_size; i++) {
			child = state->children[i];
			best = child;
			value = MAX(value, alpha_beta(child, depth - 1, alpha, beta, SEARCH_WHITE, selected_state));
			alpha = MAX(alpha, value);
			if (alpha >= beta) {
				break;
			}
		}
		*selected_state = best;
		return value;
	} else {
		value = POS_INF;
		for (int i = 0; i < state->cur_size; i++) {
			child = state->children[i];
			best = child;
			value = MIN(value, alpha_beta(child, depth-1, alpha, beta, SEARCH_BLACK, selected_state));
			beta = MIN(beta, value);
			if (alpha >= beta) {
				break;
			}
		}
		*selected_state = best;
		return value;
	}
}

state_s *minmax(state_s *state, int depth, search_type search) {
	state_s *best_state = NULL;
	alpha_beta(state, depth, NEG_INF, POS_INF, search, &best_state);
	return best_state;
}