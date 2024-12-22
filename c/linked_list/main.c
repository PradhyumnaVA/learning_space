#include <stdio.h>
#include "ll_lib.h"

//struct node{
//        int data;
 //       struct node *next;
 //};

int main(){
        struct node *head = create(1);
        head -> next = create(2);
        head -> next -> next = create(4);
	
	// print the present list once
        printlist(head);
        
	// inserting a number at the head of the list
        printf("new data added at head is 0\n");
        head = head_insert(head,0);
        printlist(head);

	// inserting a number at the tail or end of the list
        printf("new data to append is 5\n");
        head = tail_insert(head,5);
        printlist(head);

	// inserting a number at the given node
	printf("new data to be inserted after 2 is 6\n");
	place_insert(head -> next -> next, 6);
	printlist(head);
	
	// deleting the head
	printf("deleting the head\n");
	head = delete_head(head);
	printlist(head);
     	
       	// deleting the tail
	printf("deleting the tail\n");	
	head = delete_tail(head);
	printlist(head);
	
	// deleting a number at a given node
	printf("deleting 6 from the list\n");
	place_delete(head, head -> next -> next);
	printlist(head);

	return 0;
}
