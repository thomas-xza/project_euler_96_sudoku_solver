#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "./lib/file_to_array.c"

#define int8   char
#define sint8  signed char
#define uint   unsigned int
#define int64  long long int
#define uint64 unsigned long long int

int
main(int argc, char *argv[]) {

  uint64 x;

  uint64 sum = 0;

  int8 int_triangle;

  /* uint64 *squares = malloc(sizeof(int64) * SQUARESTOTAL); */

  /* gen_squares(squares, SQUARESTOTAL); */

  for ( x = 2 ; x < UPPERLIMIT ; x++ ) {

    int_triangle = investigate_n(x, 1);

    if ( int_triangle == 1 ) {

      printf("%llu  +\n", x);

      sum += x;

    } else {

      int_triangle = investigate_n(x, 2);

      if ( int_triangle == 1 ) {

	printf("%llu  -\n", x);

	sum += x;

      }
    
    }

  }

  printf("sum: %llu\n", sum);

}
