/*H**********************************************************************
 * FILENAME : project2WithAllAlgorithms.c
 *
 * DESCRIPTION :
 *       This file tests four different page replacement algorithms
 *
 * NOTES : None
 *
 * AUTHOR :    Joshua Molden, Andrew Voss, Dylan Martie, Meagan Olson
 * 
 * START DATE :    3 Nov 21
 *
 * VERSION:
 *       1.0.0
 *
 * LAST UPDATED:
 *       12 Nov 21
 * H*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stddef.h>

/*****************************************************************************
* @brief               prints out spacers between rows
* @author              Joshua Molden
* @date                3 Nov 21
* @lastUpdated         4 Nov 21
* @return              void (prints to command line)
* @arg                 columnWidth - the width of both columns
* @note                This method doesn't allow for different width of columns.
*                      If this is desired, this method will have to be changed.
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
* @brief               prints out spacers without plus signs in the middle of columns
* @author              Joshua Molden
* @date                3 Nov 21
* @lastUpdated         4 Nov 21
* @return              void (prints to command line)
* @arg                 totalWidth - total width of the table.
* @note                Nothing special about this method
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
* @brief               prints out the data portion of the table
* @author              Joshua Molden
* @date                3 Nov 21
* @lastUpdated         4 Nov 21
* @return              void (prints to command line)
* @arg                 data - 2 dimensional array holding data
*                      columnWidth - the width of both columns. Doesn't allow for different size columns.
*                                    If desired, changes will need to be made.
*                      numOfRows - how many rows the table needs to be
*                      totalWidth - total width of the table
* @note                This method only allows for tables with two columns, and doesn't take into account if
*                      numbers are larger than the column headers. If this is desired, changes will need to be made.
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
* @brief               prints ascii table with a header, 2 coulmns with fixed sizes
* @author              Joshua Molden
* @date                3 Nov 21
* @lastUpdated         4 Nov 21
* @return              void (prints to command line)
* @arg                 data - 2 dimensional array holding data
*                      numOfRows - number of rows for the data portion of the table
* @note                This ascii table will only print correctly if the size of the columns are the same. If
*                      it is desired to be more "flexible," changes will need to be made.
*****************************************************************************/
void printTable(int data[][2], int numOfRows, char* tableName)
{
        // array for header of table. Can replace algorithm name (i.e "FIFO") and it will center itself
        char* tableHeader[2] = {"Replacement Algorithm", tableName};

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
}

/*****************************************************************************
* @brief               simulates FIFO replacement algorithm
* @author              Joshua Molden
* @date                5 Nov 21
* @lastUpdated         6 Nov 21
* @return              int (0 if page was found, 1 if page was not found and had to be replace a page)
* @arg                 page - page that is being requested
*                      maxSizeOfQueue - the maximum size a queue can be
*                      currentSizeOfQueue - the current size the queue is
*                      front - the index to the "front" of the queue (item to be removed if page isn't found)
*                      rear - the index to the "rear" of the queue (item most recently added)
*                      queue - the queue holding page numbers
* @note                None
*****************************************************************************/
int fifoAlgorithm(int page, int maxSizeOfQueue, int *currentSizeOfQueue, int *front, int *rear, int queue[])
{

        // first page
        if(*currentSizeOfQueue < 0)
        {
                queue[0] = page;
                *front = *rear = 0;
                *currentSizeOfQueue = 1;
                // return 1 to capture that there was a page fault
                return 1;
        }
        else
        {
                // this is created so that as we cycle through the array, we aren't changing the actual
                // index of the front of the queue. modifyFront will be the next index into the queue to check if
                // it equals the specified page we are looking for
                int modifyFront = *front;

                // cycles through queue looking to see if page is in the queue, if not, put it in the queue
                for (int i = *currentSizeOfQueue - 1; i >= 0; i--)
                {
                        // if in queue, return 0 to show there wasn't a page fault
                        if (queue[modifyFront] == page)
                        {
                                return 0;
                        }
                        else if (i != 0)        // if we haven't cycled through the queue yet, do this
                        {
                                // if next index will be an illegal bound, set it to the "0th" index
                                if (modifyFront + 1 == maxSizeOfQueue)
                                {
                                        modifyFront = 0;
                                }
                                else    // else, set next index to modifyFront + 1
                                {
                                        modifyFront++;
                                }
                                // continue to next iteration of for loop since the page wasn't found and we haven't cycled
                                // through the queue yet
                                continue;
                        }
                        else    // cycled through queue and page not found
                        {
                                // if this is true, front is set to the last legal index, so set the front back to the "0th" index
                                if (*front == maxSizeOfQueue - 1)
                                {
                                        *rear = *front;
                                        *front =  0;
                                        // replace page in "front" of queue with the page number
                                        queue[*front] = page;
                                }
                                else if (*currentSizeOfQueue != maxSizeOfQueue) // this takes care of fully populating the queue before trying to replace pages already in the queue or adding the same page twice
                                {
                                        queue[*rear + 1] = page;
                                        *rear = *rear + 1;
                                        *currentSizeOfQueue = *currentSizeOfQueue + 1;
                                }
                                else    // normal replacement that adjusts front and pack accordingly
                                {
                                        *rear = *front;
                                        queue[*front + 1] = page;
                                        *front = *front + 1;
                                }
                                // return 1 to indicate there was a page fault
                                return 1;
                        }
                }
        }

}

