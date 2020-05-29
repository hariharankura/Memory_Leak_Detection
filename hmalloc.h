/*
Project Name: Memory Leakage Detector
Author :Hari Haran Kura
*/


#ifndef _H_MALLOC_
#define _H_MALLOC_

#include <stddef.h>

// void sigintHandler(int sig_num);
void* hmalloc(size_t requested_bytes);
int hfree(void*);
void print_leaks();

#endif
