#include "util.h"

using namespace std;

/* this first figures out how many bits it takes to write down max_label, and
   then writes label as a number using that many bits. (e.g., if max_label
   is 7, then it would print out "3" as 011, and if max_label was 9, then
   it would print out "3" as 0011.
   Since you can't print out less than one byte, it stores in "buffer"
   things that haven't actually been printed out yet.
 */
void print_label(FILE* fp, int label, int max_label) {
  static unsigned char buffer = 0;
  static int how_full = 0;   // when this gets to 8, print out buffer.
  int mask;

  if (max_label == 0) return;
  for(mask = 1; max_label > 1; max_label /=2) mask *= 2; // get high order bit

  for(; mask != 0; mask /= 2) {
    buffer = buffer * 2 + ((label & mask) / mask);
    ++how_full;
    if (how_full == 8) {
      fwrite(&buffer, sizeof(unsigned char), 1, fp);
      buffer = 0;
      how_full = 0;
    }
  }
}

void print_letter(FILE* fp, char c) {
  print_label(fp, (unsigned char) c, 128);
}

/* print out last label and flush */
void print_final_label(FILE* fp, int label, int max_label) {
  print_label(fp, label, max_label);
  print_label(fp, 0, 127);
}

/* reads in labels printed out using print_label.
   returns -1 on end-of-file, but this should only happen when called by
   read_letter.
 */
int read_label(FILE* fp, int max_label) {
  static int buffer;
  static int how_full = 0;
  int label;

  for(label=0; max_label != 0; max_label /= 2) {
    if (how_full == 0) {
      buffer = fgetc(fp);  // C-ism to handle objectcenter bug
      if (buffer == EOF) return -1;
      how_full = 8;
    }
    label = label * 2 +  ((buffer & 128) / 128);
    buffer *=2;
    how_full--;
  }
  return label;

}

/* use like cin.get(c). returns 1 normally, or 0 on end of file */
int read_letter(FILE* fp, char &c) {
  int val = read_label(fp, 128);
  if (val == -1) return 0;
  c = (char) val;
  return 1;
}

// int main(int argc, char const *argv[]) {
//     print_label(5, 16);
//     print_label(5, 16);
//     print_label(5, 16);
//     print_label(5, 16);
//
//     return 0;
// }
