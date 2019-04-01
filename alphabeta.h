#ifndef alphabeta_h
#define alphabet_h

#include "heuristic.h"
#include "state.h"
#include "valid_moves.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int alpha_beta(state_s *state, int depth, int alpha, int beta, search_type search, state_s **selected_state);
state_s *minmax(state_s *state, int depth, search_type search);

#endif /* alphabeta_H */