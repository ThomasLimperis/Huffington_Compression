#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string.h>
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void compressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
//    cerr << "TODO: compress '" << infile << "' -> '"
//        << outfile << "' here (ASCII)" << endl;
	vector<int> freqs(256, 0);
	ostringstream oss;
	ifstream file, file2;
	ofstream out;
	file.open(infile);
	string line;
	int x;
	int symbol = 0;
	bool symb = true;
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file,line);
			unsigned char* d = (unsigned char*)line.c_str();

			for (unsigned int i =0; i < line.size(); i++)
			{
				int x = d[i];
				freqs[x]++;
			}
			freqs[10]++; //change?
		}
	}
	else
	{
		cout << "Error";
		return;
	}

	out.open(outfile);
	for (unsigned int i = 0; i < freqs.size(); i++)
	{
		out << freqs[i] << endl;
	}

	for (int i = 0; i < freqs.size(); i++)
	{
		if (freqs[i] > 0 && i !=10)
			symbol++;
	}
	if (symbol == 1) //No need to compress
	{
		return;
	}

	HCTree tree;
	tree.build(freqs);
	file2.open(infile);
	while (!file2.eof())
	{
		getline(file2,line);
		for (unsigned int i = 0; i < line.size(); i++)
		{
			int x = line.at(i);
			tree.encode(x,oss);
		}
		if (!file2.eof())
			tree.encode(10,oss);
	}
	string str = oss.str(); //what does this do
	out << str;

}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * Uses bitwise I/O.
 */
void compressBitwise(const string & infile, const string & outfile)
{
    // TODO (final)
//    cerr << "TODO: compress '" << infile << "' -> '"
//        << outfile << "' here (bitwise)" << endl;

	vector<int> freqs(256, 0);
		ostringstream oss;
		ifstream file, file2;
		ofstream out;
		file.open(infile);
		string line;
		int x;
		int symbol = 0;
		bool symb = true;
		//hello
		int size = 0;
		if (file.is_open())
		{
			while (!file.eof())
			{
				getline(file,line);
				unsigned char* d = (unsigned char*)line.c_str();

				for (unsigned int i =0; i < line.size(); i++)
				{
					int x = d[i];
					freqs[x]++;
					size +=1;
				}
				freqs[10]++; //change?
			}
		}
		else
		{
			cout << "Error";
			return;
		}
		out.open(outfile);
		BitOutputStream outB = BitOutputStream(out);

		for (unsigned int i = 0; i < freqs.size(); i++)
		{
			out << freqs[i] << endl;
		}

		for (int i = 0; i < freqs.size(); i++)
		{
			if (freqs[i] > 0 && i !=10)
				symbol++;
		}
		if (symbol == 1) //No need to compress
		{
			return;
		}
		HCTree tree;
		tree.build(freqs);
		file2.open(infile);

		while (!file2.eof())
		{
			getline(file2,line);
			unsigned char* d = (unsigned char*)line.c_str();
			for (unsigned int i = 0; i < line.size(); i++)
			{
				int x = d[i];
				tree.encode(x,outB);
			}
			if (!file2.eof())
				tree.encode(10,outB);
		}
		//cout << endl << "the size is: " << size;
		outB.size = size;
		//int m = size % 8 ;
		//cout << endl << m << endl;
		while (outB.nbits != 0)
		{
			//cout << "true";
			outB.writeBit(0);
		}
		//string str = oss.str();
		//out << str;

		//cout << endl << outB.c;


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
        compressBitwise(infile, outfile);
    } else {
        compressAscii(infile, outfile);
    }

    return 0;
}
