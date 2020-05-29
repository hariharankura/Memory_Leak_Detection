/*
Project Name: Memory Leakage Detector
Author :Hari Haran Kura
*/

//Include Files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include "hmalloc.h"

//Constants


#define SUCCESS					(0)
#define ERROR_UNDEFINED			(-1)
#define ERROR_ADDRESS_NULL		(-2)
#define ERROR_LIST_EMPTY		(-3)
#define ERROR_NODE_NOT_FOUND	(-4)


//Structure to keep track of allocated memory
typedef struct mem_block{
	void *alloc_address;
	size_t bytes;
	struct mem_block *next;
	struct mem_block *prev;
}mem_node;

mem_node *head=NULL;
mem_node *tail=NULL;

// //Handler which Prints the Leakage Information on SIGINT Singnal
// void sigintHandler(int sig_num){
// 	print_leaks();
// 	exit(sig_num);	
// }
//Record the newly assigned address into mem_node
int add_node_to_ll(void *allocated_heap_addr, size_t requested_byes){
	
	int error_code=SUCCESS;
	
	if(allocated_heap_addr==NULL || requested_byes <=0){
		error_code=ERROR_ADDRESS_NULL;
		return error_code;
	}
	
	mem_node* new_node = (mem_node *) malloc(sizeof(mem_node));
	new_node->alloc_address=(void *)allocated_heap_addr;
	new_node->bytes=requested_byes;
	new_node->next=NULL;
	new_node->prev=NULL;
	
	//handle first Entry	
	if(head==NULL){
	  	head=new_node;
	  	tail=new_node;
  	}
	
	else{	
		new_node->prev=tail;	
		tail->next=new_node;
		tail=new_node; 
	}
	return  error_code;
}

int delete_node_from_ll(void *mem_free){
	int error_code=SUCCESS;
	mem_node *curr=NULL, *delete_node=NULL;
	
	if(mem_free==NULL){
		error_code=ERROR_ADDRESS_NULL;
		return error_code;
	}
	
	if(head==NULL){
		error_code=ERROR_LIST_EMPTY;
		return error_code;
	}
	
	//Remove Head Node
	if(head->alloc_address==mem_free){
		delete_node=head;
		head=head->next;
		if(head){
			head->prev=NULL;
		}		
		free(delete_node);	
		return error_code;
	}

	//Remove Tail Node
	if(tail->alloc_address == mem_free){
        delete_node = tail;
        tail = tail->prev;
        tail->next = NULL;
        free(delete_node);
        return error_code;
    }

	//Remove Node in between
	curr=head;
	while(curr!=NULL){	
		if(curr->alloc_address == mem_free){
		    delete_node=curr;
			curr->prev->next=curr->next;
			curr->next->prev=curr->prev;		
			curr=curr->next;
			free(delete_node);
			return error_code;
		}
		curr=curr->next;		
	}

	if(curr==NULL){
		error_code=ERROR_NODE_NOT_FOUND;
	}
	return error_code;
}

//This is a wrapper Function to malloc
void* hmalloc(size_t requested_bytes){

	if(requested_bytes<=0){
		return NULL;
	}
	
	mem_node* alloc_address=(void *)malloc(requested_bytes);
	if(alloc_address==NULL){
		return NULL;
	}

	int error_code=add_node_to_ll(alloc_address,requested_bytes);
	if(error_code>=0){
		return alloc_address;
	}
	else{
		return NULL;
	}
}

//This is a wrapper Function to free
int hfree(void* mem_free){
	int error_code=delete_node_from_ll(mem_free);
	if(error_code>=0){
		free(mem_free);
	}
	return error_code;

}

//Print mem_rec_List
void print_leaks(){
	printf("\n-----------Memory Leakage Detector-----------------\n");
	mem_node *curr = head;
	if(curr){
		printf("\nBelow are the Memory Leaks:\n");
	}
	else{
		printf("No Memory Leaks in the Program.\n");
	}
	while(curr!=NULL){
		printf("Adress: 0X%X Size: %d Byte \n ",curr->alloc_address,curr->bytes);
		curr=curr->next;
	}
	printf("\n------------------------------------------------------\n");

}
