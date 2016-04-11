#include <cstring>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>

#ifndef __Tree__
#define  __Tree__

struct Tree_node{
   int label;
   char byte;
   Tree_node *first_child;
   Tree_node *sibling;
   Tree_node *parent;

   Tree_node(){
       label = 0;
       byte = '\0';
       parent = NULL;
       sibling = NULL;
       first_child = NULL;
   };  // Constructor (structs can have them too)

};

Tree_node* find_child(Tree_node *parent, char c);

Tree_node* insert_child(Tree_node *parent, char byte, int label);

void print_path(Tree_node *last_node);

char* path(Tree_node* last_node);

void print_tree(Tree_node *root);

#endif