/*****************************************************************************
* @brief               Updates circular frame buffer to next position
* @author              Dylan Martie
* @date                5 Nov 21
* @lastUpdated         5 Nov 21
* @return              integer
* @arg                         pointer - the current position of the pointer
                                frameSize - the # of frames in the current cycle
* @note                Utility function
*****************************************************************************/
int updatePointer(int pointer, int frameSize) {
        // Reset pointer back to beginning
        if ((pointer + 1) >= frameSize) {
                pointer = 0;
        }
        else {
                pointer += 1;
        }
        return pointer;
}

/*****************************************************************************
* @brief               Predicts frame to replace
* @author              Andrew Voss
* @date                11 Nov 21
* @lastUpdated         11 Nov 21
* @return              int frameNum
* @arg                         pageRequest - pages that is being requested
*                              numOfPages - number of pages
*                              freq[] - frequency of each request
*                              frames[] - current frames
*                              frameSize - size of frames
*                              index - index of the page request
* @note                None
*****************************************************************************/
int predict(int pageRequest[], int numberOfPages, int freq[], int frames[], int frameSize, int index, int *frameBufferSize){
        int res = -1;
        int farthest = index;

        for(int i = 0; i < frameSize; i++) {
                if(freq[(int) frames[i]] < 1)
                        return i;

                // Find page that won't be used for the longest time
                for(int j = index; j < numberOfPages; j++) {
                        if(pageRequest[j] == frames[i]) {
                                if(j > farthest) {
                                        farthest = j;
                                        res = i;
                                }
                                break;
                        }
                }

                // replace frame not used in future
                if(res == -1)
                        return i;

        }

        return res;
}

/*****************************************************************************
* @brief               Simulates optimal replacement algorithm
* @author              Andrew Voss
* @date                11 Nov 21
* @lastUpdated         11 Nov 21
* @return              int (0 if page was found, 1 if page was not found and had to be replace a page)
* @arg                         pageRequest[] - pages that are being requested
*                              numberOfPages - number of pages
*                              freq[] - frequency of each page
*                              frames[] - frame buffer
*                              frameSize - number of element in current frame buffer
*                              index - index for the page request
*                              frameBufferSize - size of the frame buffer
* @note                None
*****************************************************************************/
int optimalAlgothrim(int pageRequest[], int numberOfPages, int freq[], int frames[], int frameSize, int index, int *frameBufferSize){
        int replace = -1;
        bool pageFound = false;

        // Searches buffer for page
        for (int k = 0; k < frameSize; k++) {
                if (frames[k] == pageRequest[index]) {
                        pageFound = true;
                        break;
                }
        }


        freq[pageRequest[index]] -= 1;

        if (!pageFound) {
                bool pageReplaced = false;

                if(*frameBufferSize < frameSize) {
                        frames[*frameBufferSize] = pageRequest[index];
                        *frameBufferSize += 1;
                } else {
                  replace = predict(pageRequest, numberOfPages, freq, frames, frameSize, index, frameBufferSize);
                  if(replace > -1)
                          frames[replace] = pageRequest[index];
                }
        }

        return !pageFound;
}

