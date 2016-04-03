#ifndef MALLOC_H
#define MALLOC_H

struct Node;

struct node{
	struct node *next;
	struct node *prev;
	unsigned int size;
	void* data;
	unsigned int isFree;
};


void* mymalloc(unsigned int size,char* filename, int line);

void myfree(void* ptr, char*filename, int line);

#endif
