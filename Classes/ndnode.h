#ifndef NDIMENSIONALNODE_H
#define NDIMENSIONALNODE_H

typedef unsigned long long ull;

typedef struct NDNode {
// Unique number for a node within a controller. 0 is reserved.
	ull index;
// Number of dimensions the node will work on. Defaults to 1. Can't be 0.
	ull dimensions;
// Position with reference to origin.
long long *position;
// Pointer to data, duh.
	void *data;
// Previous and next nodes in the controller. They come in pairs, one pair for each dimension.
	struct NDNode **prev, **next;
} NDNode;

typedef NDNode* NDNodeRef;

typedef struct NDNodeController {
// Unique number for a controller in memory.
	ull ID;
// Number of dimensions the controller and its nodes are going to work on.
	ull dimensions;
// Number of nodes contained in the controller.
	ull size;
// Indices already in use.
	ull *indices;
// First node. Use .previous and .next fields to navigate through the nodes.
	NDNodeRef nodes;
} NDNodeController;

typedef NDNodeController* NDNodeControllerRef;

#endif
