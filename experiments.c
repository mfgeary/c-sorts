#include <stdio.h>
#include <stdlib.h>

#include "array_util.h"
#include "sorts.h"

//Written by Marion Geary
//I used experiment.c from Lab 2 written by Dr. Pohly as a resource
//for this code. I also used C for Java Programmers: A Primer
// by Charlie McDowell as a resource, particularly in reading
// the data to a file. I also referenced this website:
//https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_418.html
//to understand the timeval struct.

// turn matrix data into csv
void toCSV(int row[17][8], int n, int m, FILE* out);

int main(int argc, char* argv[])
{
  FILE* out_file;

  //error handling
  if(argc != 2) {
    printf("Usage: ./experiment outputFile\n");
    exit(1);
  }

	int i;
	long fore, aft;
	int compars;

	int master[500000];
	int copy[500000];

	int matrix[17][8];

	//possible array sizes
	int sizes[] = {10, 25, 50, 75, 100, 150, 250, 500, 750, 1000, 2500, 5000, 7500, 10000, 15000, 20000, 25000};

	//create table of number of comparisons for all sort functions
	//for small array sizes
	printf("\tbubble\t\tselection\tinsertion\tshell\tmerge\tquick\n");
	printf("comparisons\n");

	for (i = 0; i < 5; i++) {
	  printf("%d:", sizes[i]);
	  random_array(master, sizes[i]);

	  copy_array(master, copy, sizes[i]);
	  compars = bubbleSort(copy, sizes[i]);

	  printf("\t%d", compars);

	  copy_array(master, copy, sizes[i]);
	  compars = selectionSort(copy, sizes[i]);
	
	  printf("\t\t%d", compars);

	  copy_array(master, copy, sizes[i]);
	  compars = insertionSort(copy, sizes[i]);

	  printf("\t\t%d", compars);

	  copy_array(master, copy, sizes[i]);
	  compars = shellSort(copy, sizes[i]);

	  printf("\t\t%d", compars);

	  copy_array(master, copy, sizes[i]);
	  compars = mergeSort(copy, sizes[i]);

	  printf("\t%d", compars);

      	  copy_array(master, copy, sizes[i]);
	  compars = quickSort(copy, sizes[i]);

	  printf("\t%d\n", compars);

	}

	// Create table of runtimes for all sort functions
	//for all array sizes. Store the runtimes in a matrix.
	printf("running times\n");
	for (i = 0; i < 17; i++) {

	  // first column of matrix is an index
	  matrix[i][0] = i;
	  
	  random_array(master, sizes[i]);
	  printf("%d:", sizes[i]);

	  // second column of matrix is array size
	  matrix[i][1] = sizes[i];

	  copy_array(master, copy, sizes[i]);
	  fore = get_time_microsec();
	  bubbleSort(copy, sizes[i]);
	  aft = get_time_microsec();

	  if(aft-fore < 10000000){
	    printf("\t%ld", aft-fore);
	  } else {
	    printf(" %ld", aft-fore);
	  }

	  matrix[i][2] = aft-fore;

	  copy_array(master, copy, sizes[i]);
	  fore = get_time_microsec();
	  selectionSort(copy, sizes[i]);
	  aft = get_time_microsec();

	  if(aft-fore < 10000000){
	    printf("\t\t%ld", aft-fore);
	  } else {
	    printf("\t%ld", aft-fore);
	  }

	  matrix[i][3] = aft-fore;

	  copy_array(master, copy, sizes[i]);
	  fore = get_time_microsec();
	  insertionSort(copy, sizes[i]);
	  aft = get_time_microsec();

    	  if(aft-fore < 10000000){
	    printf("\t\t%ld", aft-fore);
	  } else {
	    printf("\t%ld", aft-fore);
	  }

	  matrix[i][4] = aft-fore;
       
	  copy_array(master, copy, sizes[i]);
	  fore = get_time_microsec();
	  shellSort(copy, sizes[i]);
	  aft = get_time_microsec();

	  if(aft-fore < 10000000){
	    printf("\t\t%ld", aft-fore);
	  } else {
	    printf("\t%ld", aft-fore);
	  }

	  matrix[i][5] = aft-fore;
	  
	  copy_array(master, copy, sizes[i]);
	  fore = get_time_microsec();
	  mergeSort(copy, sizes[i]);
	  aft = get_time_microsec();

	  printf("\t%ld", aft-fore);

     	  matrix[i][6] = aft-fore;

	  copy_array(master, copy, sizes[i]);
	  fore = get_time_microsec();
	  quickSort(copy, sizes[i]);
	  aft = get_time_microsec();

	  printf("\t%ld\n", aft-fore);

	  matrix[i][7] = aft-fore;

	}

	//error handling
	out_file = fopen(argv[1], "w");
	if(out_file == NULL){
	  fprintf(stderr, "ERROR: couldn't open %s for writing\n", argv[1]);
	  exit(1);
	}

	//turn matrix into csv
	toCSV(matrix, 17, 8, out_file);

	return 0;
}


//Turn a matrix into a csv file. n and m are the dimensions
// of the matrix
void toCSV(int row[17][8], int n, int m, FILE* out) {
  int i, j;
  for(j = 0; j < n; j++) {
    for(i = 0; i < m; i++) {
      fprintf(out, "%d, ", row[j][i]);
    }
    fprintf(out, "\n");
  }
}
