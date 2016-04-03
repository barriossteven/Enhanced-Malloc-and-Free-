#include<stdio.h>
#include<stdlib.h>
#include"malloc.h"
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)


int main(int argc, char** argv){
	/*printf("THIS IS V\n");
	char *v;
	free(v);
		
	char *y;
	y =(char*) malloc(500);	

	char *p;
	p =(char*) malloc(32);
	
	char *ti;
	ti =(char*) malloc(232);
	
	char *vff;
	vff =(char*) malloc(234);
	free(v);
	printf("this is v\n");
	v = (char*) malloc(4980);
	*/


/*char *y;
y = (char*)malloc(50);

char *x;
x = (char*)malloc(50);

char *z;
z = (char*)malloc(50);

free(y);
free(x);
free(z);
*/
/* char *y;
y = (char*)malloc(4980);

char *z;
y = (char*)malloc(500);
*/
/* char *y;
y = (char*)malloc(4980);

char *z;
free(z);
*/ 

/*
char *v;
free(v); */

char *y;
y = (char*)malloc(1000);

char *x;
x = (char*)malloc(500);

char *z;
z = (char*)malloc(50);

char *b;
b = (char*)malloc(50);

char *a;
a = (char*)malloc(3000);


free(z);
free(b);

char *c;
c = (char*)malloc(70);



	return 0;

}
