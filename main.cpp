#include "LZ78.h"

int main(int argc, char const *argv[]) {

    char* filename = new char[255];
    if (argc > 1) {
        strncpy(filename, argv[1], 255);
    }
    else {
        filename = "Data/input_large_original.txt"; // Default file;
    }


    compress(filename);

    return 0;
}
