Compile instructions:
In order to compile the files, run:

		gcc fileName.c

As of now, each algorithm is implimented in a separate file. In order to test
each algorithm, compile each .c file separatly and then run it with the same
input file that holds the simulated page address stream.

Run instructions:
After compilation, you can run the compile program with the command:

		./a.out inputFile.txt 4 15 15

The parameters to this command represent:
	./a.out		- the compiled project name
	inputFilte.txt	- the text file that is delineated by new line characters
	4		- the minimun number of frames allocated
	15		- the maximun number of frames allocated
	15		- the number of pages in the simulated process
