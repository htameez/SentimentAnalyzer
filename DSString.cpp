#include "DSString.h"
#include <cstring>

/* 
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project. 
 *
 * Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions 
 * from <string.h> or <cstring> other than for conversion from a c-string.
 */  

/**
     * Make sure you implement the rule-of-three and use proper memory management.
     * To help you get started, you can implement the following:
     **/

    DSString::DSString() { //default constructor
        len = 0;
        data = new char[1];
        data[len] = '\0';
    }

    DSString::DSString(const char* c) { // constructor that converts a cstring
        len = strlen(c);
        data = new char[len+1];
        for(size_t i = 0; i < len; ++i) {
            data[i] = c[i];
        }
        data[len] = '\0';

    } 

    // Rule of three is needed if dynamic memory allocation is used

    DSString::DSString(const DSString &s) { // copy constructor
        data = new char[s.len+1];
        for(size_t i = 0; i < s.len; ++i) {
            data[i] = s.data[i];

            // *(data + i) 
            // data[i]
        }
        data[s.len] = '\0';
        len = s.len;
    }

    DSString::~DSString() { // destructor
        delete[] data;
    }                           

    DSString &DSString::operator=(const DSString &original) { // assignment operator
        if(this != &original) {
            delete[] data;
            len = original.len;
            data = new char[original.len+1];
            for(size_t i = 0; i < len; ++i) {
                data[i] = original.data[i];
            }
            data[len] = '\0';
        }
        return *this;
    }

    // you can also implement the move versions for the big 5 (C+11)

    size_t DSString::length() const {
        return this->len;
    } // returns the length of the string

    char &DSString::operator[](size_t i) {
        if(i >= 0 && i < this->len) {
            return data[i];
        }
    } // returns a reference to the character at the given index

    /**
     * Overloaded operator+ which appends the string in the argument to this string
     */
    DSString DSString::operator+(const DSString &rhs) {
        size_t newLength = this->len + rhs.len;
        char newCharArray[newLength + 1];


        for(size_t i = 0; i < this->len; ++i) {
            newCharArray[i] = this->data[i];
        }

        for(size_t i = this->len; i < newLength; ++i) {
            newCharArray[i] = rhs.data[i - this->len];
        }

        newCharArray[newLength] = '\0';

        return DSString(newCharArray);
    }

    /**
     * Standard relational operators to compare and order your strings.
     * Feel free to add additional.
     **/
    bool DSString::operator==(const DSString &rhs) const { //== operator
        bool isEqual = true;

        if(this->len != rhs.len) { //if lengths don't equal, set isEqual to false
            isEqual = false;
        }

        for(size_t i = 0; i < this->len; ++i) { 
            if(this->data[i] != rhs.data[i]) { //if the element at i in data for each DSString doesn't equal, set isEqual to false
                isEqual = false;
            }
        }

        return isEqual;
    }

    bool DSString::operator<(const DSString &rhs) const { //< operator

        if(this->len < rhs.len) { //if this length is less than the other length, loop through this and compare the elements at i
            for(size_t i = 0; i < this->len; ++i) {
                if(this->data[i] < rhs.data[i]) { //
                    return true;
                }
                if(this->data[i] > rhs.data[i]) {
                    return false;
                }
            }
        } else { //else if the other length is less, loop through the other one and compare the elements at i
            for(size_t i = 0; i < rhs.len; ++i) { 
                if(this->data[i] < rhs.data[i]) {
                    return true;
                }
                if(this->data[i] > rhs.data[i]) {
                    return false;
                }
            }
        }
        
        if(this->len < rhs.len) { 
            return true;
        } else {
            return false;
        }
    }

    /**
     * The substring method returns a new string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
    DSString DSString::substring(size_t start, size_t numChars) const {
        char substring[numChars+1];

        if(start + numChars > this->len) {
            std::cerr << "ERROR: Substring entered is larger than DSString." << std::endl;
        }

        for(size_t i = 0; i < numChars; ++i) {
            substring[i] = this->data[i + start];
        }

        substring[numChars] = '\0';

        return DSString(substring);
    }

    /**
     * @brief Returns a new string object with all characters in lowercase
     *
     * @return DSString
     */
    DSString DSString::toLower() const {
        char newString[this->len+1];

        for(size_t i = 0; i < this->len; ++i) {
            if(this->data[i] >= 'A' && this->data[i] <= 'Z') {
                newString[i] = this->data[i] + 32;
            }
        }

        newString[this->len] = '\0';

        return DSString(newString);
    } // look at the ASCII table for this!

    /**
     * the c_str function returns a pointer a null-terminated c-string holding the
     * contents of this object. Since data already has a `\0`
     * at the end of the string in DSString so you can just return a pointer to data.
     **/
    char *DSString::c_str() const {
        return data;
    }

    // a conversion to std::string would also be nice: string string() const;
    std::string DSString::string() const {
        std::string s = std::string(data);
        return s;
    } // constructor that converts a cstring
    // you can also provide  DSString(const string &); for std::string

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument. Remember:
     * This operator needs to be implemented outside of the class as
     * a friend because it operates on the stream and not the DSString object.
     **/
    std::ostream &operator<<(std::ostream &os, const DSString &string) {
        return os << string.data;
    }

    // You are free to add more functionality to the class.  For example,
    // you may want to add a find(...) function that will search for a
    // substring within a string or a function that breaks a string into words.
    // You will need a split or tokenize function.
