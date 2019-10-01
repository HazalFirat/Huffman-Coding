#include<iostream>
#include <fstream>
#include "linkedList.h"
#include "unorderedLinkedList.h"
using namespace std;


int main()
{
	unorderedLinkedList<char> list, freqList;
	list.readText();
	//list.print();                                           //To see the text read from file 
	cout << endl << endl;
	list.convertToASCII();
	cout << "File with ASCII codes is created!" << endl;
	//freqList = list.freqList();                             //To see frequency list of characters
	//cout << "Frequencies of Characters:" << endl;
	//freqList.print();;                                      
	cout << endl << endl;
	list.convertToHuffman();
	cout << "File with Huffman codes is created!" << endl;
	return 0;
}

