#include "BitInputStream.hpp"

// TODO (final)
BitInputStream::BitInputStream(istream & i) : in(i) {
	nbits = 0;
	size = 0;
	eof = false;
	in >> buff;

}

bool BitInputStream::readBit()
{

	if (nbits == 8)
	{
		in >> buff;
		//cout << buff << endl;
		nbits = 0;

	}

	if (size == buff)
	{
		eof = true;
		return false;
	}


	bool d = (buff >> nbits++) & 1;
	//cout << d;

	return d;


    return false;  // TODO (final)
}
