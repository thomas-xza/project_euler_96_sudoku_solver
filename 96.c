#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
  
void
setup_possibilities(int8 *possibilities_pt, int8 *sudoku_pt);

void
print_possibilities(int8 *possibilities_pt, int8 *sudoku_pt);

int8
attempt_possibility(int8 *possibilities_pt, int8 *sudoku_pt);

int8
find_earliest_blank(int8 *sudoku_pt);

int8
extract_next_possibility(int8 *possibilities_pt, int8 pos);

void
write_to_sudoku(int8 *sudoku_pt, int8 pos, int8 new_value);

int8
check_sets(int8 *sudoku_pt, int8 set_type);

int8
check_columns(int8 *sudoku_pt);

int8
check_groups(int8 *sudoku_pt);

int8
check_for_duplicates(int8 *set);

int8
validate_sudoku(int8 *sudoku_pt);

void
backtrack(int8 pos, int8 *sudoku_pt);


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

  int8 possibilities[81][9] = {0};

  int8 pos, result, i = 0;

  int8 write_path[81] = {0}; 

  setup_possibilities(&possibilities[0][0], sudoku_pt);

  /* print_possibilities(&possibilities[0][0], sudoku_pt); */

  pos = attempt_possibility(&possibilities[0][0], sudoku_pt);

  write_path[i] = pos;

  i += 1;

  /* print_possibilities(&possibilities[0][0], sudoku_pt); */

  print_sudoku(sudoku_pt);

  result = validate_sudoku(sudoku_pt);

  /* if ( result == 0 ) { */

  /*   backtrack(pos, sudoku_pt); */

  /* } */

}


int8
attempt_possibility(int8 *possibilities_pt, int8 *sudoku_pt) {

  int8 pos, to_write, target, new_value;

  pos = find_earliest_blank(sudoku_pt);
  
  new_value = 1 + \
    extract_next_possibility(possibilities_pt, pos);

  write_to_sudoku(sudoku_pt, pos, new_value);
  
}


void
write_to_sudoku(int8 *sudoku_pt, int8 pos, int8 new_value) {

  *(sudoku_pt + pos) = new_value;

}


int8
find_earliest_blank(int8 *sudoku_pt) {

  int8 i = 0;

  while ( *(sudoku_pt + i) != 0 ) {

    i += 1;

  }

  printf("earliest possibility: %d\n", i);

  return i;

}


int8
extract_next_possibility(int8 *possibilities_pt, int8 pos) {

  int8 i = 0;

  while ( *(possibilities_pt + pos*9 + i) == 0 ) {

    i += 1;

  }

  printf("writing to: %d %d\n", pos, i);

  *(possibilities_pt + pos*9 + i) = 0;

  return i;  

}


int8
validate_sudoku(int8 *sudoku_pt) {

  int8 error;
  
  error = check_sets(sudoku_pt, 1);

  if ( error == 1 ) {

    return 1;

  }

  printf("error: %d \n", error);

  error = check_sets(sudoku_pt, 2);

  if ( error == 1 ) {

    return 1;

  }

  error = check_sets(sudoku_pt, 3);

  if ( error == 1 ) {

    return 1;

  }

  return 0;

}


int8
check_sets(int8 *sudoku_pt, int8 set_type) {

  int8 i, j, result, duplicate_found;

  int8 set[9] = {0};

  int8 selector_a[9] = {0, 3, 6, 27, 30, 33, 54, 57, 60};

  int8 selector_b[9] = {0, 1, 2, 9, 10, 11, 18, 19, 20};

  for ( i = 0 ; i < 9 ; i++ ) {

    for ( j = 0 ; j < 9 ; j++ ) {

      if ( set_type == 1 ) {

	/*  Horizontal rows.  */

	set[j] = *(sudoku_pt + i*9 + j);

	/* printf("%d  ", *(sudoku_pt + i*9 + j)); */

      } else if ( set_type == 2 ) {

	/*  Vertical columns.  */
	
	set[j] = *(sudoku_pt + i + j*9);

	/* printf("%d  ", *(sudoku_pt + i + j*9)); */

      } else if ( set_type == 3 ) {

	/*  3 x 3 boxes.  */

	set[j] = *(sudoku_pt + selector_a[i] + selector_b[j]);
	
	printf("%d  ", *(sudoku_pt + selector_a[i] + selector_b[j]));
	
      }

    }

    duplicate_found = check_for_duplicates(&set[0]);

    if ( duplicate_found == 1 ) {

      return 1;

    }

  }

  return 0;

}


