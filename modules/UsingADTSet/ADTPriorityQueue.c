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
    CompareFunc compare;		
};
struct priority_queue_node   {
    Pointer value;
    PriorityQueue pqueue;
};




// Συναρτήσεις του ADTPriorityQueue //////////////////////////////////////////////////
int compare_nodes(Pointer a,Pointer b)  {
        PriorityQueueNode node1= (PriorityQueueNode) a;
        PriorityQueueNode node2=  (PriorityQueueNode) b;
        return (node2->pqueue->compare)(node1->value,node2->value);
};
void destroy_nodes(Pointer a)  {
    PriorityQueueNode node=(PriorityQueueNode) a;
    if (node->pqueue->destroy!=NULL)  {
        (node->pqueue->destroy)(node->value);
    }
    free(node);
    
}
PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
	PriorityQueue pqueue;
    PriorityQueueNode node;
    pqueue=malloc(sizeof(*pqueue));
    pqueue->compare=compare;
    pqueue->set=set_create(compare_nodes,destroy_nodes);
    pqueue->destroy=destroy_value;
    if (values!=NULL)  {
        for (int i=0;i<vector_size(values);i++)  {
            node=malloc(sizeof(*node));
            node->value=vector_get_at(values,i);
            node->pqueue=pqueue;
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
    node=malloc(sizeof(*node));
    node->value=value;
    node->pqueue=pqueue;
    set_insert(pqueue->set,node);
	return node;
}

void pqueue_remove_max(PriorityQueue pqueue) {
    set_remove(pqueue->set,set_node_value(pqueue->set,set_last(pqueue->set)));
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	return set_set_destroy_value(pqueue->set,destroy_value);
}

void pqueue_destroy(PriorityQueue pqueue) {
    set_destroy(pqueue->set);
	free(pqueue);
}



//// Νέες συναρτήσεις για την εργασία 2 //////////////////////////////////////////

Pointer pqueue_node_value(PriorityQueue pqueue, PriorityQueueNode node) {
    return node->value;
}

void pqueue_remove_node(PriorityQueue pqueue, PriorityQueueNode node) {
    set_remove(pqueue->set,node);
    return ;
}

void pqueue_update_order(PriorityQueue pqueue, PriorityQueueNode node) {

}
