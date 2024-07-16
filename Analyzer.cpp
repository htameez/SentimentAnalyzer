#include "Analyzer.h"
#include "Tweet.h"

/*

train() takes in a command line argument, the training file name, and passes it to readTrainingTweets(), which reads in from
the input file, train_dataset_20k.csv, tokenizes the tweet in each line, and passes it to analyzeTrain(), which evaluates the
tweets based on the sentiment value.

*/

void Analyzer::train(char *trainingFile)
{
    readTrainingTweets(trainingFile); // reads in tweets from test file, tokenizes the tweets, and calls analyze to create token map
}

/*

test() takes in a 2 command line arguments, the test file and the results file, and passes them to readTestTweets and
createOutputFile. readTestTweets reads in the tweets from the test file, tokenizes them, calculates the sentiment value of the
tweets' words based on tokenMap, and inserts the sentiment value and id of each tweet into the results map. createOutputFile takes
the results and writes the results to resultsFile, or results.csv

*/

void Analyzer::test(char *testFile, char *resultsFile)
{
    readTestTweets(testFile);
    createOutputFile(results, resultsFile);
}

/*

classify() takes in two command line arguments, the input file and the classifications file. it passes these to convertToMap and
createClassificationsFile. convertToMap converts the input file values into to a map, with the id as the key and the assignment
sentiment value as the value. it then accesses each id and passes it to calculateAccuracy(), which calculates the accuracy of the
predictions/results and inserts incorrect guesses into a map of ids and sentiment values, which is later used to write to the
output file. createClassificationsFile writes this output file using accuracy and the map of incorrect guesses.

*/

void Analyzer::classify(char *inputFile, char *classificationsFile)
{
    convertToMap(inputFile);
    createClassificationsFile(classificationsFile);
}

// read in sentiment value and tweet from test file
int Analyzer::readTrainingTweets(char *trainingFile)
{
    FILE *stream;

    // set up the buffer
    char buffer[1000]; // maximum line length

    stream = fopen(trainingFile, "r");
    if (stream == NULL)
    {
        std::cerr << "Opening the file failed!" << std::endl;
        return (-1);
    }

    /* The C library function char *fgets(char *str, int n, FILE *stream)
     * reads a line from the specified stream and stores it into the string
     * pointed to by str. It stops when either (n-1) characters are read, the
     * newline character is read, or the end-of-file is reached, whichever
     * comes first. See https://en.cppreference.com/w/c/io/fgets
     */

    bool isFirstRow = true;

    while (fgets(buffer, sizeof(buffer), stream) != NULL)
    {
        if (isFirstRow)
        {
            isFirstRow = false;
            continue;
        }

        bool sentiment;

        if (buffer[0] == '0')
        {
            sentiment = false;
        }
        else
        {
            sentiment = true;
        }

        Tweet t(buffer);
        std::vector<DSString> tweetWords = t.tokenizer(true);

        this->analyzeTrain(tweetWords, sentiment);
    }

    fclose(stream);
    return (0);
}

void Analyzer::analyzeTrain(std::vector<DSString> &words, bool sentiment)
{
    // for loop which goes through each word
    // if new word
    // TokenMap[words[i]] = 0
    // if sentiment is true
    // TokenMap[word.at(i)]++
    // else if sentiment is false
    // TokenMap[word.at(i)]--

    for (size_t i = 0; i < words.size(); ++i)
    {
        if (tokenMap.find(words.at(i)) == tokenMap.end())
        {
            tokenMap.insert({words.at(i), (sentiment) ? 1 : -1});
        }
        else if (sentiment == true)
        {
            tokenMap[words.at(i)]++;
        }
        else if (sentiment == false)
        {
            tokenMap[words.at(i)]--;
        }
    }
}

