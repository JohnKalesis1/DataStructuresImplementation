///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT BList μέσω διπλά συνδεδεμένης λίστας.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTBList.h"


// Ενα BList είναι pointer σε αυτό το struct
struct blist {
	BListNode dummy;
	BListNode last;
	int size;
	DestroyFunc destroy_value;
};

struct blist_node {
	Pointer value;
	BListNode prev;
	BListNode next;
};


BList blist_create(DestroyFunc destroy_value) {
	BList blist;
	blist=malloc(sizeof(*blist));
	blist->size=0;
	blist->dummy=malloc(sizeof(*blist->dummy));
	blist->dummy->next=NULL;
	blist->dummy->prev=NULL;
	blist->last=blist->dummy;
	blist->destroy_value=destroy_value;
	return blist;
}

int blist_size(BList blist) {
	return blist->size;
}

void blist_insert(BList blist, BListNode node, Pointer value) {
	if (node==BLIST_EOF)  {
		BListNode prev_node;
		prev_node=blist->last;
		if (blist->size!=0)  {
			blist->last->next=malloc(sizeof(BListNode*));
			blist->last->next->value=value;
			blist->last=blist->last->next;
			blist->last->prev=prev_node;
			blist->last->next=NULL;
		}
		else  {
			blist->dummy->next=malloc(sizeof(BListNode*));
			blist->dummy->next->value=value;
			blist->dummy->next->prev=blist->dummy;
			blist->last=blist->dummy->next;
		}
	}
	else  {
		BListNode prev_node=node->prev;
		node->prev=malloc(sizeof(node));
		node->prev->prev=prev_node;
		prev_node->next=node->prev;
		node->prev->value=value;
		node->prev->next=node;
	}
	blist->size++;
	return ;
}

void blist_remove(BList blist, BListNode node) {
	BListNode prev_node=node->prev,next_node=node->next;
	prev_node->next=next_node;
	if (next_node!=NULL)  {
		next_node->prev=prev_node;
	}
	if (blist->destroy_value!=NULL)  {
		(blist->destroy_value)(node->value);
	}
	free(node);
	blist->size--;
	return ;
}

Pointer blist_find(BList blist, Pointer value, CompareFunc compare) {
	if (blist->size!=0)  {
		BListNode node=blist->dummy->next;
		while (node!=BLIST_EOF)  {
			if (compare(node->value,value)==0)  {
				return value;
			}
			else  {
				node=node->next;
			}
		}
	}
	return NULL;
}

DestroyFunc blist_set_destroy_value(BList blist, DestroyFunc destroy_value) {
	DestroyFunc old_destroy_value=blist->destroy_value;
	blist->destroy_value=destroy_value;
	return old_destroy_value;
}

void blist_destroy(BList blist) {
	BListNode node = blist->dummy;
	
	while (node != NULL) {			
		BListNode next = node->next;		
		if (node != blist->dummy && blist->destroy_value != NULL)  { 
			blist->destroy_value(node->value);
		}
		free(node);
		node = next;
	}
	free(blist);
}


// Διάσχιση της λίστας /////////////////////////////////////////////

BListNode blist_first(BList blist) {
	if (blist->size!=0)  {
		return blist->dummy->next;
	}
	return BLIST_BOF;
}

BListNode blist_last(BList blist) {
	return blist->last;
}

BListNode blist_next(BList blist, BListNode node) {
	assert(node!=NULL);
	if (node->next!=NULL)  {
		return node->next;
	}  
	return BLIST_EOF;
}

BListNode blist_previous(BList blist, BListNode node) {
	if (node->prev!=NULL)  {
		return node->prev;
	}  
	return BLIST_BOF;
}

Pointer blist_node_value(BList blist, BListNode node) {
	return node->value;
}

BListNode blist_find_node(BList blist, Pointer value, CompareFunc compare) {
	if (blist->size!=0)  {
		BListNode node=blist->dummy->next;
		while (node!=BLIST_EOF)  {
			if (compare(value,node->value)==0)  {
				return node;
			}
			else  {
				node=node->next;
			}
		}
	}
	return BLIST_EOF;
}