/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 22, 19
 * File: model.h
 * Description: Header file for the minmax search.
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "minmax.h"
#include "heuristic.h"
#include "state.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


int max_value(state_s *state, int alpha, int beta, state_s *selected_state, int depth) {
    selected_state = NULL;
    state_s *best_state = malloc(sizeof(state_s));
    if (best_state == NULL){
        fprintf(stderr, "Error Allocating best_state");
    }
    valid_moves(state, SEARCH_BLACK);
    if (state == NULL)
        return NEG_INF;

    if (depth == 0) { //OR time restriction met
        return num_moves_diff(state->board);
    }

    int v = NEG_INF;
    for (int i = 0; i < state->cur_size; i++) {
        v = MAX(v, min_value(state->children[i], alpha, beta, selected_state, depth - 1));
        best_state = state->children[i];
        alpha = MAX(alpha, v);
        if (alpha >= beta) {
            break; //beta cutoff
        }
    }
    selected_state = best_state;
    print_move(selected_state);
    printf("\n");
    print_state(selected_state);
    return v;
}

int min_value(state_s *state, int alpha, int beta, state_s *selected_state, int depth) {
    selected_state = NULL;
    state_s *best_state = malloc(sizeof(state_s*));
    int heur;
    if (best_state == NULL){
        fprintf(stderr, "Error Allocating best_state");
    }
    valid_moves(state, SEARCH_WHITE);
    if (state == NULL)
        return POS_INF;

    if (depth == 0) {
        return num_moves_diff(state->board);
    }

    int v = POS_INF;

    for (int i = 0; i < state->cur_size; i++) {
        v = MIN(v, max_value(state->children[i], alpha, beta, selected_state, depth - 1));
        best_state = state->children[i]; 
        beta = MIN(beta, v);
        if (alpha >= beta)
            break;
    }
    selected_state = best_state;
    print_move(selected_state);
    printf("\n");
    print_state(selected_state);
    return v;
}

state_s *minmax(state_s *state, int depth) {
    state_s *best_state = malloc(sizeof(state_s));
    if (best_state == NULL){
        fprintf(stderr, "Error Allocating best_state");
    }
    max_value(state, POS_INF, NEG_INF, best_state, depth);
    printf("Chosen State: \n");
    print_state(best_state);
    return best_state;
}
