#include <stdio.h>
#include <stdlib.h>

#include "ndlib.h"

//order:
NDNodeControllerRef NDNewController(ull dimensions);
ull NDDeleteController(NDNodeControllerRef controller, ull ID);
ull NDPush(NDNodeControllerRef controller, void *data);
ull NDPop(NDNodeControllerRef controller, ull index);
NDNodeRef NDNewNode(NDNodeControllerRef controller);
ull NDDeleteNode(NDNodeControllerRef controller, ull index);
ull NDCount(NDNodeControllerRef controller);
ull NDMemory(NDNodeControllerRef controller, ull (*memUsedByData)(void *));
ull NDFindData(NDNodeControllerRef controller, void *data, bool (*comparator)(void *, void *));
ull NDFindNextAvailable(NDNodeControllerRef controller);
NDNodeRef NDNodeRefAtIndex(NDNodeControllerRef controller, ull index);
void *NDDataAtIndex(NDNodeControllerRef controller, ull index);
ull NDApplyFunction(NDNodeControllerRef controller, ull *indexes, void *(*function)(void **));


	if (controller == NULL || index == 0 || function == NULL) {
return 0;
}


//code from another list code I made but will reuse to build this new one.

//list

ull SNPush(SNodeRef *node, void *data) {
void mnPush(mtxnode **node, matrix *self) {
	if (data == NULL) {
//		  printf("#Empty matrix.\n");
		return 1;
	}
SNodeRef aux = *node;

	ull nextIndex = SNFindNextAvailable(aux);
	SNodeRef new = (SNodeRef)malloc(sizeof(SNode));
new->index = newIndex;
	new->data = data;
	new->self = new;

	//if list is empty or index:0 is missing
	if ( == NULL || (*node != NULL && (*node)->index != 0)) {
		new->index = 0;
		new->prev = NULL;
		new->next = aux;
		*node = new;
	}
	else {
		//otherwise
		new->index = aux->index + 1;
		new->prev = aux;
		new->next = aux->next;
		aux->next = new;
		//if the next element is not the last
		if (new->next != NULL)
			new->next->prev = new;
	}
	return;
}
void mnPop(mtxnode **node, int index) {
	if (node == NULL || index < 0) {
		printf("#Empty node.\n");
		return;
	}

	mtxnode *aux = mnFindByIndex(*node, index);
	if (aux == NULL) {
		printf("No matrix with index: %d \n", index);
		return;
	}
	if (aux->prev != NULL)
		aux->prev->next = aux->next;
	else
		*node = aux->next;
	if (aux->next != NULL)
		aux->next->prev = aux->prev;
	mnFree(aux);
	return;
}

void mnFree(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return;
	}

	mtxFree(node->data);
	free(node);
	return;
}
void mnDump(mtxnode **node) {
	if (*node == NULL) {
		printf("#Empty node.\n");
		return;
	}

	while (*node != NULL)
		mnPop(node, (*node)->index);

	return;
}

long int mnMemory(mtxnode *node) {
	if (node == NULL)
		return 0;

	long int size = 0;
	mtxnode *aux = node;
	do {
		size += sizeof(mtxnode) + mtxMemory(aux->data);
		aux = aux->next;
	} while (aux != NULL);
	return size;
}
char mnCount(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return 0;
	}

	int i;
	mtxnode *aux;
	for (i = 0, aux = node; aux != NULL; i++, aux = aux->next);
//if (debug) dbgInt(i, "\n");
	return i;
}
char *mnList(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return NULL;
	}

	int j = mnCount(node);
	char *list = (char *) malloc((j + 1) * sizeof(char));
	list[0] = j;

	mtxnode *aux = node;
	for (int  i = 1; i < j; i++, aux = aux->next)
		list[i] = aux->index;

	return list;
}

ull SNFindNextAvailable(SNodeRef *node) {
SNodeRef n = *node;
	if (n == NULL) {
//		printf("#Empty node.\n");
		return NULL;
	}

	SNodeRef *aux = n;
	for (ull now = 0; aux->next != NULL; now++) {
		if (aux->next->index != now + 1)
			break;
		aux = aux->next;
	}
	return now + 1;
}