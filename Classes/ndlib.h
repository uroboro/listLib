#ifndef NDIMENSIONALNODELIB_H
#define NDIMENSIONALNODELIB_H

/*
will change to sharedInstance based list to simplify function calls, but will be a layer on top of node controllers

With sharedInstance feature, indexes can be provided alone
*/

#include <stdio.h>
#include <stdlib.h>
#include "simplenode.h"

// Allocates and initializes a new controller. All nodes created with this controller will have the same dimensions as the controller.
NDNodeControllerRef NDNewController(ull dimensions);
// Deletes the controller with ID and all its nodes.
ull NDDeleteController(NDNodeControllerRef controller, ull ID);

// Adds a new node with data to the controller
ull NDPush(NDNodeControllerRef controller, void *data);
// Removes the node with index from the controller
ull NDPop(NDNodeControllerRef controller, ull index);

// Creates a new node for the controller
NDNodeRef NDNewNode(NDNodeControllerRef controller);
// Dwletes the node with index in the controller
ull NDDeleteNode(NDNodeControllerRef controller, ull index);

// Returns the number of data nodes loaded in a list
ull NDCount(NDNodeControllerRef controller);

// Returns bytes used by list, provided a function to get the memory used by the data stored in each node.
ull NDMemory(NDNodeControllerRef controller, ull (*memUsedByData)(void *));

/* This function will search for a node containing the data given.
 * If there is no data to be found, they return 0; otherwise, the node containing it.
 * A function capable of comparing 2 data pointers (and its content) must be provided.
 */
ull NDFindData(NDNodeControllerRef controller, void *data, bool (*comparator)(void *, void *));

/* NDFindNextAvailable() is used internally by SNPush()
 * It will return 0 if the list is empty or the first available index.
 * Always check if there are nodes around it.
 */
ull NDFindNextAvailable(NDNodeControllerRef controller);

NDNodeRef NDNodeRefAtIndex(NDNodeControllerRef controller, ull index);

// Retrieve data from node
void *NDDataAtIndex(NDNodeControllerRef controller, ull index);

// Apply a function to a NULL-terminated array of data nodes.
ull NDApplyFunction(NDNodeControllerRef controller, ull *indexes, void *(*function)(void **));


// @optional

/* Returns an array with the indexes of the data nodes in a list.
 * The first position is the number of data nodes in the list.
 */
ull *SNList(SNodeRef *node);

#endif
