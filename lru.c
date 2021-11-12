/*H**********************************************************************
* FILENAME : asciiTable.c
*
* DESCRIPTION :
*       This file prints an ascii table for data in a 2 dimensional array and a specified
*	number of rows that is taken from the command line
*
* PUBLIC FUNCTIONS :
*       void 	spacers( int columnWidth )
*	void	topAndBottom( int totalWidth )
*	void 	printData( int data[][2], int columnWidth, int numOfRows, int totalWidth )
*	void 	printTable( int data[][2], int numOfRows )
*       int     main( int argc, char** argv )
*
* NOTES :
*       This ascii table is not very flexible; if you use it incorrectly,
*	the table will not print correctly. We can make it more robust if we want to.
*
* AUTHOR :    Meagan Olson and Joshua Molden       START DATE :    3 Nov 21
*
* VERSION:
*	1.0.0
*
* LAST UPDATED:
*	4 Nov 21
*H*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*****************************************************************************
 * @brief		prints out spacers between rows
 * @author  		Joshua Molden
 * @date    		3 Nov 21
 * @lastUpdated 	4 Nov 21
 * @return  		void (prints to command line)
 * @arg			columnWidth - the width of both columns
 * @note    		This method doesn't allow for different width of columns.
 *			If this is desired, this method will have to be changed.
 *****************************************************************************/
void spacers(int columnWidth)
{
	printf("|");
	for (int j = 0; j < 2; j++)
	{
		// adds correct number of dashes for each column
		for (int i = 0; i < columnWidth; i++)
		{
			printf("-");
		}

		// if this is second column, don't print a "+" sign
		if (j == 1) 
		{
			break;
		}
		else
		{
			printf("+");
		}
	}
	printf("|\n");
}

/*****************************************************************************
 * @brief		prints out spacers without plus signs in the middle of columns
 * @author  		Joshua Molden
 * @date    		3 Nov 21
 * @lastUpdated 	4 Nov 21
 * @return  		void (prints to command line)
 * @arg			totalWidth - total width of the table.
 * @note    		Nothing special about this method
 *****************************************************************************/
void topAndBottom(int totalWidth)
{
	printf("+");
	for (int i = 0; i < totalWidth; i++)
	{
		printf("-");
	}
	printf("+\n");
}

/*****************************************************************************
 * @brief		prints out the data portion of the table
 * @author  		Joshua Molden
 * @date    		3 Nov 21
 * @lastUpdated 	4 Nov 21
 * @return  		void (prints to command line)
 * @arg			data - 2 dimensional array holding data
 *			columnWidth - the width of both columns. Doesn't allow for different size columns.
 *				      If desired, changes will need to be made.
 *			numOfRows - how many rows the table needs to be
 *			totalWidth - total width of the table
 * @note    		This method only allows for tables with two columns, and doesn't take into account if
 *			numbers are larger than the column headers. If this is desired, changes will need to be made.
 *****************************************************************************/
void printData(int data[][2], int columnWidth, int numOfRows, int totalWidth)
{
	// print spacer between column header and first row of data
	spacers(columnWidth);

	// print out data centered in the column
	for (int i = 0; i <= numOfRows; i++)
	{
		// variables to hold spaces to right and left of data values
		int leftSpaces1 = 0, rightSpaces1 = 0, leftSpaces2 = 0, rightSpaces2 = 0;

		// variables to hold the number of digits data values are
		int numOfDigits1 = 0, numOfDigits2 = 0;

		// number of frames
		int firstNum = data[i][0];

		// number of faults
		int secondNum = data[i][1];

		// calculates how many digits "firstNum" is
		do
		{
			numOfDigits1++;

			/* Remove last digit of 'firstNum' */
			firstNum /= 10;
		}
		while (firstNum != 0);

		// calculates how many digits "secondNum" is
		do
		{
			numOfDigits2++;

			/* Remove last digit of 'secondNum' */
			secondNum /= 10;
		}
		while (secondNum != 0);

		// calculations for necessary number of spaces
		leftSpaces1 = (columnWidth - numOfDigits1) / 2;
		rightSpaces1 = columnWidth - numOfDigits1 - leftSpaces1;
		leftSpaces2 = (columnWidth - numOfDigits2) / 2;
		rightSpaces2 = columnWidth - numOfDigits2 - leftSpaces2;

		// these for loops print print out the row with data values centered in the columns
		printf("|");

		for(int j = 0; j < leftSpaces1; j++)
		{
			printf(" ");
		}

		printf("%d", data[i][0]);

		for(int j = 0; j < rightSpaces1; j++)
		{
			printf(" ");
		}

		printf("|");

		for(int j = 0; j < leftSpaces2; j++)
		{
			printf(" ");
		}

		printf("%d", data[i][1]);

		for(int j = 0; j < rightSpaces2; j++)
		{
			printf(" ");
		}

		printf("|\n");

		// for last spacer, print it without a plus sign in it
		if (i == numOfRows)
		{
			topAndBottom(totalWidth);
		}
		else
		{
			spacers(columnWidth);
		}
	}
}

