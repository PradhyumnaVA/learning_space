#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};

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

void *printlist(struct node *head){
	struct node *current = head;
	while(current != NULL){
		printf("%d\n",current -> data);
		current = current -> next;
	}
}

int main(){
	struct node *head = create(1);
	head -> next = create(2);
	head -> next -> next = create(4);

	printlist(head);
	
	printf("new data added at head is 0\n");
	head = head_insert(head,0);
	printlist(head);

	printf("new data to append is 5\n");
	head = tail_insert(head,5);
	printlist(head);

	return 0;
}

