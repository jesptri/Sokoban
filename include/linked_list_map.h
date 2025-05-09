/**
 * @file linked_list_int_fun.h
 *
 * @brief Simple definition of linked list containing `int` values
 *
 * This is a simple definition of a linked list containing `int`
 * values implemented using cells linked by pointers. Warning: the cells
 * pointers should not be shared as deallocation of a linked list
 * deallocates the memory space reserved for the cells!
 *
 * This is a "functional" version of the list.
 *
 * The API of the linked list is defined as follows:
 *
 * - a function to create an empty list
 * - a function to append an element at the beginning of the list
 * - a function to return the size of a list
 * - a function to return if a list is empty of not
 * - a function to get the element at a specified position
 * - a function to insert an element at a specified position in
 *   the list
 * - a function to remove an element at a specified position
 *   in the list
 * - a function to deallocate a list
 * - a function to print a list
 *
 * You should always call the deallocate function when you do not
 * need a list anymore.
 */

#ifndef LINKED_LIST_INT_FUN_H
#define LINKED_LIST_INT_FUN_H

#include <stdbool.h>

/**
 * @brief An alias for the structure representing the cells
 */
typedef struct cell_map cell_map;

/**
 * @brief The structure representing the cells of the list
 */

typedef struct my_map my_map;

struct cell_map{
    /** the value in the cell */
    my_map *map;
    /** the next cell in the list */
    cell_map *next;
};

/**
 * @brief An alias for the structure representing the
 *        linked list
 */
typedef cell_map *linked_list_map;

bool compare_maps(my_map *map1, my_map *map2);

/**
 * @brief 
 *
 * @return 
 */
bool map_list_contains(linked_list_map list, my_map *map);

/**
 * @brief Creates an empty list
 *
 * @return an empty list
 */
linked_list_map map_list_nil();

/**
 * @brief Append an element at the beginning of a list
 *
 * @param list    the list to which the value is to be appended
 * @param value   the value to be added in the list
 *
 * @return a list whose first cell contains the value passed as
 *         parameter. The next cells are the ones of the list
 *         passed as parameter.
 */
linked_list_map map_list_cons(linked_list_map list, my_map * MAP);

/**
 * @brief The length of a list
 *
 * @param list  the list whose length is wanted
 *
 * @return the length of the list (i.e. the number of distinct cells
 *         in the list)
 */
int map_list_size(linked_list_map list);

/**
 * @brief Is the list empty?
 *
 * @param list  the list
 *
 * @return true is the list is empty, false else
 */
bool map_list_is_empty(linked_list_map list);

/**
 * @brief Get an element in the list at a specified position
 *
 * @param list  the list to be queried
 * @param pos   the position of the wanted element
 * @pre   `pos` should be comprised between 0 and the length of
 *         the list (excluded)
 *
 * @return the value stored at position `pos`
 */
my_map * map_list_get_element(linked_list_map list, int pos);

/**
 * @brief Insert an element in the list at a specified position
 *
 * @param list   the list in which the element is inserted
 * @param pos    the position of the wanted element
 * @param value  the value of the new element
 *
 * @return a list `l` such that:
 *         - \f$\forall i \in [0, ..., pos - 1]\f$ `get_element(l, i) ==
 *           get_element(list, i)`
 *         - `get_element(l, pos) == value`
 *         - \f$\forall i \in [pos + 1, ..., length]\f$
 *          `get_element(l, i) == get_element(list, i - 1)`
 *
 * @pre   `pos` should be comprised between 0 and the length of
 *         the list
 */
linked_list_map map_list_insert_element(linked_list_map list, int pos, my_map * MAP);

/**
 * @brief Remove an element in the list at a specified position
 *
 * @param list  the list from which the element is to be removed
 * @param pos   the position of the element
 *
 * @return a list `l` such that:
 *         - \f$\forall i \in [0, ..., pos - 1]\f$ `get_element(l, i) ==
 *           get_element(list, i)`
 *         - \f$\forall i \in [pos, ..., length - 1]\f$
 *           `get_element(l, i) == get_element(list, i + 1)`
 *
 * @pre   `pos` should be comprised between 0 and the length of
 *         the list (excluded)
 */
linked_list_map map_list_remove_element(linked_list_map list, int pos);

/**
 * @brief Deallocate a list
 *
 * @param list  the list to be deallocated
 *
 * @post After the call to `deallocate_list`, all cells composing `list`
 *       are deallocated.
 */
void map_list_deallocate_list(linked_list_map list);

#endif