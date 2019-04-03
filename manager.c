/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 27, 19
 * File: manager.h
 * Description: Header file for game manager.
 */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

#include "manager.h"
#include "heuristic.h"
#include "state.h"

#define MICROSECOND 1000
#define SECOND      1000 * (MICROSECOND)
#define SLEEP_TIME  9.5 * (SECOND)

manager_s manager;

void init_manager() {
    manager.heuristic = num_moves_diff;
    manager.stop = 0;
    manager.top_move = NULL;

    manager.explored = 0;
    manager.created = 0;

    manager.top_move_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void set_manager_heuristic(int heuristic) {
    switch (heuristic) {
        case 1:
            manager.heuristic = num_moves_diff;
            break;
        case 2:
            manager.heuristic = num_stones_diff;
            break;
        case 3:
            manager.heuristic = combined;
            break;
        default:
            manager.heuristic = num_moves_diff;
    }
}

int setup_manager_timer(state_s *top_move) {
    if (top_move == NULL)
        return 0;

    pthread_mutex_lock(&(manager.top_move_mutex));

    manager.top_move = top_move;

    pthread_mutex_unlock(&(manager.top_move_mutex));

    manager.stop = 0;

    return 1;
}

void *move_timer(__attribute__((unused)) void *_) {
    //state_s *best_state;
    if (usleep(SLEEP_TIME) == -1) {
        // handle error
        perror("usleep");
    }

    // stop search
    manager.stop = 1;

    // print move
    pthread_mutex_lock(&(manager.top_move_mutex));

    //best_state = best_move(manager.top_move);
    //print_move(best_state);

    pthread_mutex_unlock(&(manager.top_move_mutex));

    return NULL;
}
