# Assignment 0
Download the attached zip file A1.zip. It contains C++ code. This code reads a list of data items from a file, subdivide them into bins by value ranges. (Ranges are defined in a second file.) Finally, it sorts the data according to their bins.

You are to make this code faster. Sample data files are included. Other data files will be used for testing. Please note that you should not modify the file main.cpp. You should make sure to test performance on at least 4 cores. Up to 48 cores are available on HPC, where the testing will take place.

## Submission Instruction:
Submit a single zip file named [Your Entry Number].zip with all of the following:

1. Modified code (and Makefile) with improved efficiency.
1. Analysis of gprof, perf and valgrind reports of the original code.
1. Analysis of gprof, perf and valgrind reports of the modified code.
1. Document explaining what you learned from analysis 2, and how they led to the decisions to modify the code.

## Modifications Done (will be updated with code changes)
1. Changed the loop over `D` from a skip-by number of threads to a divide into consecutive ranges
1. Performed a similar modification for the loop over `R`, but indices divided such that there are roughly equal number of values to update for each thread
1. Implemented padding in the array to prevent false sharing
1. Removed alignment in `Counter` since it was in fact increasing cache misses (when being accessed in the first threading loop)
