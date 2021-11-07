


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*****************************************************************************
 * @brief                       prints out spacers between rows
 * @author              Joshua Molden
 * @date                3 Nov 21
 * @lastUpdated         4 Nov 21
 * @return              void (prints to command line)
 * @arg                         columnWidth - the width of both columns
 * @note                This method doesn't allow for different width of columns.
 *                                      If this is desired, this method will have to be changed.
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
 * @brief                       prints out spacers without plus signs in the middle of columns
 * @author              Joshua Molden
 * @date                3 Nov 21
 * @lastUpdated         4 Nov 21
 * @return              void (prints to command line)
 * @arg                         totalWidth - total width of the table.
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
 * @brief                       prints out the data portion of the table
 * @author              Joshua Molden
 * @date                3 Nov 21
 * @lastUpdated         4 Nov 21
 * @return              void (prints to command line)
 * @arg                         data - 2 dimensional array holding data
 *                                      columnWidth - the width of both columns. Doesn't allow for different size columns.
 *                                                                If desired, changes will need to be made.
 *                                      numOfRows - how many rows the table needs to be
 *                                      totalWidth - total width of the table
 * @note                This method only allows for tables with two columns, and doesn't take into account if
 *                                      numbers are larger than the column headers. If this is desired, changes will need to be made.
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
 * @brief                       prints ascii table with a header, 2 coulmns with fixed sizes
 * @author              Joshua Molden
 * @date                3 Nov 21
 * @lastUpdated         4 Nov 21
 * @return              void (prints to command line)
 * @arg                         data - 2 dimensional array holding data
 *                                      numOfRows - number of rows for the data portion of the table
 * @note                This ascii table will only print correctly if the size of the columns are the same. If
 *                                      it is desired to be more "flexible," changes will need to be made.
 *****************************************************************************/
void printTable(int data[][2], int numOfRows)
{
        // array for header of table. Can replace algorithm name (i.e "FIFO") and it will center itself
        char* tableHeader[2] = {"Replacement Algorithm", "Clock"};

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
        printf("\n\n");

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
 * @brief                       Updates circular frame buffer to next position
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
        if ((pointer + 1) >= frameSize){
                pointer = 0;
        }
        else {
                pointer += 1;
        }
        return pointer;
}

/*****************************************************************************
 * @brief                       Performs Clock replacement Algorithm with associated page request stream
 * @author              Dylan Martie
 * @date                5 Nov 21
 * @lastUpdated         6 Nov 21
 * @return              void (prints to command line)
 * @arg                 argv - the actual agruments
                                                argv[1] = input file containting page requests
                                                argv[2] = minimum number of frames
                                                argv[3] = maximum number of frames
                                                argv[4] = number of pages (15, 30, 60)
 * @note                Calculates # of page faults for each frame amount for Clock Algorithm
 *****************************************************************************/
int main(int argc, char** argv) {

        // Read inputs from command line as strings
        char* inputFile = argv[1];

        char* minFramesStr = argv[2];

        char* maxFramesStr = argv[3];

        char* pages = argv[4];

        // Convert from string to number
        int minFrames = atoi(minFramesStr);
        int maxFrames = atoi(maxFramesStr);
        int pagesNum = atoi(pages);

        // ASCII Table
        int rows = maxFrames - minFrames;
        int totalFaults[rows][2];
        int counter = 0;


        for (int i = minFrames; i <= maxFrames; i++) {

                int numFrames = i;

                // Memset ensures all values initialized to -1
                int frameBuffer[numFrames];
                memset(frameBuffer, -1, numFrames*sizeof(int));
                int frameUseBits[numFrames];
                memset(frameUseBits, -1, numFrames*sizeof(int));

                int framePointer = 0;
                int numPageFaults = 0;

                FILE *file = fopen(inputFile, "r");
                for (int j = 0; j < 1000; j++) {

                        int buff[1];
                        bool pageFound = false;
                        fscanf(file, "%d", buff);
                        int pageRequest = buff[0];

                        // Searches buffer for page
                        for (int k = 0; k < numFrames; k++) {

                                if (frameBuffer[k] == pageRequest){
                                        pageFound = true;
                                        frameUseBits[k] = 1;
                                        break;
                                }
                        }
                        // If page not found, start replacement algorithm
                        if (!pageFound) {
                                numPageFaults += 1;
                                bool pageReplaced = false;

                                // Clock Algorithm
                                // Finds first frame with use bits of 0, changing each frame passed from 1 to 0
                                for (int m = 0; m < numFrames; m++) {

                                        if (frameUseBits[framePointer] == 0){
                                                frameBuffer[framePointer] = pageRequest;
                                                frameUseBits[framePointer] = 1;
                                                pageReplaced = true;
                                                break;
                                        }
                                        else {
                                                frameUseBits[framePointer] = 0;
                                        }
                                        framePointer = updatePointer(framePointer, numFrames);

                                }
                                // If none found, starting point frame replaced
                                if (!pageReplaced) {
                                        frameBuffer[framePointer] = pageRequest;
                                        frameUseBits[framePointer] = 1;
                                        framePointer = updatePointer(framePointer, numFrames);
                                }
                        }

                }

                fclose(file);
                //printf("Number of Frames: %d\n", numFrames);
                //printf("Number of Page Faults: %d\n", numPageFaults);

                totalFaults[counter][0] = numFrames;
                totalFaults[counter][1] = numPageFaults;
                counter++;


        }
        printTable(totalFaults, rows);

}


