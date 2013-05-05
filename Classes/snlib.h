#ifndef SIMPLENODELIB_H
#define SIMPLENODELIB_H

/*
will change to sharedInstance based list to simplify function calls
functions will, in next edits, rely on a SNode*, or multiple, and a function pointer so the function acts on the nodes and reduce the number of list functions.
combined with sharedInstance feature, indexes can be provided instead of SNode* (maybe)
the idea is to separate this list library from the matrix library and reuse in other projects
*/

#include <stdio.h>
#include <stdlib.h>
#include "simplenode.h"

#define ull unsigned long long

// Returns index number for pushed data
ull SNPush(SNodeRef *node, void *data);
// Returns 0 if no errors
ull SNPop(SNodeRef *node, ull index);

// Returns 0 if no errors
ull SNFree(SNodeRef *node, ull index);
ull SNDump(SNodeRef *node);

// Returns the number of data nodes loaded in a list
ull SNCount(SNodeRef *node);

// Returns bytes used by list, provided a function to get the memory used by the data stored in each node.
ull SNMemory(SNodeRef *node, ull (*memUsedByData)(void *));

/* This function will search for a node containing the data given.
 * If there is no data to be found, they return 0; otherwise, the node containing it.
 * A function capable of comparing 2 data pointers (and its content) must be provided.
 */
ull SNFindData(SNodeRef *node, void *data, bool (*comparator)(void *, void *));

/* SNFindNextAvailable() is used internally by SNPush()
 * It will return 0 if the list is empty or the first available index.
 * Always check if there is another node after it.
 */
ull SNFindNextAvailable(SNodeRef *node);

// Retrieve data from node
void *SNGetDataFromIndex(SNodeRef *node, ull index);

// Apply a function to a NULL-terminated array of data nodes.
ull SNApplyFunction(SNodeRef *node, ull *index, void *(*appliedFunction)(void **));

/* Returns an array with the indexes of the data nodes in a list.
 * The first position is the number of data nodes in the list.
 */
ull *SNList(SNodeRef *node);

#endif
