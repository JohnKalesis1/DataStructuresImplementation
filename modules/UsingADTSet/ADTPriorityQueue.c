///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Priority Queue μέσω σωρού.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTSet.h"	
#include "ADTVector.h"


struct priority_queue {
	Set set;	
    DestroyFunc destroy;			
};
struct priority_queue_node   {
    Pointer value;
};




// Συναρτήσεις του ADTPriorityQueue //////////////////////////////////////////////////
int compare_nodes(PriorityQueue pqueue,CompareFunc compare,Pointer a,Pointer b)  {
    return compare(((PriorityQueueNode)a)->value,((PriorityQueueNode)b)->value);
}
PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
	PriorityQueue pqueue;
    PriorityQueueNode node;
    pqueue=malloc(sizeof(PriorityQueue*));
    pqueue->set=set_create(compare_nodes(pqueue,compare,),destroy_value);
    pqueue->destroy=destroy_value;
    if (values!=NULL)  {
        for (int i=0;i<vector_size(values);i++)  {
            node=malloc(sizeof(PriorityQueueNode*));
            node->value=vector_get_at(values,i);
            set_insert(pqueue->set,node);
        }
    }
	return pqueue;
}

int pqueue_size(PriorityQueue pqueue) {
	return set_size(pqueue->set);
}

Pointer pqueue_max(PriorityQueue pqueue) {
	return 	pqueue_node_value(pqueue,set_node_value(pqueue->set,set_last(pqueue->set)));	
}

PriorityQueueNode pqueue_insert(PriorityQueue pqueue, Pointer value) {
    PriorityQueueNode node;
    node=malloc(sizeof(PriorityQueueNode*));
    node->value=value;
    set_insert(pqueue->set,node);
	return node;
}

void pqueue_remove_max(PriorityQueue pqueue) {
	if (pqueue->destroy!=NULL)  {
        (pqueue->destroy)(((PriorityQueueNode) set_node_value(pqueue->set,set_last(pqueue->set)))->value);
    }
    free(set_node_value(pqueue->set,set_last(pqueue->set)));
    set_remove(pqueue->set,set_last(pqueue->set));
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	return set_set_destroy_value(pqueue->set,destroy_value);
}

void pqueue_destroy(PriorityQueue pqueue) {
	SetNode old,snode=set_first(pqueue->set);
    while (snode!=SET_EOF)  {
        if (pqueue->destroy!=NULL)  {
            (pqueue->destroy)(((PriorityQueueNode) set_node_value(pqueue->set,snode))->value);
        }
        free(set_node_value(pqueue->set,snode));
        old=snode;
        set_remove(pqueue->set,snode);
        snode=set_next(pqueue->set,old);
    }
    set_destroy(pqueue->set);
	free(pqueue);
}



//// Νέες συναρτήσεις για την εργασία 2 //////////////////////////////////////////

Pointer pqueue_node_value(PriorityQueue pqueue, PriorityQueueNode node) {
    return ((PriorityQueueNode) set_node_value(pqueue->set,set_find_node(pqueue->set,node)))->value;
}

void pqueue_remove_node(PriorityQueue pqueue, PriorityQueueNode node) {
    SetNode snode=set_find_node(pqueue->set,pqueue_node_value(pqueue,node));
    if (pqueue->destroy!=NULL)  {
        (pqueue->destroy)(pqueue_node_value(pqueue,node));
    }
    free(node);
    set_remove(pqueue->set,snode);
    return ;
}

void pqueue_update_order(PriorityQueue pqueue, PriorityQueueNode node) {

}
