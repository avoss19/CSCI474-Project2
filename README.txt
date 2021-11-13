Compile instructions:
In order to compile the file, run:

		gcc project2WithAllAlgorithms.c

Run instructions:
After compilation, you can run the compile program with the command:

		./a.out inputFile.txt 4 15 15

The parameters to this command represent:
	./a.out		- the compiled project name
	inputFile.txt	- the text file that is delineated by new line characters
	4		- the minimum number of frames allocated
	15		- the maximum number of frames allocated
	15		- the number of pages in the simulated process

***************************** NOTE ***********************************
We ran into a weird bug where when you run the project2WithAllAlgorithms.c
file, the first entry on 3 of our tables are incorrect. Along with this the last
entry on the 3rd table is incorrect.  We were unable to figure out why this is
occuring. We are all very confused about why it is happening. We had originally
coded our algorithms in separate files, and when you run them independently, they
work just fine.