int8
check_for_duplicates(int8 *set) {

  int8 i, j = 0;

  for ( i = 0 ; i < 8 ; i++ ) {

    /* printf("\n%d : ", *(set + i)); */

    for ( j = i + 1 ; j < 9 ; j++ ) {

      /* printf("%d,  ", *(set + j)); */

      /* printf("%d = %d,   %d = %d  \n", i, *(set + i), j, *(set + j)); */

      if ( *(set + i) == *(set + j) ) {

	return 1;

      }

    }

  }

  return 0;

}


/* int8 */
/* check_columns(int8 *sudoku_pt) { */

/*   int8 i, j, result, duplicate_found; */

/*   int8 set[9] = {0}; */

/*   for ( i = 0 ; i < 9 ; i++ ) { */

/*     for ( j = 0 ; j < 9 ; j++ ) { */

/*       /\* printf("%d  ", *(sudoku_pt + i + j*9)); *\/ */

/*     } */

/*     /\* printf("\n"); *\/ */

/*     duplicate_found = check_for_duplicates(&set[0]); */

/*     if ( duplicate_found == 1 ) { */

/*       return 1; */

/*     } */

/*   } */

/*   return 0; */
  
/* } */


/* int8 */
/* check_groups(int8 *sudoku_pt) { */

/*   int8 selector_a[9] = {0, 3, 6, 27, 30, 33, 54, 57, 60}; */

/*   int8 selector_b[9] = {0, 1, 2, 9, 10, 11, 18, 19, 20}; */

/*   int8 i, j, result, duplicate_found; */

/*   int8 set[9] = {0}; */

/*   for ( i = 0 ; i < 9 ; i++ ) { */

/*     for ( j = 0 ; j < 9 ; j++ ) { */

/*       set[j] = *(sudoku_pt + selector_a[i] + selector_b[j]); */

/*       printf("%d  ", *(sudoku_pt + selector_a[i] + selector_b[j])); */

/*     } */

/*     /\* printf("\n"); *\/ */

/*     duplicate_found = check_for_duplicates(&set[0]); */

/*     if ( duplicate_found == 1 ) { */

/*       return 1; */

/*     } */

/*   } */

/*   return 0; */
  
/* } */


void
backtrack(int8 pos, int8 *sudoku_pt) {

  

}


void
print_possibilities(int8 *possibilities_pt, int8 *sudoku_pt) {

  int i, j;

  for ( i = 0 ; i < 81 ; i++ ) {

    printf("%d : ", *(sudoku_pt + i));

    for ( j = 0 ; j < 9 ; j++ ) {

      printf("%d ", *(possibilities_pt + i*9 + j));

    }

    printf("    %d", i);

    printf("\n");

  }

}

void
setup_possibilities(int8 *possibilities_pt, int8 *sudoku_pt) {

  int8 known_value;

  int i, j;

  for ( i = 0 ; i < 81 ; i++ ) {

    known_value = *(sudoku_pt + i);

    if ( known_value == 0 ) {

      memset((possibilities_pt + i * 9), 1, 9);

    } else {

      memset((possibilities_pt + i * 9), 0, 9);

      /* *(possibilities_pt + i * 9 + known_value - 1) = 1; */

    }

  }
  
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
