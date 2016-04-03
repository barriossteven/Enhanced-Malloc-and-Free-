#include "malloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char myblock[5000];

struct node* head;//creates head

void *mymalloc(unsigned int size, char* filename, int line){
	if(head ==NULL){ //if malloc has never been called
		//initialize head and place at front of array
		//printf("size of struct node %lu\n", sizeof(struct node));
		head = (struct node*)myblock; //create a block struct
		head->next = NULL; // set prev and next to null since they point to nothing yet
		head->prev = NULL; 
		head->isFree = 1; // the next next block of memory is free
		head->size = 5000-sizeof(struct node); //the size of the block of memeory is the total size of the space minus the size of the struct

	}

	struct node* curr = head; //sets current to the head
	struct node* next; //creates a next node


	while(curr != NULL){ //find the next block of memory that is free
		if(curr->isFree == 0){ //current is not free, continue to next block of memeory
			curr = curr->next;
			continue;
		}else if(curr->size <size){ //if the amount of memory is less than the size of the current block, continue to next block of memory
			curr = curr->next;
			continue;
		}else if(curr->next != NULL && curr->size >= size){ //if the block of memory after current is not null and the amount of memory needed is greater than the current block 
			return (char*)curr + sizeof(struct node); //return a pointer to this block of memory 
		}else if(curr->size > (size + sizeof(struct node))) { //if the current block of memory is greater than the size of the node to be allocated 
			next = (struct node*)((char*)curr + sizeof(struct node) + size); //create the new node with the size of data to be allocated and the size of the node struct
			next->prev = curr; //set the new node's previous to the current node
			next->next = curr->next; //seet the new node's next to the node after current, so placing the node after the current node 
			if(curr->next != NULL){ // if the space after current is null 
				curr->prev = next->next; 
			}
			next->isFree = 1; //the new node is now free 
			next->size = curr->size - sizeof(struct node) - size; 
			curr->isFree = 0; //current is no longer free
			curr->next = next;//set current's next to the new node
			curr->size = size; 
			return (char*)curr + sizeof(struct node); // return pointer to the node
		}
		curr = curr->next; // continue to next node until find the block of memory is free
	}

		printf("ERROR IN MALLOC. NOT ENOUGH SPACE FOR REQUEST. '%s' ON LINE '%d'\n",filename,line);//could not allocate space and return a null pointer
	return NULL;


}

void myfree(void* ptr, char* filename, int line){
	struct node* curr = head;
	struct node* p, *next;
	struct node* previous = NULL;
	int merge = 0;
	/****************************error cases*************************************************/
	if(head == NULL){
		printf("list empty, error %s at %d\n",filename, line);
		return;
	}
	if(ptr == NULL){
		printf("ERROR IN myfree. POINTER IS NULL. FREE FAILED IN FILE '%s' ON LINE '%d'\n",filename,line);
		return;
	}
	/******************************************************************************************/

	p = (struct node*)((char*)ptr - sizeof(struct node)); //create a node that is just the size of the data allocated without the node information
	while(curr != NULL){ //while the current node is not null
		if( p < curr){ //if the address of the memory to be freed is less than the current node than there is an error
			printf("ERROR. FREE FAILED IN FILE. POINTER IS NOT BEGINNING OF MEMORY ALLOCATED '%s' ON LINE '%d'\n", filename,line);
			return;
		}else if(curr == p){ //if we have found the address of the memory to be freed
			if(curr->isFree == 1){ //the block is already free, return an error, doesn't allow a user to free something twice
				printf("ERROR. FREE FAILED IN FILE. POINTER IS ALREADY FREE'%s' ON LINE '%d'\n", filename,line);
				return;
			}
			memset(ptr, 0, p->size); //set all the values in pointer memory block to 0 
			p->isFree = 1; // set the memory block to indicate that it is now free
			if(previous != NULL && previous->isFree == 1){ //merge the previous block of memeory and pointer's block of memeory if previous is also free 
				previous->size += sizeof(struct node) + curr->size; // previous's size is now the size of the node and pointer's size (current)
				previous->next = curr->next; //previous's next is now the node after current (the pointer to be freed)
				if(curr->next != NULL){ //if the next node is null after current
					curr->next->prev = previous; //insert the previous inbetween current and the last node 
				}
				merge = 1; //set merge to 1 to indicate that the memory has been freed 
			}else{
				previous = curr; //if not previous is now equal to current 
			}

			next = curr->next; //set the next node to the node after current 
			if(merge ==1){ //if previous and the pointer's block of memory has been merged 
				if(next != NULL && next->isFree == 1){ //if next is not null and it is free, merge the previously merged block of memory and this block of memory 
					previous->size += sizeof(struct node) + next->size; //previous's size now include the size of next's
					previous->next = next->next; 
					if(next->next != NULL){
						next->next->prev = previous;
					}

				}	
			}else if(merge == 0){ //if previous and pointer's memory blocks have not been merged 
				if(next != NULL && next->isFree == 1){ //if next is not null and it is free, merge the pointer's memory block and the 
					curr->size += sizeof(struct node) + next->size; // merge pointer's and the memory after it 
					curr->next = next->next;
					if(next->next != NULL){
						next->next->prev = curr;
					}

				}
			} 
			return;
		}else{ //if can not merge continue to move pointers 
			previous = curr;
			curr = curr->next; 
		}
	}

	printf("ERROR. FREE FAILED IN FILE. POINTER WAS NEVER ALLOCATED. '%s' ON LINE '%d'\n", filename,line);
	return;
}



