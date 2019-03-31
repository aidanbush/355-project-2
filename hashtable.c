/* Author: Aidan Bush, David Dowie, Ben Ha
 * Project: Konane puzzle
 * Course: CMPT 355
 * Date: Mar. 31, 19
 * File: hashtable.h
 * Description: Hashtable header file for storing states.
 *  From Project 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "hashtable.h"
#include "state.h"

#define MAX_LOAD    0.70
#define RESIZE_RATE 4

// defined so it starts at the total size of a page
#define DEFAULT_HASHTABLE_SIZE  (sysconf(_SC_PAGESIZE) / sizeof(state_s **))

hashtable_s *init_hashtable(int size) {
    hashtable_s *table = malloc(sizeof(hashtable_s));
    if (table == NULL)
        return NULL;

    table->nodes = malloc(sizeof(state_s *) * size);
    if (table->nodes == NULL)
        return NULL;

    for (int i = 0; i < size; i++)
        table->nodes[i] = NULL;

    table->size = size;
    table->elements = 0;
    table->non_NULL = 0;

    return table;
}

void print_hashtable(hashtable_s *table) {
    if (table == NULL)
        return;

    for (int i = 0; i < table->size; i++)
        if (table->nodes[i] != NULL)
            print_state(table->nodes[i]);
}

static int search_hashtable_index(hashtable_s *table, state_s *state) {
    if (table == NULL || state == NULL)
        return -1;

    state_s *cur_node;
    int i = hash_state(state) % table->size;

    while ((cur_node = table->nodes[i]) != NULL) {
        if ((void *)cur_node != (void *)table)
            if (duplicate_state(state, cur_node))
                break;
        i = (i + 1) % table->size;
    }

    if (table->nodes[i] == NULL)
        return -1;

    return i;
}

/* search looks for the key and returns the bucket where it is located;
   returns NULL on failure */
state_s *search_hashtable(hashtable_s *table, state_s *state) {
    if (table == NULL || state == NULL)
        return NULL;

    int i = search_hashtable_index(table, state);

    if (i < 0)
        return NULL;

    return table->nodes[i];
}

int remove_hashtable(hashtable_s *table, state_s *state) {
    if (table == NULL || state == NULL)
        return 0;

    int i = search_hashtable_index(table, state);

    if (i < 0)
        return 0;

    state_s *node = table->nodes[i];

    if (node != NULL) {
        free_model(node);
        table->elements--;
        table->nodes[i] = (state_s *)table;
    }

    return 1;
}

/* table_rehash doubles the number of buckets and rehashes the values in the
   table; returns false on failure */
static int rehash_table(hashtable_s *table, int resize_rate) {
    if (table == NULL)
        return 0;

    state_s **new_nodes;
    state_s **old_nodes;
    int new_size, old_size;
    int old_elements;
    int old_non_NULL;

    new_size = table->size * resize_rate;

    new_nodes = malloc(sizeof(state_s *) * new_size);
    if (new_nodes == NULL) {
        fprintf(stderr, "rehash new_nodes == NULL\n");
        return 0;
    }

    for (int i = 0; i < new_size; i++)
        new_nodes[i] = NULL;

    old_nodes = table->nodes;
    table->nodes = new_nodes;

    old_size = table->size;
    table->size = new_size;

    old_elements = table->elements;
    table->elements = 0;

    old_non_NULL = table->non_NULL;
    table->non_NULL = 0;

    for (int i = 0; i < old_size; i++) {
        if (old_nodes[i] == NULL || (void *)old_nodes[i] == (void *)table)
            continue;

        if (!insert_hashtable(table, old_nodes[i])) {
            table->nodes = old_nodes;
            table->size = old_size;
            table->elements = old_elements;
            table->non_NULL = old_non_NULL;
            free(new_nodes);
            return 0;
        }
    }

    free(old_nodes);

    return 1;
}

int insert_hashtable(hashtable_s *table, state_s *node) {
    if (table == NULL || node == NULL) {
        return 0;
    }

    if ((table->elements + 1) / table->size >= MAX_LOAD)
        if (!rehash_table(table, RESIZE_RATE))
            return 0;

    if ((float)table->non_NULL / table->size >= MAX_LOAD)
        //rehash to same size
        if (!rehash_table(table, 1))
            return 0;

    int i = hash_state(node) % table->size;

    while (table->nodes[i] != NULL && (void *)table->nodes[i] != (void *)table) {
        if (duplicate_state(node, table->nodes[i])) {
            // TODO handle duplicate currently return code to not that it was a duplicate
            return 2;
        }
        i = (i + 1) % table->size;
    }

    if (table->nodes[i] == NULL)
        table->non_NULL++;

    table->nodes[i] = node;
    table->elements++;
    return 1;
}

void free_hashtable(hashtable_s *table) {
    if (table == NULL)
        return;

    for (int i = 0; i < table->size; i++)
        if (table->nodes[i] != NULL && (void *)table->nodes[i] != (void *)table)
            free_model(table->nodes[i]);

    free(table->nodes);
    free(table);
}
