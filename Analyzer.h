#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include "DSString.h"
#include "SentimentToken.h"

class Analyzer {
    private:
        std::map<DSString, int> tokenMap; // map from word to sentiment counter; using a map is faster than a vector bc it uses binary search, whereas vectors use linear search
        std::map<DSString,int> results;
        std::map<DSString,int> input;
        float accuracy;
        size_t correctlyClassified = 0;
        DSString id;
        std::map<DSString, int> incorrectGuesses;

    public:
        int readTrainingTweets(char*);
        int readTestTweets(char*);
        void analyzeTrain(std::vector<DSString>&, bool);
        int analyzeTest(std::vector<DSString>&);
        void train(char*);
        void test(char*, char*);
        void classify(char*, char*);
        void createOutputFile(std::map<DSString,int>, char*);
        void createClassificationsFile(char*);
        void convertToMap(char*);
        void calculateAccuracy(DSString);

};

#endif
