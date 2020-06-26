#ifndef _PMEM_H_
#define _PMEM_H_

#include"pmem.h"

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/types.h>

#define MAP_SIZE 4096
#define MAP_MASK (MAP_SIZE - 1)

extern int errno;

void p_function_choice();
void introduction();
void read_p_mem();
void modify_p_mem();
void view_process_maps();
void access_mod_proc();

#endif 