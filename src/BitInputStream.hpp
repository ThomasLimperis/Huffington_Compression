#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
    istream & in;

    //mew
    unsigned char buff = 0;
   // int nbits = 8;
public:
    bool eof = false;
    int size = 0;
    int max = 0;
    int nbits = 0;
    int c = 0;
    string s ="";
    int j = 0;



public:
    BitInputStream(istream & i);
    bool readBit();
};

#endif // BITINPUTSTREAM_HPP