/*****************************************************************************
 * @brief		prints ascii table with a header, 2 coulmns with fixed sizes
 * @author  		Joshua Molden
 * @date    		3 Nov 21
 * @lastUpdated 	4 Nov 21
 * @return  		void (prints to command line)
 * @arg			data - 2 dimensional array holding data
 *			numOfRows - number of rows for the data portion of the table
 * @note    		This ascii table will only print correctly if the size of the columns are the same. If
 *			it is desired to be more "flexible," changes will need to be made.
 *****************************************************************************/
void printTable(int data[][2], int numOfRows)
{
	// array for header of table. Can replace algorithm name (i.e "FIFO") and it will center itself
	char* tableHeader[2] = {"Replacement Algorithm", "LRU"};

	// needed to center the headers dynamically
	int sizeOfLine1 = strlen(tableHeader[0]);
	int sizeOfLine2 = strlen(tableHeader[1]);

	// the ascii table is based on the assumption that these column headers will be the same lengthOfPageStream
	// if we want it to be dynamic, we will have to do some reworking.
	char* columnHeaders[2] = {"# of Frames", "# of Faults"};

	// add 4 for spaces to the right and left of headers
	int columnWidths[2] = {strlen(columnHeaders[0]) + 4, strlen(columnHeaders[1]) + 4};

	// based on ascii table being 2 columns
	int spacesBetween = 9;

	// total width (minus bars on the side) of ascii table
	int totalWidth = strlen(columnHeaders[0]) + strlen(columnHeaders[1]) + spacesBetween;

	// table header is two rows, so these take care of spaces to the right and left of first row
	int line1Left = (totalWidth - sizeOfLine1) / 2;
	int line1Right = totalWidth - sizeOfLine1 - line1Left;

	// these take care of spaces to the left and right of second row
	int line2Left = (totalWidth - sizeOfLine2) / 2;
	int line2Right = totalWidth - sizeOfLine2 - line2Left;

	// start new line for ascii table
	printf("\n");

	// first line of table
	topAndBottom(totalWidth);

	// these for loops print the table header
	printf("|");

	for (int i = 0; i < line1Left; i++)
	{
		printf(" ");
	}

	printf("%s", tableHeader[0]);

	for (int i = 0; i < line1Right; i++)
	{
		printf(" ");
	}

	printf("|\n|");

	for (int i = 0; i < line2Left; i++)
	{
		printf(" ");
	}

	printf("%s", tableHeader[1]);

	for (int i = 0; i < line2Right; i++)
	{
		printf(" ");
	}

	printf("|\n");

	topAndBottom(totalWidth);

	// prints column headers. This is based on the assumption that the column headers are the widest part
	// of the table. If we want columns to be dynamic, we will have to create a method to that 
	// prints the column headers dynamically
	printf("|  %s  |  %s  |\n", columnHeaders[0], columnHeaders[1]);

	// print data into table. "15" is based on the size of columnHeaders (11) + 4 for spaces (2 spaces to
	// to the right of the column header, and 2 spaces to the left). If we want dynamic headers, we will have
	// to change this so it isn't hard coded
	printData(data, 15, numOfRows, totalWidth);
	printf("\n");
}

/*****************************************************************************
 * @brief		simulates LRU replacement algorithm
 * @author  		Meagan Olson
 * @date    		10 Nov 21
 * @lastUpdated 	11 Nov 21
 * @return  		int (0 if page was found, 1 if page was not found and a page had to be replaced)
 * @arg			page - page that is being requested
 *			    frameSetSize - the maximum number of frames being used
 *		    	currentFrameSetSize - the current number of frames being used
 *			    frameSet - the set of frames holding page numbers
 *			    timeStamps - an array of times corresponding to the last time each page was recently used
 * @note    	None
 *****************************************************************************/
