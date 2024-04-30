#include "BitOutputStream.hpp"

// TODO (final)
BitOutputStream::BitOutputStream(ostream & o) : out(o) {
	buff = 0;
	nbits = 0;
	size = 0;
	c = 0;
}

void BitOutputStream::writeBit(bool bit)
{
    // TODO (final)
	buff = buff | (bit << nbits);
	nbits++;
	size++;
//
	//cout << "nbits: " << nbits;
	if (nbits == 8)
		flush();

//	buff = buff | (bit << nbits);
//	//cout << buff << endl;
//	nbits++;
//	size++;
//	cout << size << endl;

}

void BitOutputStream::flush()
{
    // TODO (final)
	//cout << buff << " ";
	c++;
	//cout << "true";
//	for(int i = 0; i < 8; i ++)
//	{
//		bool d = (buff >> i) & 1;
//		cout << d;
//		out << d;
//	}
	out << buff;
	nbits = 0;
	char clear = 0;
	buff = buff & clear;

}
