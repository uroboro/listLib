#include "snlib.h"

//code from another list code I made but will reuse to build this new one.

mtxnode *mnFindByIndex(mtxnode *node, int index) {
	if (node == NULL || index < 0) {
		printf("#Empty node or invalid index.\n");
		return NULL;
	}

	mtxnode *aux = node;
	while (aux->next != NULL && aux->index != index)
		aux = aux->next;
	if (aux->index == index)
		return aux;
	return NULL;
}
mtxnode *mnFindByData(mtxnode *node, matrix *self) {
	if (node == NULL || self == NULL) {
		printf("#Empty node or matrix.\n");
		return NULL;
	}

	mtxnode *aux = node;
	while (aux->next != NULL && ! mtxEquals(aux->data, self))
		aux = aux->next;
	if (mtxEquals(aux->data, self))
		return aux;
	return NULL;
}
mtxnode *mnFindNextAvailable(mtxnode *node) {
	if (node == NULL) {
//		printf("#Empty node.\n");
		return NULL;
	}

	mtxnode *aux = node;
	for (unsigned char now = 0; aux->next != NULL; now++) {
		if (aux->next->index != now + 1)
			return aux;
		aux = aux->next;
	}
	return aux;
}

//list

void mnPush(mtxnode **node, matrix *self) {
	if (self == NULL) {
		printf("#Empty matrix.\n");
		return;
	}

	mtxnode *aux = mnFindNextAvailable(*node);
	mtxnode *new = (mtxnode *) malloc(sizeof(mtxnode));
	new->data = self;
	new->self = new;

	//if list is empty or index:0 is missing
	if (aux == NULL || (*node != NULL && (*node)->index != 0)) {
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
void mnProperties(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return;
	}

	mtxProperties(node->data);
	return;
}
void mnUpdate(mtxnode *node) {
	if (node == NULL) {
		printf("#Empty node.\n");
		return;
	}

	mtxUpdate(node->data);
	return;
}

mtxnode *mnOpposite(mtxnode **list, mtxnode *node) {
	if (*list == NULL || node == NULL)
		return NULL;

	matrix *sender = mtxOpposite(node->data);
	mnPush(list, sender);
	return mnFindByData(*list, sender);
}
mtxnode *mnTranspose(mtxnode **list, mtxnode *node) {
	if (*list == NULL || node == NULL)
		return NULL;

	matrix *sender = mtxTranspose(node->data);
	mnPush(list, sender);
	return mnFindByData(*list, sender);
}
mtxnode *mnAdjugate(mtxnode **list, mtxnode *node) {
	if (*list == NULL || node == NULL)
		return NULL;

	matrix *sender = mtxAdjugate(node->data);
	if (sender == NULL)
		return NULL;

	mnPush(list, sender);
	return mnFindByData(*list, sender);
}
mtxnode *mnInverse(mtxnode **list, mtxnode *node) {
	if (*list == NULL || node == NULL)
		return NULL;

	matrix *sender = mtxInverse(node->data);
	if (sender == NULL)
		return NULL;

	mnPush(list, sender);
	return mnFindByData(*list, sender);
}

mtxnode *mnLinearOp(mtxnode **list, mtxnode *nodeA, char op, mtxnode *nodeB) {
	if (*list == NULL || nodeA == NULL || nodeB == NULL || ! (op == '+' || op == '-' || op == '*' || op == '/'))
		return NULL;

	matrix *sender = mtxLinearOp(nodeA->data, op, nodeB->data);
	if (sender == NULL)
		return NULL;

	mnPush(list, sender);
	return mnFindByData(*list, sender);
}
mtxnode *mnVMultiply(mtxnode **list, mtxnode *nodeA, mtxnode *nodeB) {
	if (*list == NULL || nodeA == NULL || nodeB == NULL)
		return NULL;

	matrix *sender = mtxVMultiply(nodeA->data, nodeB->data);
	if (sender == NULL)
		return NULL;

	mnPush(list, sender);
	return mnFindByData(*list, sender);
}
mtxnode *mnSMultiply(mtxnode **list, mtxnode *node, float scalar) {
	if (*list == NULL || node == NULL)
		return NULL;

	matrix *sender = mtxSMultiply(node->data, scalar);
	if (sender == NULL)
		return NULL;

	mnPush(list, sender);
	return mnFindByData(*list, sender);
}

//Evaluation
bool mnEquals(mtxnode *nodeA, mtxnode *nodeB) {
	if (nodeA == NULL || nodeB == NULL)
		return FALSE;

	if (nodeA == nodeB)
		return TRUE;

	return mtxEquals(nodeA->data, nodeB->data);
}

bool mnCopy(mtxnode *nodeA, mtxnode *nodeB) {
	return FALSE;
}
/*
bool mnCopy(mtxnode *nodeA, mtxnode *nodeB) {
	if (nodeA == NULL || nodeB == NULL)
		return FALSE;

	if (nodeA == nodeB)
		return TRUE;

	return mtxCopy(nodeA->data, nodeB->data);
}
*/
