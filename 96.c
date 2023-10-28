#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./lib/file-to-array.c"

#define int8   char
#define sint8  signed char
#define uint   unsigned int
#define int64  long long int
#define uint64 unsigned long long int

#define SUDOKU_QUANTITY 50

int
read_file(int8 *storage, int8 *filename);

int
main(int argc, char *argv[]) {

  int8 raw_data[SUDOKU_QUANTITY * 10 + 64];

  int8 sudoku_set[SUDOKU_QUANTITY][81] = {0};

  int8 i, j;

  read_file(&raw_data[0], "96_sudoku_set.txt");

  printf("%s \n", &raw_data[0]);

  return 0;

}

int
read_file(int8 *storage, int8 *filename_pt) {

  FILE *in_file_pt;

  int char_read, char_n;

  int8 i = 0;

  in_file_pt = fopen(filename_pt, "r");

  while (char_read != EOF) {

    char_read = fgetc(in_file_pt);

    char_n = char_read - 48;    

    if (char_n >= 0 && char_n <= 9) {
      
      /* printf(" %d", char_n); */

      *(storage + i) = char_n;

      i += 1;

    }

  }

}
