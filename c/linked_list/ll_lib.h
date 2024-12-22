/* 
 * ll_lib.h - header file for all the linked list functions 
 * relating to insertion, deletion and search.
*/
#ifndef LL_LIB_H
#define LL_LIB_H

struct node{
        int data;
        struct node *next;
};

extern struct node *create(int);

extern struct node *head_insert(struct node* , int);

extern struct node *tail_insert(struct node* , int );

extern void place_insert(struct node* , int );

extern struct node *delete_head(struct node* );

extern struct node *delete_tail(struct node* );

extern void place_delete(struct node* , struct node* );

extern void *printlist(struct node* );

#endif
