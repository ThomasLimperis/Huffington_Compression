#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void uncompressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
//    cerr << "TODO: uncompress '" << infile << "' -> '"
//        << outfile << "' here (ASCII)" << endl;

	ifstream file;
	file.open(infile);
	string line;
	vector<int> freqs(256, 0);
	HCTree tree;
	int symbols = 0, symbol_p = 0;
	if (file.is_open())
	{
		int x, i = 0;
		while (!file.eof())
		{
			file >> x;
			freqs[i] = x;
			if (i != 10 && x > 0)
			{
				symbols++;
				symbol_p = i;
			}

			i++;
			if (i == 256)
				break;
		}

	}
	tree.build(freqs);
	file >> line;

	istringstream is(line);

	ofstream out;
	out.open(outfile);
	unsigned char d;
	if (symbols == 1)
	{
		for (int i =0; i < freqs[symbol_p];i++)
		{
			d = symbol_p;
			out << d;
		}
		return;
	}

	unsigned int x;
	char c;

	while (!is.eof())
	{
		x = tree.decode(is);
		if (x == 0)
		{
			cout << "true";
			break;
		}
		if (x < 128)
		{
			c = x;
			out << c;
		}
		else
		{
			d = x;
			out << d;
		}
	}
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * Uses bitwise I/O.
 */
void uncompressBitwise(const string & infile, const string & outfile) {
    // TODO (final)
//    cerr << "TODO: uncompress '" << infile << "' -> '"
//        << outfile << "' here (bitwise)" << endl;


	ifstream file;
	file.open(infile);
	string line;
	vector<int> freqs(256, 0);
	HCTree tree;
	int size = 0;
	int symbols = 0, symbol_p = 0;
	if (file.is_open())
	{
		int x, i = 0;
		while (!file.eof())
		{
			file >> x;
			freqs[i] = x;
			size +=x;
			if (i != 10 && x > 0)
			{
				symbols++;
				symbol_p = i;
			}

			i++;
			if (i == 256)
				break;
		}

	}
	tree.build(freqs);
	file >> line;

	istringstream is(line);

	ofstream out;
	out.open(outfile);
	BitInputStream inB = BitInputStream(is);

//	if (symbols == 1)
//	{
//		for (int i =0; i < freqs[symbol_p];i++)
//		{
//			d = symbol_p;
//			out << d;
//		}
//		return;
//	}

	//hello
	unsigned char d;
	int  x;
	char c;
	inB.size = 1;
	inB.max = size;
	//cout << inB.max << endl << endl;
	while (inB.size < inB.max)
	{
		x = tree.decode(inB);
//		if (x == 0)
//			break;
		if (x < 128)
		{
			c = x;
			out << c;
			inB.size++;
		}
		else
		{
			d = x;
			out << d;
			inB.size++;
		}
//		if (inB.size > inB.max)
//		{
//			cout << "trawdawdue";
//					break;
//		}
	}
	//cout << endl <<"size "<< inB.size << endl << inB.max;
}


int main(int argc, char ** argv) {
    string infile = "";
    string outfile = "";
    bool bitwise = false;
    for (int i = 1; i < argc; i++) {
        string currentArg = argv[i];
        if (currentArg == "-b") {
            bitwise = true;
        } else if (infile == "") {
            infile = currentArg;
        } else {
            outfile = currentArg;
        }
    }

    if (infile == "" || outfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        print_usage(argv);
        return 1;
    }

    if (bitwise) {
        uncompressBitwise(infile, outfile);
    } else {
        uncompressAscii(infile, outfile);
    }

    return 0;
}
