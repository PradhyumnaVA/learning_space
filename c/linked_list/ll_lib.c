#include <stdlib.h>
#include <stdio.h>
#include "ll_lib.h"

struct node *create(int new_data){
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	new_node -> data = new_data;
	new_node -> next = NULL;
	return new_node;
}

struct node *head_insert(struct node *head, int insert_data){
	struct node *new_head = create(insert_data);
	new_head -> next = head;
	return new_head;
}

/*
 * dont think of current as an array, in the while loop it 
 * reaches the last node and the new node is inserted in the 
 * next of last node. this updation is done in the memory 
 * stack, and head is returned because to print the list we 
 * need the pointer to head(first node).
*/
struct node *tail_insert(struct node *head, int insert_data){
	struct node *new_tail = create(insert_data);
	struct node *current = head;
	while(current != NULL){
		current = current -> next;
		if(current -> next == NULL){
			current -> next = new_tail;
			break;
		}
	}
	return head;
}

/*
 * in this first a new node is created called new_place
 * and it is given the insert_data. The node after the given place
 * is next_place. the next of place is connected to new_place and
 * the next of new_place is connected to next_place. 
 */
void place_insert(struct node *place, int insert_data){
	struct node *new_place = create(insert_data);
	struct node *next_place = place -> next;
	place -> next = new_place;
	new_place -> next = next_place;
}

/*
 * a variable called new_head is created and the node after the 
 * head is initilaised to this. the head is made to point to this 
 * new_head node, effectively deleting the previous head node. 
 */
struct node *delete_head(struct node *head){
	struct node *new_head = head -> next;
	return new_head;
}

struct node *delete_tail(struct node *head){
	struct node *current = head;
	while(current != NULL){
		current = current -> next;
		if(current -> next -> next == NULL){
			current -> next = NULL;
			break;
		}
	}
	return head;
}

void place_delete(struct node *head, struct node *place){
	struct node *current = head;
	struct node *next_place = place -> next;
	while(current != NULL){
		current = current -> next;
		if(current -> next == place){
			break;
		}
	}
	current -> next = next_place;
}

void *printlist(struct node *head){
	struct node *current = head;
	while(current != NULL){
		printf("%d\n",current -> data);
		current = current -> next;
	}
}
