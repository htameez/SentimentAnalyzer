#ifndef TWEET_H
#define TWEET_H

#include <iostream>
#include <vector>
#include "DSString.h"

class Tweet {
    public:
        Tweet(char* c) : content(c) {}
        std::vector<DSString> tokenizer(bool);

    private:
        DSString content;
};

#endif