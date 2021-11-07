#include <stdio.h>

/*****************************************************************************
 * @brief       Reads ints in from a file
 * @author      Joshua Molden
 * @date        5 Nov 21
 * @lastUpdated 5 Nov 21
 * @return      void (prints nums to command line)
 * @arg         fileName - name of the file to read
 * @note        None
 *****************************************************************************/
void readFile(char* fileName)
{
	FILE *file;
	file = fopen(fileName, "r");
	// holds number that is read from file
	int buff[1];
	
	// not end of file to start
	int endOfFile = 1;
	
	do
	{
		// read int from line. fscanf retruns 0 if successfully read
		int succRead = fscanf(file, "%d", buff);
		printf("%d\n", buff[0]);
	}
	while (!feof(file));
}

/*****************************************************************************
 * @brief			reads values from a file
 * @author  		Joshua Molden
 * @date    		5 Nov 21
 * @lastUpdated 	5 Nov 21
 * @return  		int (0 if exited normally, non-zero if issues)
 * @arg				argc - number of command line arguments passed in, including name of program
 *              	argv - the actual arguments
 *						argv[0] - name of program
 *						argv[1] = name of file to read. Include the extension of the file you want to read
 * @note    		None
 *****************************************************************************/
int main(int argc, char** argv) {
    char* fileName = argv[1];
	readFile(fileName);
}