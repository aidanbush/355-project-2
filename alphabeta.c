/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 31, 19
 * File: alphabeta.c
 * Description: alpha beta algorithm implementation.
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "alphabeta.h"
#include "manager.h"
#include "valid_moves.h"
#include "state.h"

extern manager_s manager;

int alpha_beta(state_s *state, int depth, int alpha, int beta, search_type search) {
	int value;
	state_s *child;
	if (state->cur_size == 0)
		valid_moves(state, search);

	if (depth == 0 || manager.stop || state->cur_size == 0) {
		return state->eval;
	}

	if (search == SEARCH_BLACK) {
			value = NEG_INF;
			for (int i = 0; i < state->cur_size; i++) {
				child = state->children[i];
				value = MAX(value, alpha_beta(child, depth - 1, alpha, beta, SEARCH_WHITE));
				alpha = MAX(alpha, value);
				if (alpha >= beta) {
					break;
				}
			}
	} else if (search == SEARCH_WHITE) {
			value = POS_INF;
			for (int i = 0; i < state->cur_size; i++) {
				child = state->children[i];
				value = MIN(value, alpha_beta(child, depth-1, alpha, beta, SEARCH_BLACK));
				beta = MIN(beta, value);
				if (alpha >= beta) {
					break;
				}
			}
	} else if (search == INIT_BLACK) {
			value = NEG_INF;
			for (int i = 0; i < state->cur_size; i++) {
				child = state->children[i];
				value = MAX(value, alpha_beta(child, depth - 1, alpha, beta, INIT_WHITE));
				alpha = MAX(alpha, value);
				if (alpha >= beta) {
					break;
				}
			}
    } else {
			value = POS_INF;
			for (int i = 0; i < state->cur_size; i++) {
				child = state->children[i];
				value = MIN(value, alpha_beta(child, depth - 1, alpha, beta, SEARCH_BLACK));
				beta = MIN(beta, value);
				if (alpha >= beta) {
					break;
				}
			}
  	}
		state->eval = value;
		sort_children(state);
		return value;
}

void minmax(state_s *state, int depth, search_type search) {
	alpha_beta(state, depth, NEG_INF, POS_INF, search);
}
