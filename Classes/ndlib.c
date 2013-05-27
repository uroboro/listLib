#include "snlib.h"
//order:
SNodeRef SNNew(SNodeRef *node);
ull SNPush(SNodeRef *node, void *data);
ull SNPop(SNodeRef *node, ull index);
ull SNFree(SNodeRef *node, ull index);
ull SNDump(SNodeRef *node);
ull SNCount(SNodeRef *node);
ull SNMemory(SNodeRef *node, ull (*memUsedByData)(void *));
ull SNFindData(SNodeRef *node, void *data, bool (*comparator)(void *, void *));
ull SNFindNextAvailable(SNodeRef *node);
void *SNGetDataFromIndex(SNodeRef *node, ull index);
ull SNApplyFunction(SNodeRef *node, ull *index, void *(*appliedFunction)(void **));
ull *SNList(SNodeRef *node);

//to-do:
SNodeRef SNNew(SNodeRef *node);
ull SNPush(SNodeRef *node, void *data);
ull SNPop(SNodeRef *node, ull index);
ull SNFree(SNodeRef *node, ull index);
ull SNDump(SNodeRef *node);
ull SNCount(SNodeRef *node);
ull SNMemory(SNodeRef *node, ull (*memUsedByData)(void *));
ull SNFindData(SNodeRef *node, void *data, bool (*comparator)(void *, void *));
void *SNGetDataFromIndex(SNodeRef *node, ull index);
ull SNApplyFunction(SNodeRef *node, ull *index, void *(*appliedFunction)(void **));
ull *SNList(SNodeRef *node);


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

void mnShow(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return;
	}

	printf("Matrix %d:\n", node->index);
	mnUpdate(node);
	mnPrint(node);
	mnProperties(node);

/*if (debug) {
	dbgPointer(node->self, "\t");
	dbgPointer(node->prev, "\t");
	dbgPointer(node->next, "\n");
	printf("--------------------\n");
}
*/
	return;
}
void mnShowAll(mtxnode *node) {
if (debug) dbgPointer(node, "\n");
	if (node == NULL) {
		printf("#Empty node.\n");
		return;
	}

	for (mtxnode *aux = node; aux != NULL; aux = aux->next)
		mnShow(aux);
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
void mnUpdateAll(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return;
	}

	if (node->next != NULL)
		mnUpdateAll(node->next);
	if (node != NULL)
		mnUpdate(node);
	return;
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
char *mnEnumerate(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return NULL;
	}

	char *list = mnList(node);
	char *enumeration = (char *) malloc(list[0] * 4 * sizeof(char));
	enumeration[list[0] * 4] = 0;

	mtxnode *aux = node;
	for (unsigned char i = 0, j = 0; j < list[0]; j++, aux = aux->next) {
		enumeration[i] = aux->index + '0'; i++;

		if (j < list[0] - 1) {
			enumeration[i] = ','; i++;
			enumeration[i] = ' '; i++;
		}
	}

	unsigned char strlen;
	for (strlen = 0; enumeration[strlen] != 0; strlen++);
	enumeration = (char *) realloc(enumeration, (strlen + 1) * sizeof(char));
	enumeration[strlen] = 0;

	return enumeration;
}

//matrix
void mnPrint(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return;
	}

	mtxPrint(node->data);
	return;
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