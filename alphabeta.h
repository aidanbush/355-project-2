#ifndef alphabeta_h
#define alphabet_h

#include "state.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int alpha_beta(state_s *state, int depth, int alpha, int beta, search_type search);
void minmax(state_s *state, int depth, search_type search);

#endif /* alphabeta_H */