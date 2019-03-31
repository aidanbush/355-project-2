/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 31, 19
 * File: hashtable.h
 * Description: Hashtable header file for storing states.
 *  From Project 1.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <unistd.h>

#include "state.h"

typedef struct hashtable_s {
    int size;
    int elements;
    int non_NULL;
    struct state_s **nodes;
} hashtable_s;

/* table_ create allocates a new hash table and returns a pointer to that table;
   returns NULL on failure */
hashtable_s *init_hashtable(int size);

/* table_print prints all the keys and values in the table */
void print_hashtable(hashtable_s *table);

/* table_search looks for and returns the value associated with the key;
   returns NULL on failure */
state_s *search_hashtable(hashtable_s *table, state_s *state);

/* table_remove removes the key and value pair; returns false on failure */
int remove_hashtable(hashtable_s *table, state_s *state);

/* Inserts node into the table if it is not a duplicate
 * returns 0 on failure, 1 on sucess, and 2 if a duplicate was found
 */
int insert_hashtable(hashtable_s *table, state_s *node);

/* frees table and all the nodes in it */
void free_hashtable(hashtable_s *table);

#endif /* HASHTABLE_H */
