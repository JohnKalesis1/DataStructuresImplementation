//////////////////////////////////////////////////////////////////
//
// Unit tests για τον ADT BList.
// Οποιαδήποτε υλοποίηση οφείλει να περνάει όλα τα tests.
//
//////////////////////////////////////////////////////////////////

#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "ADTBList.h"

int* create_int(int a)  {
	int* h; 
	h=malloc(sizeof(int*));
	*h=a;
	return h;
}
void test_create(void) {
	BList blist=blist_create(free);
	TEST_ASSERT(blist_size(blist)==0);
	blist_destroy(blist);
}

void test_insert(void) {
	BList blist=blist_create(free);
	int N=50;
	int array[N];
	for (int i=0;i<N;i++)  {
		array[i]=i;
		blist_insert(blist,BLIST_BOF,create_int(array[i]));
		TEST_ASSERT(*(int*)blist_node_value(blist,blist_first(blist))==array[i]);
	}
	BListNode node;
	node=blist_first(blist);
	for (int i = N - 1; i >= 0; i--) {
		TEST_ASSERT(*(int*)blist_node_value(blist, node) == array[i]);
		node = blist_next(blist, node);
	}
	node=blist_last(blist);
	for (int i = 0; i < N; i++) {
		TEST_ASSERT(*(int*)blist_node_value(blist, node) == array[i]);
		node = blist_previous(blist, node);
	}
	blist_destroy(blist);
}

void test_remove(void) {
	BList blist=blist_create(free);
	int N=50;
	int array[N];
	for (int i=0;i<N;i++)  {
		array[i]=i;
		blist_insert(blist,BLIST_BOF,create_int(array[i]));
	}
	for (int i=0;i<N;i++)  {
		blist_remove(blist,blist_first(blist));
		TEST_ASSERT(blist_size(blist)==N-i-1);
	}
	blist_destroy(blist);
}
int compare_ints(Pointer a,Pointer b)  {
	return *(int*)a - *(int*)b;
}
void test_find() {
	BList blist=blist_create(free);
	int N=50;
	int array[N];
	for (int i=0;i<N-1;i++)  {
		array[i]=i;
		blist_insert(blist,BLIST_BOF,create_int(array[i]));
		TEST_ASSERT(blist_find(blist,&array[i],compare_ints)!=NULL);
	}
	array[N-1]=100;
	TEST_ASSERT(blist_find(blist,&array[50],compare_ints)==NULL);
	blist_destroy(blist);
}

void test_find_node() {
	BList blist=blist_create(free);
	int N=50;
	int array[N];
	for (int i=0;i<N-1;i++)  {
		array[i]=i;
		blist_insert(blist,BLIST_BOF,create_int(array[i]));
		TEST_ASSERT(blist_find_node(blist,&array[i],compare_ints)!=BLIST_EOF);
	}
	array[N-1]=100;
	TEST_ASSERT(blist_find_node(blist,&array[50],compare_ints)==BLIST_EOF);
	blist_destroy(blist);
}


// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "list_create", test_create },
	{ "list_insert_next", test_insert },
	{ "list_remove", test_remove },
	{ "list_find", test_find },
	{ "list_find_node", test_find_node },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};