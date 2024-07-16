#include <iostream>
#include <math.h>
#include "Analyzer.h"
#include <chrono>

/*

Creates an instance of Analyzer, checks if the right amount of arguments are passed, and calls train() test() and classify(),
passing in appropriate command line argument. main takes in an int representing the number of arguments passed and a char pointer,
representing a char array of command line arguments, from index 0 to argc-1;

*/

int main(int argc, char **argv) // argv has all six files, argv[0] = "./sentiment"; argv[1] = "data/train_dataset_20k.csv", etc.
{
    Analyzer analyzer;

    if (argc == 1)
    {
        std::cout << "No extra command line argument passed other than program name.";
    }
    else
    {
        analyzer.train(argv[1]);
        analyzer.test(argv[2], argv[4]);
        analyzer.classify(argv[3], argv[5]);
    }

    return 0;
}