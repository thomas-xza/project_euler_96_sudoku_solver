#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./lib/file-to-array.c"

#define int8   char
#define sint8  signed char
#define uint   unsigned int
#define int64  long long int
#define uint64 unsigned long long int

#define SUDOKU_QUANTITY 2

void
read_file(int8 *storage, int8 *filename);

int
load_sudoku(int8 *raw_data, int8 *sudoku);

void
print_sudoku(int8 *sudoku_pt);

void
solve_sudoku(int8 *sudoku_pt);
  
int
main(int argc, char *argv[]) {

  int8 raw_data[SUDOKU_QUANTITY * 128] = {0};

  int8 sudoku[81] = {0};

  int i, j;

  read_file(&raw_data[0], "96_sudoku_set.txt");

  for ( i = 0 ; i < SUDOKU_QUANTITY * 81 ; i += 81 ) {

    load_sudoku(&raw_data[i], &sudoku[0]);

    solve_sudoku(&sudoku[0]);

    /* print_sudoku(&sudoku[0]); */

  }

  return 0;

}


void
solve_sudoku(int8 *sudoku_pt) {

  int8 possibilities[81][9] = {0}

  /*  setup possibilities  */

    /*  begin brute-force  */

    

}

void
print_sudoku(int8 *sudoku_pt) {

  int i;

  for ( i = 0 ; i < 81 ; i++ ) {

    printf("%d ", *(sudoku_pt + i));

    if ( (i+1) % 9 == 0 ) {

      printf("\n");

    }

  }

  printf("\n");
  
}


int
load_sudoku(int8 *raw_data_pt, int8 *sudoku_pt) {

  int i;

  for ( i = 0 ; i < 81 ; i++ ) {

    *(sudoku_pt + i) = *(raw_data_pt + i);

  }

}


void
read_file(int8 *storage, int8 *filename_pt) {

  FILE *in_file_pt;

  int i = 0;

  int8 char_n, char_read;

  in_file_pt = fopen(filename_pt, "r");

  while (char_read != EOF) {

    char_read = fgetc(in_file_pt);

    char_n = char_read - 48;

    if (char_n >= 0 && char_n <= 9) {
      
      *(storage + i) = char_n;

      i += 1;

    }

  }

}
