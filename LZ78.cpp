#include "tree.h"
#include "LZ78.h"
#include "util.h"

using namespace std;

void compress_ascii(char* filename){
    FILE* input_fp = fopen(filename, "r"); // open a ascii file to compress
    if (input_fp == NULL) {
        cerr << "File not found\n"; // if the file can't be found under current directory
    }

    /* generate output file name */
    char* pch;
    pch = strrchr(filename, '.');
    int len = pch-filename;
    char* output_filename;
    if (len >0) {
        output_filename = new char[len+6];
        strncpy(output_filename, filename, len);
        output_filename[len] = '\0';
        strcat(output_filename, ".ascii");
    }
    else{
        output_filename = new char[100];
        strncpy(output_filename, filename, 100);
        strcat(output_filename, ".ascii");
    }

    FILE* output_fp = fopen(output_filename, "w"); // output compressed file with .ascii suffix


    Tree_node* root = new Tree_node();

    char ch;
    int ch_int;
    Tree_node* current = root;
    int label = 0;

    while ((ch_int = fgetc(input_fp)) != -1) {
        ch = (char) ch_int;

        if(find_child(current, ch) != NULL) {
            current = find_child(current, ch);
        }
        else {
            Tree_node* child = insert_child(current, ch, ++label);

            fprintf(output_fp, "%d", current->label);
            fputc((int) ' ', output_fp);
            fputc((int) ch, output_fp);

            current = root;
        }
    }

    fprintf(output_fp, "%d\n", current->label);

    fclose(input_fp);
    fclose(output_fp);
}


void uncompress_ascii(char* filename){
    FILE* input_fp = fopen(filename, "r"); // open a ascii file to compress
    if (input_fp == NULL) {
        cerr << "File not found\n"; // if the file can't be found under current directory
    }

    /* generate output file name */
    char* pch;
    pch = strrchr(filename, '.');
    int len = pch-filename;
    char* output_filename;
    if (len >0) {
        output_filename = new char[len+4];
        strncpy(output_filename, filename, len);
        output_filename[len] = '\0';
        strcat(output_filename, ".txt");
    }
    else{
        output_filename = new char[100];
        strncpy(output_filename, filename, 100);
        strcat(output_filename, ".txt");
    }

    FILE* output_fp = fopen(output_filename, "w"); // output compressed file with .ascii suffix


    // declarations
    Tree_node* root = new Tree_node();

    char ch;
    Tree_node* current = root;
    int p_index;
    int label = 0;
    vector<Tree_node*> tree;
    tree.push_back(root);

    // uncompress process
    while (fscanf(input_fp, "%d", &p_index)) {

        // char* path = path(tree[p_index]);
        fprintf(output_fp, "%s", path(tree[p_index]));

        int blank = fgetc(input_fp); // get a blank space
        if (blank != ' ') break; // should get a space. If not, means reached the end-of-file.

        int ch_int = fgetc(input_fp);
        if(ch_int == -1) break;
        ch = (char) ch_int; // get the byte for the node

        fprintf(output_fp, "%c", ch);
        Tree_node* current = insert_child(tree[p_index], ch, ++label);
        tree.push_back(current);
    }

    fclose(input_fp);
    fclose(output_fp);
}

void compress(char* filename){
    FILE* input_fp = fopen(filename, "r"); // open a ascii file to compress
    if (input_fp == NULL) {
        cerr << "File not found\n"; // if the file can't be found under current directory
    }

    /* generate output file name */
    char* pch;
    pch = strrchr(filename, '.');
    int len = pch-filename;
    char* output_filename;
    if (len >0) {
        output_filename = new char[len+6];
        strncpy(output_filename, filename, len);
        output_filename[len] = '\0';
        strcat(output_filename, ".comp");
    }
    else{
        output_filename = new char[100];
        strncpy(output_filename, filename, 100);
        strcat(output_filename, ".comp");
    }

    FILE* output_fp = fopen(output_filename, "w"); // output compressed file with .ascii suffix


    Tree_node* root = new Tree_node();

    char ch;
    int ch_int;
    Tree_node* current = root;
    int label = 0;

    while ((ch_int = fgetc(input_fp)) != -1) {
        ch = (char) ch_int;

        if(find_child(current, ch) != NULL) {
            current = find_child(current, ch);
        }
        else {

            // fprintf(output_fp, "%d", current->label);
            // fputc((int) ' ', output_fp);
            // fputc((int) ch, output_fp);

            print_label(output_fp ,current->label, label);

            print_letter(output_fp, ch);

            Tree_node* child = insert_child(current, ch, ++label);

            current = root;
        }
    }

    // fprintf(output_fp, "%d\n", current->label);
    print_final_label(output_fp, current->label, label);

    fclose(input_fp);
    fclose(output_fp);
}

void uncompress(char* filename){
    FILE* input_fp = fopen(filename, "r"); // open a ascii file to compress
    if (input_fp == NULL) {
        cerr << "File not found\n"; // if the file can't be found under current directory
    }

    /* generate output file name */
    char* pch;
    pch = strrchr(filename, '.');
    int len = pch-filename;
    char* output_filename;
    if (len >0) {
        output_filename = new char[len+4];
        strncpy(output_filename, filename, len);
        output_filename[len] = '\0';
        strcat(output_filename, ".txt");
    }
    else{
        output_filename = new char[100];
        strncpy(output_filename, filename, 100);
        strcat(output_filename, ".txt");
    }

    FILE* output_fp = fopen(output_filename, "w"); // output compressed file with .ascii suffix


    // declarations
    Tree_node* root = new Tree_node();

    char ch;
    Tree_node* current = root;
    int p_index;
    int label = 0;
    vector<Tree_node*> tree;
    tree.push_back(root);

    // uncompress process
    while ((p_index = read_label(input_fp, label)) >= 0) {

        fprintf(output_fp, "%s", path(tree[p_index]));

        int ch_int = read_letter(input_fp, ch);
        if(!ch_int) break;

        fprintf(output_fp, "%c", ch);
        Tree_node* current = insert_child(tree[p_index], ch, ++label);
        tree.push_back(current);
    }

    fclose(input_fp);
    fclose(output_fp);
}

// // test client
// int main(int argc, char const *argv[]) {
// 
//     char* comp = "input_large.comp";
//     uncompress(comp);
//     return 0;
// }