/*****************************************************************************
* @brief               Simulates clock replacement algorithm
* @author              Dylan Martie
* @date                5 Nov 21
* @lastUpdated         10 Nov 21
* @return              int (0 if page was found, 1 if page was not found and had to be replace a page)
* @arg                         pageRequest - page that is being requested
*                              frameBuffer[] - the predetermined sized array for holder stored frame values
*                              frameUseBits[] - the predetermined sized array for holding use bit value of each frame
*                              numFrames - number of frames
*                              framePointer - Pointer that keeps track of where we are in framebuffer
* @note                None
*****************************************************************************/
int clockAlgorithm(int pageRequest, int frameBuffer[], int frameUseBits[], int numFrames, int* framePointer) {

        bool pageFound = false;
        int numPageFaults = 0;
        int index = *framePointer;

        // Searches buffer for page
        for (int i = 0; i < numFrames; i++) {

                if (frameBuffer[i] == pageRequest) {
                        pageFound = true;
                        frameUseBits[i] = 1;
                        break;
                }
        }

        // If page not found, start replacement algorithm
        if (!pageFound) {
                numPageFaults += 1;
                bool pageReplaced = false;

                // Clock Algorithm
                // Finds first frame with use bits of 0, changing each frame passed form 1 to 0
                for (int j = 0; j < numFrames; j++) {

                        if (frameUseBits[index] == 0) {
                                frameBuffer[index] = pageRequest;
                                frameUseBits[index] = 1;
                                pageReplaced = true;
                                break;
                        }
                        else {
                                frameUseBits[index] = 0;
                        }
                        index = updatePointer(index, numFrames);

                }
                // If none found, starting point frame replaced
                if (!pageReplaced) {
                        frameBuffer[index] = pageRequest;
                        frameUseBits[index] = 1;
                        index = updatePointer(index, numFrames);
                }
        }
        *framePointer = index;

        return numPageFaults;
}

/*****************************************************************************
 * @brief			simulates LRU replacement algorithm
 * @author  		Meagan Olson
 * @date    		10 Nov 21
 * @lastUpdated 	11 Nov 21
 * @return  		int (0 if page was found, 1 if page was not found and a page had to be replaced)
 * @arg				page - page that is being requested
 *			    	frameSetSize - the maximum number of frames being used
 *		    		currentFrameSetSize - the current number of frames being used
 *			    	frameSet - the set of frames holding page numbers
 *			    	timeStamps - an array of times corresponding to the last time each page was recently used
 * @note    		None
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
			timeStamps[i] = now;
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
* @brief               prints contents of results array to a file
* @author              Joshua Molden
* @date                11 Nov 21
* @lastUpdated         11 Nov 21
* @return              void (prints to file)
* @arg                 results - array holding values to print to file
*						numOfRows - number of rows to print to file
*						fileName - the name of the file to create
* @note                Simulates FIFO replacement algorithm and prints results in ASCII table
*****************************************************************************/
void printResultsToFile(int results[][2], int numOfRows, char* fileName)
{
        FILE *file;
        file = fopen(fileName, "a");

        // create "numOfPagesInStreamInt" number of page numbers as ints between 0 and pagesInt
        for (int i = 0; i <= numOfRows; ++i) {
                fprintf(file, "%d,", results[i][0]);
                fprintf(file, "%d\n", results[i][1]);
        }

        // close file that was appended to
        fclose(file);
}

