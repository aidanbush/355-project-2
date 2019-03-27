/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * File: difference_heuristic.h
 * Description: Header file for difference heuristic
 */

#ifndef DIFFERENCE_HEURISTIC_H
#define DIFFERENCE_HEURISTIC_H

typedef enum
{
    INIT_BLACK,
    INIT_WHITE,
    SEARCH_BLACK,
    SEARCH_WHITE,
} search_type;

//calculates the difference heuristic
int difference(char **cur_state, search_type move_set);

#endif /* DIFFERENCE_HEURISTIC_H */
