
void file_to_array_of_ints(int *ints_init_ptr, char *filename);

void file_to_array_of_int8(char *int8_init_ptr, char *filename);


/*  SAMPLE USAGE: initialize array and pass pointer to it  */
  
/*  +1 element for null pointer  */

/*  static int quantity = 664579 +1; */

/*  static int quantity = 5761455 +1;  */
 
/*  int primes[quantity]; */


/* int main() { */

/*   file_to_array_of_ints(&primes[0], "./lib/primes-below-10.tx); */

/* } */


void file_to_array_of_ints(int *ints_init_ptr, char *filename) {

  FILE *ints_file;

  int i = 0;

  if ((ints_file = fopen(filename, "r"))) {

    while ( fscanf(ints_file, "%d", ints_init_ptr + i) != EOF) {

      i++;

    }

    fclose(ints_file);

    *(ints_init_ptr + i) = '\0';

    printf("read ints from file, to %p \n", ints_init_ptr);

  }

}


void file_to_array_of_int8(char *int8_init_ptr, char *filename) {

  FILE *int8_file;

  int i = 0;

  if ( (int8_file = fopen(filename, "r")) ) {

    while ( fscanf(int8_file, "%s", int8_init_ptr + i) != EOF) {

      i++;

    }

    fclose(int8_file);

    *(int8_init_ptr + i) = '\0';

    printf("read int8 from file, to %p \n", int8_init_ptr);

  }

}
