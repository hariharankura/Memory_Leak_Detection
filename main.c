/*
Project Name: Memory Leak Detector
Author :Hari Haran Kura
*/

#include	<stdio.h>
#include	<stdint.h>
#include 	<signal.h>
#include "hmalloc.h"

int main(){
	// signal(SIGINT,sigintHandler);	
	
	printf("Hello World\n");
	int *iptr =(int*)hmalloc(10*sizeof(int));
	double *dptr =(double*)hmalloc(10*sizeof(double));
	char *cptr =(char*)hmalloc(10*sizeof(char));
		
	hfree(iptr);
	hfree(dptr);
	hfree(cptr);
	
	print_leaks();
	while(1);	
return 0;
}
