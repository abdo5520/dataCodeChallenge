/*
 *
 * @author  Abdallah S. Abdallah <abdo.aast@gmail.com>
 * @file median.h
 * @version 0.1
 * @date Mar 13, 2015
 *
 */

/**
 *  COPYRIGHT Disclaimer
 *
 *  The linked list handling code is heavily depending on the code found in the following  link
 *
 *  http://www.geeksforgeeks.org/merge-sort-for-linked-list/
 *
 *
 *
 */

#ifndef MEDIAN_H_
#define MEDIAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <error.h>


#include <sys/types.h>


#include <dirent.h>

#define NAME_LEN 256
#define MAX_NO_FILES 100

#include<stdio.h>
#include<stdlib.h>

/* Link list node */
struct node
{
	int data;
	struct node* next;
};

/* function prototypes */
struct node* SortedMerge(struct node* a, struct node* b);
void FrontBackSplit(struct node* source,
		struct node** frontRef, struct node** backRef);

/**
 *
 * sorts the linked list by changing next pointers (not data)
 *
 */
void MergeSort(struct node** headRef)
{
	struct node* head = *headRef;
	struct node* a;
	struct node* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

/**
 *
 *  ReCombine the sub -lists again into one list with one root node
 *
 *
 */
struct node* SortedMerge(struct node* a, struct node* b)
{
	struct node* result = NULL;

	/* Base cases */
	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (a->data <= b->data)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return(result);
}

/**
 *
 *  split any linked list into two halfs and return a pointer to the first member node
 *  in each half
 *
 */

void FrontBackSplit(struct node* source,
		struct node** frontRef, struct node** backRef)
{
	struct node* fast;
	struct node* slow;
	if (source==NULL || source->next==NULL)
	{
		/* length < 2 cases */
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		/* Advance 'fast' two nodes, and advance 'slow' one node */
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		/* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

/**
 *
 *  Receives the linked list root and traverse the list until the middle nodes
 *  then calcualtes/returns the median value
 *
 *
 */
float FindMedianValue(struct node* source, int nnodes)
{

	int counter =0;

	struct node* tracer;

	tracer = source;

	if (nnodes <=0)
		return (-1);

	if (nnodes == 1)
		return tracer->data;

	if (nnodes == 2)
		return ((float)(  tracer->data  +  ((tracer->next)->data )  )/2 );


	// Odd number of nodes
	if (nnodes%2 == 1 )
	{
		while (counter < (int)(nnodes/2) -1)
		{
			tracer = tracer->next;

			counter++;

		}
		//printf("internal counter = %d", counter);
		return (tracer->next->data);


	}

	// Even Number of Nodes
	else
	{
		while (counter <  (nnodes/2) -1 )
		{
			tracer = tracer->next;

			counter++;

		}
	//	printf("internal counter = %d", counter);
		return ((float)(  tracer->data  +  (tracer->next->data )  )/ 2 );


	}




	/* 'slow' is before the midpoint in the list, so split it in two
      at that point. */


}


/**
 * Function to print nodes in a given linked list
 *
 */



void PrintList(struct node *node)
{
	while(node!=NULL)
	{
		printf("%d ", node->data);
		node = node->next;
	}
}

/* Function to insert a node at the beginging of the linked list */
void Push(struct node** head_ref, int new_data)
{
	/* allocate node */
	struct node* new_node =
			(struct node*) malloc(sizeof(struct node));

	/* put in the data  */
	new_node->data  = new_data;

	/* link the old list off the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref)    = new_node;
}



#endif /* MEDIAN_H_ */
