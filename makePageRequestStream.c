#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 * @brief			reads values in from command line, makes random page stream
 * @author  		Joshua Molden
 * @date    		5 Nov 21
 * @lastUpdated 	5 Nov 21
 * @return  		int (0 if exited normally, non-zero if issues)
 * @arg				argc - number of command line arguments passed in, including name of program
 *              	argv - the actual arguments
 *						argv[0] = name of program
 *						argv[1] = name of file you want to create. Do not need to specify what type of file it is, the program will
 *								  make it a .txt file
 *						argv[2] = how many pages a process has.
 *						argv[3] = how long the simulated page stream should be. 1000 for this project
 * @note    		None
 *****************************************************************************/
int main(int argc, char** argv) {
    // read inputs from command line as strings
	char* fileToCreate = argv[1];
	
	// how many pages to simulate. This number controls what range of numbers can be generated.
	// i.e 0 to pages
	char* pages = argv[2];
	
	// number of random pages to make, 1000 for this project
	char* numOfPagesInStream = argv[3];
	
	// convert from string to number
	int pagesInt = atoi(pages);
	int numOfPagesInStreamInt = atoi(numOfPagesInStream);
	
	// apend ".txt" to file name so it is always a .txt file
	strcat(fileToCreate, ".txt");
	
	FILE *file;
	
	// open a file to append to
	file = fopen(fileToCreate, "a");
	
	// use pagesInt for seeder
	srand(pagesInt);
	
	// create "numOfPagesInStreamInt" number of page numbers as ints between 0 and pagesInt
	for (unsigned long i = 0; i < numOfPagesInStreamInt; ++i) {
		// random number between 0 inclusive and "pagesInt" exclusive
		int page = ((int) rand() % pagesInt);
		// write number to file and start new line	
		if (i != numOfPagesInStreamInt - 1) 
		{
			fprintf(file, "%d\n", page);
		}
		else 
		{
			fprintf(file, "%d", page);
		}
	}
	
	// close file that was appended to
    fclose(file);
}
