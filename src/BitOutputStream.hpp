#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitOutputStream {
private:
    ostream & out;
    unsigned char buff;
   // int nbits = 8;

//

public:
    BitOutputStream(ostream & o);
    void writeBit(bool bit);
    void flush();
    int size = 0;
    int nbits = 8;
    int c = 0;
};

#endif // BITOUTPUTSTREAM_HPP
