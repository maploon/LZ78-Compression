#include <iostream>
#include <cstdio>

#ifndef __UTIL__
#define __UTIL__

void print_label(FILE* fp, int label, int max_label);

void print_letter(FILE* fp, char c);

void print_final_label(FILE* fp, int label, int max_label);

int read_label(FILE* fp, int max_label);

int read_letter(FILE* fp, char &c);

#endif
