#include "Tweet.h"

std::vector<DSString> Tweet::tokenizer(bool isTraning)
{
    int commaCounter = isTraning ? 5 : 4;
    size_t i = 0;
    while (commaCounter > 0 && i < content.length())
    {
        if (content[i] == ',')
        {
            commaCounter--;
        }
        i++;
    }

    char temp[content.length() + 1];
    size_t j = 0;
    std::vector<DSString> answer;
    for (i; i < content.length(); ++i)
    {
        if (isalpha(content[i]))
        {
            temp[j] = content[i];
            j++;
        }
        else if (j > 0 && isspace(content[i]))
        {
            temp[j] = '\0';
            j = 0;
            answer.push_back(DSString(temp));
        }
    }
    if (j > 0) //if we reach the end of the for loop, and we've places something into temp array, then we add it to vector
    {
        temp[j] = '\0';
        answer.push_back(DSString(temp));
    }

    return answer;
}

// tokenizer function: convert tweet to lowercase then make a for loop which parses through each Tweet in vector.

// createSentimentTokens function: creates a sentiment token for each positive or negative word. stores each in a container, probably a 2D vector, where one line is of negative words and one line is of positive words. this is the dictionary. returns the dictionary vector to Analyzer
