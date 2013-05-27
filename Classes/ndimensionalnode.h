#ifndef NDIMENSIONALNODE_H
#define NDIMENSIONALNODE_H

typedef unsigned long long ull;

typedef struct NDNode {
	ull index;
	ull dimensions;
	void *data;
	struct NDNode **prev, **next;
} NDNode;

typedef NDNode* NDNodeRef;

typedef struct NDNodeController {
	ull ID;
	ull dimensions;
	ull size;
	NDNodeRef nodes;
} NDNodeController;

typedef NDNodeController* NDNodeControllerRef;

#endif