int lruAlgorithm(int page, int frameSetSize, int *currentFrameSetSize, int frameSet[], time_t timeStamps[])
{
	// First page; add it to the frame set and return that there was a page fault
	if (*currentFrameSetSize == 0)
	{
		time_t now;
		time(&now);
		frameSet[0] = page;
		timeStamps[0] = now;
		*currentFrameSetSize = 1;
		return 1;
	}

	// Check to see if the page is already loaded into a frame
	for (int i = 0; i < *currentFrameSetSize; i++) {
		if (frameSet[i] == page)
		{
			// Update the timestamp corresponding to that page
			time_t now;
			time(&now);
			timeStamps[*currentFrameSetSize] = now;
			return 0;
		}
	}

	// If there is room, load the page into an empty frame
	if (*currentFrameSetSize < frameSetSize)
	{
		time_t now;
		time(&now);
		frameSet[*currentFrameSetSize] = page;
		timeStamps[*currentFrameSetSize] = now;
		*currentFrameSetSize += 1;
		return 1;

	}

	// Find the least recently used page and replace it
	int max = 0;
	time_t current;
	time(&current);
	int index = 0;

	// Find the max time difference between now and the timestamps in the array
	// Store the index position of the least recently used page in "index"
	for (int i = 0; i < frameSetSize; i++)
	{
		int diff = difftime(timeStamps[i], current);
		if (diff <= max) continue;
		max = diff;
		index = i;
	}

	// Replace the page at the selected index position
	time_t now;
	time(&now);
	frameSet[index] = page;
	timeStamps[index] = now;
	return 1;

}

/*****************************************************************************
 * @brief		reads values in from command line, makes random page stream for testing, creates
 *			data array based on inputed parameters
 * @author  		Joshua Molden, Meagan Olson
 * @date    		3 Nov 21
 * @lastUpdated 	11 Nov 21
 * @return  		int (0 if exited normally, non-zero if issues)
 * @arg			argc - number of command line arguments passed in, including name of program
 *              	argv - the actual arguments
 *				argv[0] = name of program
 *				argv[1] = input file from which page stream should be read from. Need to make this file yet
 *				argv[2] = minimum number of frames to test replacement algorithm with (always 4 for this assignment)
 *				argv[3] = maximum number of frames to test replacement algorithm with (15, 30, 60 for this assignment)
 *				argv[4] = number of pages in process (15, 30, 60 for this assignment)
 * @note    		Simulates LRU replacement algorithm and prints results in ASCII table
 *****************************************************************************/
int main(int argc, char** argv) {

	// read inputs from command line as strings
	char* inputFile = argv[1];
	char* minNumOfFrames = argv[2];
	char* maxNumOfFrames = argv[3];
	char* numPagesPerProcess = argv[4];

	// convert from string to number
	int minNumOfFramesInt = atoi(minNumOfFrames);
	int maxNumOfFramesInt = atoi(maxNumOfFrames);
	int numPagesPerProcessInt = atoi(numPagesPerProcess);

	// number of rows of data. Also number of rows of data in ascii table
	int rows = maxNumOfFramesInt - minNumOfFramesInt;
	int data[rows][2];

	// populate from numbers in data array, may delete this later
	for (int i = minNumOfFramesInt; i <= maxNumOfFramesInt; ++i) 
	{
		// initalize frame values, subtrack "minNumOfFramesInt" in
		// order to start putting values into array at index 0
		data[i - minNumOfFramesInt][0] = i;
		// initialize fault values to 0, same reason for subtracking "minNumOfFramesInt"
		// initialize to 0 because if you don't these cells don't start at 0 by default for some reason
		data[i - minNumOfFramesInt][1] = 0;
	}

	for (int i = minNumOfFramesInt; i <= maxNumOfFramesInt; i++)
	{
		FILE *file;
		file = fopen(inputFile, "r");
		// holds number that is read from file
		int buff[1];

		// not end of file to start
		int endOfFile = 1;

		int frameSet[i];
		time_t timestamps[i];
		int currentFrameSetSize = 0;

		int numOfFaults = 0;

		do
		{
			// read int from line. fscanf returns 0 if successfully read
			int succRead = fscanf(file, "%d", buff);
			numOfFaults += lruAlgorithm(buff[0], i, &currentFrameSetSize, frameSet, timestamps);
		}
		while (!feof(file));
		data[i - 4][1] = numOfFaults;

		fclose(file);
	}

	printTable(data, rows);

	return 0;
}
