/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 27, 19
 * File: manager.h
 * Description: Header file for game manager.
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "heuristic.h"
#include "state.h"

typedef struct manager_s {
    heur_func heuristic;
    int stop;
    state_s *top_move;
    pthread_mutex_t top_move_mutex;
    int explored;
    int created;
} manager_s;

void init_manager();

void set_manager_heuristic(int heuristic);

void *move_timer(__attribute__((unused)) void *_);

int setup_manager_timer(state_s *top_move);

#endif /* MANAGER_H */
