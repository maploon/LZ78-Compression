This is an implementation of LZ78 compression.

--------------------
Compilation:
g++ main.cpp LZ78.cpp tree.cpp util.cpp -o compress

Change the method in main function in main.cpp to generate uncompressor, compressor of ascii version and uncompressor of ascii version.

If a file name is given in the command line, that file will be commpressed/uncompressed. Otherwise, the default input file is "Data/input_large_original.txt"

I have already compiled the files to binary files: compress, uncompress, ascii_compress, ascii_uncompress. They are ready for use.

--------------------
Performance:

The following are some performances of byte compression.

The compression for "Data/input_large_original.txt" is about 1.43

The compression for "Data/shakespear.txt" is about 2.26

The compression for "Data/Taylor Swift - Shake It Off.mp3" is about 0.87

It seems that the algorithm compresses text file very good but not very good for other types of file.

--------------------
Explanation of source files:

LZ78.cpp includes the compress and uncompress methods. There are two different versions of compressing. One is used to compress only ascii files and the other is suitable for any file. Both methods implements the LZ78 dictionary as a tree for quick lookups.

----- LZ78.cpp -----

// First two is the ascii version of LZ78.
compress_ascii(char* filename);
uncompress_ascii(char* filename);

// The following two is the byte version of LZ78.
compress(char* filename);
uncompress(char* filename);


tree.cpp includes the basic implementation of the dictionary of LZ78

----- tree.cpp -----

struct Tree_node;
Tree_node* find_child(Tree_node *parent, char c);
Tree_node* insert_child(Tree_node *parent, char byte, int label);
void print_path(Tree_node *last_node);
char* path(Tree_node* last_node);
void print_tree(Tree_node *root);


util.cpp includes the basic bits input and output

----- util.cpp -----

void print_label(FILE* fp, int label, int max_label);
void print_letter(FILE* fp, char c);
void print_final_label(FILE* fp, int label, int max_label);
int read_label(FILE* fp, int max_label);
int read_letter(FILE* fp, char &c);