/*****************************************************************************
* @brief               reads values in from command line, makes random page stream for testing, creates
*                      data array based on inputed parameters
* @author              Joshua Molden
* @date                3 Nov 21
* @lastUpdated         4 Nov 21
* @return              int (0 if exited normally, non-zero if issues)
* @arg                 argc - number of command line arguments passed in, including name of program
*                      argv - the actual arguments
*                              argv[0] = name of program
*                              argv[1] = input file from which page stream should be read from. Need to make this file yet
*                              argv[2] = minimum number of frames to test replacement algorithm with (always 4 for this assignment)
*                              argv[3] = maximun number of frames to test replacement algorithm with (15, 30, 60 for this assignment)
*                              argv[4] = number of pages in process (15, 30, 60 for this assignment)
* @note                Simulates FIFO replacement algorithm and prints results in ASCII table
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
        int clockFaults[rows][2];
        int fifoFaults[rows][2];
        int optimalFaults[rows][2];
        int lruFaults[rows][2];

        // Read all page requests for Optimal Algorithm
        int pageRequests[1000];
        int buff[1];
        int freq[16];
        //memset(freq, 0, 1000*sizeof(int));
        FILE *file = fopen(inputFile, "r");
        for(int i = 0; i < numPagesPerProcessInt; i++) {
                fscanf(file, "%d", buff);
                pageRequests[i] = buff[0];
                freq[buff[0]] += 1;
        }
        fclose(file);

        // populate from numbers in arrays
        for (int i = minNumOfFramesInt; i <= maxNumOfFramesInt; ++i)
        {
                // initalize frame values, subtrack "minNumOfFramesInt" in
                // order to start putting values into array at index 0
                fifoFaults[i - minNumOfFramesInt][0] = i;
                clockFaults[i - minNumOfFramesInt][0] = i;
                optimalFaults[i - minNumOfFramesInt][0] = i;
                lruFaults[i - minNumOfFramesInt][0] = i;
                // initialize fault values to 0, same reason for subtracking "minNumOfFramesInt"
                // initialize to 0 because if you don't these cells don't start at 0 by default for some reason
                fifoFaults[i - minNumOfFramesInt][1] = 0;
                clockFaults[i - minNumOfFramesInt][1] = 0;
                optimalFaults[i - minNumOfFramesInt][1] = 0;
                lruFaults[i - minNumOfFramesInt][1] = 0;
        }

        for (int i = minNumOfFramesInt; i <= maxNumOfFramesInt; i++)
        {
                file = fopen(inputFile, "r");
                // holds number that is read from file

                // not end of file to start
                int endOfFile = 1;

                // for fifo algorithm
                int queue[i];
                int front = -1;
                int rear = -1;
                int currentSizeOfQueue = -1;

                // for clock algorithm
                int clockNumFrames = i;
                // Memset ensures all values initialized to -1
                int clockFrameBuffer[clockNumFrames];
                memset(clockFrameBuffer, -1, clockNumFrames*sizeof(int));
                int clockFrameUseBits[clockNumFrames];
                memset(clockFrameUseBits, -1, clockNumFrames*sizeof(int));

                // optimal algorithm
                int index = 0;
                int optimalFrameBuffer[i];
                int bufferSize = 0;

                int clockFramePointer = 0;

                // lru algorithm
                int lruFrameSet[i];
		time_t lruTimestamps[i];
		int lruCurrentFrameSetSize = 0;

                int fifoNumOfFaults = 0;
                int clockNumOfFaults = 0;
                int optimalNumOfFaults = 0;
                int lruNumOfFaults = 0;

                do
                {
                        // read int from line. fscanf retruns 0 if successfully read
                        int succRead = fscanf(file, "%d", buff);
                        fifoNumOfFaults += fifoAlgorithm(buff[0], i, &currentSizeOfQueue, &front, &rear, queue);
                        clockNumOfFaults += clockAlgorithm(buff[0], clockFrameBuffer, clockFrameUseBits, clockNumFrames, &clockFramePointer);
                        optimalNumOfFaults += optimalAlgothrim(pageRequests, numPagesPerProcessInt, freq, optimalFrameBuffer, i, index, &bufferSize);
			lruNumOfFaults += lruAlgorithm(buff[0], i, &lruCurrentFrameSetSize, lruFrameSet, lruTimestamps);
                        index++;
                }
                while (!feof(file));

                fifoFaults[i - 4][1] = fifoNumOfFaults;
                clockFaults[i - 4][1] = clockNumOfFaults;
                optimalFaults[i - 4][1] = optimalNumOfFaults;
                lruFaults[i - 4][1] = lruNumOfFaults;
                fclose(file);
        }

        /* print to file in order to make it easier to copy to excel spreadsheet

           char fifoOutput[50], clockOutput[50], optimalOutput[50], lruOutpur[50];
           strcat(fifoOutput, "fifoOutput");
           strcat(fifoOutput, maxNumOfFrames);
           strcat(fifoOutput, ".csv");

           strcat(clockOutput, "clockOutput");
           strcat(clockOutput, maxNumOfFrames);
           strcat(clockOutput, ".csv");

           strcat(optimalOutput, "optimalOutput");
           strcat(optimalOutput, maxNumOfFrames);
           strcat(optimalOutput, ".csv");

           strcat(lruOutput, "lruOutput");
           strcat(lruOutput, maxNumOfFrames);
           strcat(lruOutput, ".csv");

           printResultsToFile(optimalFaults, rows, optimalOutput);
           printResultsToFile(fifoFaults, rows, fifoOutput);
           printResultsToFile(clockFaults, rows, clockOutput);
           printResultsToFile(lruFaults, rows, lruOutput);
         */

        //printTable(optimalFaults, rows, "OPT");
        printTable(fifoFaults, rows, "FIFO");
        printTable(clockFaults, rows, "CLOCK");
        printTable(optimalFaults, rows, "OPTIMAL");
        printTable(lruFaults, rows, "LRU");

        return 0;
}
