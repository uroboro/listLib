#ifndef SIMPLENODE_H
#define SIMPLENODE_H

typedef struct SNode {
	long long index;
	void *data;
	struct SNode *prev, *self, *next;
} SNode;

typedef SNode* SNodeRef;

#endif
