#include <stack>
#include <queue>
#include <algorithm>
#include "HCTree.hpp"

/**
 * Destructor for HCTree
 */
HCTree::~HCTree()
{

	return;
 for(unsigned int i = 0; i < leaves.size(); i++)
 {
	 HCNode *t, *k;
	 if (leaves[i] != nullptr)
	 {
		 t = leaves[i];
		 while (t->p != nullptr)
		 {
			 k = t->p;
			 delete t;
			 t = k;
		 }
		 delete t;


	 }
 }


}


/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs)
{
    // TODO (checkpoint)
	std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;
	HCNode *p;
	for (unsigned int i  = 0; i < freqs.size(); i++)
	{

		if (freqs[i] != 0)
		{
			if (i < 128)
			{
			char c = char(i);
			p = new HCNode(freqs[i],c);
			leaves[i] = p;
			pq.push(p);
			}
			else
			{
				unsigned char d = i;
				p = new HCNode(freqs[i],d);
				leaves[i] = p;
				pq.push(p);
			}
		}
	}

	HCNode *a, *b;
	HCNode *top;
	while (pq.size() > 1)
	{
		a = pq.top();
		pq.pop();
		b = pq.top();
		pq.pop();
		top = new HCNode(a->count + b->count, 0);
		top->c0 = a;
		top->c1 = b;
		a->p = top;
		b->p = top;
		pq.push(top);
	}
	root = pq.top();
	//printTree();
}


/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const
{
    // TODO (checkpoint)
	int x = symbol;
	HCNode *n =leaves[x];
	if (n == nullptr)
		return;
	string s = "";

	while (n->p != nullptr)
	{
		if (n->p->c0 == n)
			s = "0" + s;
		else
			s = "1" + s;
		n = n->p;
	}
	cout << s;
	//cout << "encoding " << symbol << ": " << s << endl;
	out << s;

}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the istream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(istream& in) const
{
	// TODO (checkpoint)c
	char c;
	HCNode *temp = root;
	if (root->c0 == nullptr && root->c1 == nullptr)
		exit(0);
	while (!in.eof())
	{
	   in >> c;
	   if (c == '0')
		   temp = temp->c0;
	   else
		   temp = temp->c1;

	   if (temp->symbol != 0)
		   break;
   }
   return temp->symbol;

}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
    // TODO (final)
	int x = symbol;
	HCNode *n =leaves[x];
	if (n == nullptr)
		return;
	string s = "";

	//hello
	while (n->p != nullptr)
	{
		if (n->p->c0 == n)
		{
			s = "0" + s;
			//out.writeBit(0);
		}
		else
		{
			s = "1" + s;
			//out.writeBit(1);
		}
		n = n->p;
	}
	//cout << s;
	for (int i = 0; i < s.size(); i++)
	{
		if (s.at(i) == '0')
			out.writeBit(0);
		else
			out.writeBit(1);
	}
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(BitInputStream& in) const
{
	// TODO (checkpoint)c
		char c;
		HCNode *temp = root;
		if (root->c0 == nullptr && root->c1 == nullptr)
			exit(0);
		while (true)
		{
		   bool c = in.readBit();
		   if (c == false)
		   {
			  // cout << 0;
			   temp = temp->c0;
		   }
		   else
		   {
			 //  cout << 1;
			   temp = temp->c1;
		   }
		   if (temp->symbol != 0)
			   break;
	   }
	//   cout << temp->symbol ;
	   return temp->symbol;
    //return 0;  // TODO (final)
}

/**
 * Print the contents of a tree
 */
void HCTree::printTree() const {
    cout << "=== PRINT TREE BEGIN ===" << endl;
    printTreeHelper(root);
    cout << "=== PRINT TREE END =====" << endl;
}

/**
 * Recursive helper function for printTree
 */
void HCTree::printTreeHelper(HCNode * node, string indent) const {
    if (node == nullptr) {
        cout << indent << "nullptr" << endl;
        return;
    }

    cout << indent << *node << endl;
    if (node->c0 != nullptr || node->c1 != nullptr) {
        printTreeHelper(node->c0, indent + "  ");
        printTreeHelper(node->c1, indent + "  ");
    }
}