int Analyzer::readTestTweets(char *testFile)
{
    FILE *stream;

    // set up the buffer
    char buffer[1000]; // maximum line length

    stream = fopen(testFile, "r");
    if (stream == NULL)
    {
        std::cerr << "Opening the file failed!" << std::endl;
        return (-1);
    }

    /* The C library function char *fgets(char *str, int n, FILE *stream)
     * reads a line from the specified stream and stores it into the string
     * pointed to by str. It stops when either (n-1) characters are read, the
     * newline character is read, or the end-of-file is reached, whichever
     * comes first. See https://en.cppreference.com/w/c/io/fgets
     */

    bool isFirstRow = true;

    while (fgets(buffer, sizeof(buffer), stream) != NULL)
    {
        if (isFirstRow)
        {
            isFirstRow = false;
            continue;
        }

        char id[11];

        for (int i = 0; i < 10; ++i)
        {
            id[i] = buffer[i];
        }
        id[10] = '\0';

        DSString ID(id);

        Tweet t(buffer);
        std::vector<DSString> tweetWords = t.tokenizer(false);

        int sentimentValue = this->analyzeTest(tweetWords);

        results.insert({ID, sentimentValue});
    }

    fclose(stream);
    return (0);
}

void Analyzer::createOutputFile(std::map<DSString, int> results, char *resultsFile)
{
    std::ofstream analyzer_results;
    analyzer_results.open(resultsFile);

    if (!analyzer_results)
    {
        std::cerr << "Opening the file failed!" << std::endl;
    }
    else
    {
        analyzer_results << "Sentiment,id" << std::endl;
        for (auto &result : results)
        {
            analyzer_results << result.second << "," << result.first << std::endl;
        }
    }
    analyzer_results.close();
}

int Analyzer::analyzeTest(std::vector<DSString> &words)
{
    // declare and initialize sum variable to 0
    int sum = 0;

    // loop through words, if the word at i equals a word in tokenMap, add the word's sentiment value to sum
    for (size_t i = 0; i < words.size(); ++i)
    {
        if (tokenMap.find(words.at(i)) != tokenMap.end())
        {
            sum += tokenMap[words.at(i)];
        }
    }

    if (sum > 0)
        return 4;
    else if (sum < 0 && sum > -140)
        return 4;
    else
        return 0;
}

void Analyzer::createClassificationsFile(char *classificationsFile)
{
    std::ofstream classifications;

    classifications.open(classificationsFile);

    if (!classifications)
    {
        std::cerr << "Opening the file failed!" << std::endl;
    }
    else
    {
        accuracy = correctlyClassified / 10000.0;
        classifications << std::fixed << std::setprecision(3) << accuracy << std::endl;
        for (auto &incorrectGuess : incorrectGuesses)
        {
            if (incorrectGuess.second == 0)
                classifications << "4, 0, " << incorrectGuess.first << std::endl;
            else
                classifications << "0, 4, " << incorrectGuess.first << std::endl;
        }
    }
    classifications.close();
}

void Analyzer::convertToMap(char *inputFile)
{
    FILE *stream;

    // set up the buffer
    char buffer[1000]; // maximum line length

    stream = fopen(inputFile, "r");
    if (stream == NULL)
    {
        std::cerr << "Opening the file failed!" << std::endl;
    }
    else
    {
        bool isFirstRow = true;

        while (fgets(buffer, sizeof(buffer), stream) != NULL)
        {
            if (isFirstRow)
            {
                isFirstRow = false;
                continue;
            }

            int sentimentVal = 0;
            if (buffer[0] == '0')
            {
                sentimentVal = 0;
            }
            else
            {
                sentimentVal = 4;
            }

            char id[11];

            for (int i = 2; i < 12; ++i)
            {
                id[i - 2] = buffer[i];
            }

            id[10] = '\0';

            DSString ID(id);

            input.insert({ID, sentimentVal});

            calculateAccuracy(ID);
        }

        fclose(stream);
    }
}

void Analyzer::calculateAccuracy(DSString key)
{
    if (input[key] == results[key])
        correctlyClassified++;
    else
    {
        incorrectGuesses.insert({key, results[key]});
    }
}
