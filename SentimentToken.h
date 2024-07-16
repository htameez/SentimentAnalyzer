#ifndef SENTIMENTTOKEN_H
#define SENTIMENTTOKEN_H

#include "SentimentToken.h"
#include "DSString.h"

class SentimentToken
{
public:
    DSString word;
    int positiveCounter;
    int negativeCounter;
};

#endif