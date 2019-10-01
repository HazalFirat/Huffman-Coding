#ifndef H_UnorderedLinkedList
#define H_UnorderedLinkedList

#include <bitset>
#include<string>
#include<fstream>
#include "linkedList.h"

using namespace std;

template <class Type>
struct HuffmanNode
{
	Type info;
	int freq;
	HuffmanNode *left, *right;
};

template <class Type>
class unorderedLinkedList : public linkedListType<Type>
{
public:
	bool search(const Type& searchItem) const;
	
	void insertFirst(const Type& newItem);
	
	void insertLast(const Type& newItem);
	
	void deleteNode(const Type& deleteItem);
	
	unorderedLinkedList<Type> readText();

	void convertToASCII();  //Function to convert info of the nodes to ASCII

	unorderedLinkedList<Type> freqList();  //Function to reduce list by finding frequencies

	HuffmanNode<Type>* buildTree();   //Function to build Huffman Tree

	void HuffmanCode(HuffmanNode<Type> *root, string code, Type c, int count);  //Function to generate Huffman code of desired nod to be found

	void convertToHuffman();  //Function to open file for list to be converted to Huffman codes
};



template <class Type>
bool unorderedLinkedList<Type>::search(const Type& searchItem) const
{
	nodeType<Type> *current; //pointer to traverse the list
	bool found = false;

	current = first; //set current to point to the first 
					 //node in the list

	while (current != NULL && !found)    //search the list
		if (current->info == searchItem) //searchItem is found
			found = true;
		else
			current = current->link; //make current point to
									 //the next node
	return found;
}


template <class Type>
void unorderedLinkedList<Type>::insertFirst(const Type& newItem)
{
	nodeType<Type> *newNode; //pointer to create the new node

	newNode = new nodeType<Type>; //create the new node

	newNode->info = newItem;    //store the new item in the node
	newNode->frequency = 1;                                              //item is stored for the first time
	newNode->link = first;      //insert newNode before first
	first = newNode;            //make first point to the
								//actual first node
	count++;                    //increment count

	if (last == NULL)   //if the list was empty, newNode is also 
						//the last node in the list
		last = newNode;
}


template <class Type>
void unorderedLinkedList<Type>::insertLast(const Type& newItem)
{
	nodeType<Type> *newNode; //pointer to create the new node

	newNode = new nodeType<Type>; //create the new node

	newNode->info = newItem;  //store the new item in the node
	newNode->frequency = 1;                                            //item is stored for the first time
	newNode->link = NULL;     //set the link field of newNode
							  //to NULL

	if (first == NULL)  //if the list is empty, newNode is 
						//both the first and last node
	{
		first = newNode;
		last = newNode;
		count++;        //increment count
	}
	else    //the list is not empty, insert newNode after last
	{
		last->link = newNode; //insert newNode after last
		last = newNode; //make last point to the actual 
						//last node in the list
		count++;        //increment count
	}
}


template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
	nodeType<Type> *current; //pointer to traverse the list
	nodeType<Type> *trailCurrent; //pointer just before current
	bool found;

	if (first == NULL)    //Case 1; the list is empty. 
		cout << "Cannot delete from an empty list."
		<< endl;
	else
	{
		if (first->info == deleteItem) //Case 2 
		{
			current = first;
			first = first->link;
			count--;
			if (first == NULL)    //the list has only one node
				last = NULL;
			delete current;
		}
		else //search the list for the node with the given info
		{
			found = false;
			trailCurrent = first;  //set trailCurrent to point
								   //to the first node
			current = first->link; //set current to point to 
								   //the second node

			while (current != NULL && !found)
			{
				if (current->info != deleteItem)
				{
					trailCurrent = current;
					current = current->link;
				}
				else
					found = true;
			}//end while

			if (found) //Case 3; if found, delete the node
			{
				trailCurrent->link = current->link;
				count--;

				if (last == current)   //node to be deleted 
									   //was the last node
					last = trailCurrent; //update the value 
										 //of last
				delete current;  //delete the node from the list
			}
			else
				cout << "The item to be deleted is not in "
				<< "the list." << endl;
		}//end else
	}//end else
}


template <class Type>
unorderedLinkedList<Type> unorderedLinkedList<Type>::readText()
{
	ifstream inFile;
	char fileName[20], character;
	initializeList();                            //list is initialized to default

	cout << "Enter input file name: ";
	cin >> fileName;                             //user is asked for file name to be read
	cout << endl;

	inFile.open(fileName);                       //open file

	if (!inFile)                                 //no file
	{
		cout << "Cannot open input file." << endl;
	}

	inFile >> noskipws;                         //doesn't skip spaces
	inFile >> character;                        //read character from file


	while (!inFile.eof())                       //until end of file
	{
		insertLast(character);                 //character read is put at the end of the list
		inFile >> character;                   //read character from file
	}

	inFile.close();                            //close file
	return *this;                              //list that is updated is returned
}


template <class Type>
void unorderedLinkedList<Type>::convertToASCII()
{
	int count = 0;                   //variable to store the number of iterations
	string binary = " ";
	if (first != NULL)              //list to be converted not empty
	{
		ofstream outputFile;    
		nodeType<Type> *current;   //pointer to traverse the list

		current = first;
		outputFile.open("ascii.txt");         //open new file to store ascii codes
		outputFile << "ascii.txt" << endl;
		while (current != NULL)
		{
			binary = bitset<8>(current->info).to_string();   //generate set with 8 bits to store current's info then convert to string
			outputFile << binary << " ";                     //write to file
			count++;                                         //for visual
			if (count % 11 == 0)                             
				outputFile << endl;                          
			current = current->link;                         //next node
		}
		outputFile.close();       //close file
	}
	else
		cout << "No characters to be converted!";           //empty list
}


template<class Type>
unorderedLinkedList<Type> unorderedLinkedList<Type>::freqList()
{

	nodeType<Type> *current, *traverseCurrent, *trailTraverse, *temp;
	unorderedLinkedList<Type> list(*this);

	current = list.first;

	traverseCurrent = current->link;              //pointer to be followed by current
	trailTraverse = current;                      //pointer to follow traverseCurrent

	while (current != NULL)                       //until current reaches the end of the list
	{
		while (traverseCurrent != NULL)           //until traverseCurrent reaches the end of the list
		{
			if (tolower(current->info) == tolower(traverseCurrent->info))        //check if node pointed by current and encountered node are the same characters
			{
				current->frequency += 1;                                         //increment the frequency of the character 
				temp = traverseCurrent;                                          //to not lose the node to be deleted
				traverseCurrent = traverseCurrent->link;                         //traverseCurrent proceeds to next node   
				trailTraverse->link = traverseCurrent;                           //link the node before the node to be deleted with the node after the node to be deleted
				delete temp;                                                     //delete the node pointed by temp
				list.count--;                                                    //decrement the count
			}
			else                                                                 //if node pointed by current and encountered node are NOT the same characters
			{
				traverseCurrent = traverseCurrent->link;                         //traverseCurrent proceeds to next node  
				trailTraverse = trailTraverse->link;                             //trailTraverse proceeds to next node  
			}

		}
		current = current->link;                                                 //current proceeds to next node
		if (current != NULL)                                                     //check if current is at the end of the list otherwise error when trying to reach current's link
		{
			traverseCurrent = current->link;                                     //traverseCurrent proceeds to next node after current
			trailTraverse = current;                                             //trailTraverse points to the same node as current 
		}
	}
	 
	return list;                                                                 //return list which contains characters and their frequencies
}


template <class Type>
HuffmanNode<Type>* unorderedLinkedList<Type>::buildTree()
{
	HuffmanNode<Type> *arr;                                   //array to store characters according to their frequencies
	nodeType<Type> *current, *temp=NULL;
	unorderedLinkedList<Type> tempList(*this);                //make a list copied from original which will be used to not change original list (frequencies will change)
	int maxFreq = 0;

	arr = new HuffmanNode<Type>[count];                       //allocate memory for array with same size as original list

	current = tempList.first;                                 //current points to the first element of copied list


	for (int i = 0; i < count; i++)                           //until all elements are put in array
	{
		while (current != NULL)                               //until current is at the end of the list
		{
			if (current->frequency > maxFreq && current->frequency > 0)       //check the node if it's frequency is bigger than 0(which are visited ones) and maximum frequency available 
			{
				maxFreq = current->frequency;                                 //update maximum frequency
				temp = current;                                               //to not lose the node with the current max frequency
				current = current->link;                                      //current proceeds to next node
			}
			else
				current = current->link;                                      //current proceeds to next node
		}
		arr[i].info = tolower(temp->info);                                    //info of the node with the current maximum frequency in the list is stored as lowercase
		arr[i].freq = temp->frequency;                                        //frequency of the node with the current maximum frequency in the list is stored in the array
		arr[i].left = NULL;                                                   //left pointer doesn't point to anything
		arr[i].right = NULL;                                                  //right pointer doesn't point to anything
		temp->frequency = 0;                                                  //visited node's frequency is set to 0 in order to be not visited again
		current = tempList.first;                                             //current points to the first node in the list
		maxFreq = 0;                                                          //reset max frequency
	}



	/*													BUILD  HUFFMAN  TREE                                               */



	int i = count - 1;                                                       //i will be the index of arr, it will start from the lowest frequency 

	HuffmanNode<Type> *top = NULL, *left = NULL, *right = NULL;              
	HuffmanNode<Type> *tempArr;                                              //tempArr will be used for shifting

	tempArr = new HuffmanNode<Type>[count];                                  //allocate memory for tempArray with same size as original arr

	int b = 0;                                                               
	while (b < count)                                                        //tempArr elements are copied from arr 
	{
		tempArr[b].freq = arr[b].freq;
		tempArr[b].info = arr[b].info;
		tempArr[b].right = arr[b].right;
		tempArr[b].left = arr[b].left;
		b++;
	}

	while (i != 0)                                                           //until the element with highest frequency
	{
		top = new HuffmanNode<Type>;                                         //parent node
		left = new HuffmanNode<Type>;                                        //left child
		right = new HuffmanNode<Type>;                                       //right child
		top->info = '$';                                                     //parent's info, not important
		top->freq = arr[i].freq + arr[i - 1].freq;                           //parent's frequency will be the sum of two lowest frequencies possible

		left->info = arr[i].info;                                            /*                      */
		left->freq = arr[i].freq;                                            /*    left and right    */
		left->left = arr[i].left;                                            /*   child properties   */
		left->right = arr[i].right;                                          /*     are assigned     */
		right->info = arr[i - 1].info;                                       /*  from array elements */
		right->freq = arr[i - 1].freq;                                       /*    with the lowest   */
		right->left = arr[i - 1].left;                                       /* frequencies possible */
		right->right = arr[i - 1].right;                                     /*                      */


		top->left = left;                                                    //parent's left child
		top->right = right;                                                  //parent's right child


		i--;                                                                 //decrease index i


		if (top->freq >= arr[i - 1].freq)                                    //check if parents frequency is bigger than or equal to element of arr which will be next to be put in the tree
		{
			for (int k = 0; k < i; k++)                                      //search arr to find the correct position to put parent
			{
				if (top->freq >= arr[k].freq)                                //when position found 
				{
					arr[k].freq = top->freq;                                 //put parent and its properties to the position found
					arr[k].info = top->info;
					arr[k].left = top->left;
					arr[k].right = top->right;
					
					while (k <= i)                                           //shift the elements of array after parent is positioned to the right by 1  
					{                                                        //till encountered the element which won't be used
						arr[k + 1].freq = tempArr[k].freq;
						arr[k + 1].info = tempArr[k].info;
						arr[k + 1].left = tempArr[k].left;
						arr[k + 1].right = tempArr[k].right;
						k++;
					}
					int c = 0;                                               //update tempArray which is used for comparison
					while (c < i)
					{
						tempArr[c].freq = arr[c].freq;
						tempArr[c].info = arr[c].info;
						tempArr[c].left = arr[c].left;
						tempArr[c].right = arr[c].right;
						c++;
					}
					break;
				}
			}
		}
		else if (i != 0)                                                    //if no bigger or equal frequency found parent will be the last element which will be considered
		{
			arr[i].info = top->info;
			arr[i].freq = top->freq;
			arr[i].left = top->left;
			arr[i].right = top->right;
		}

		/*                          Enable the following comment to see parents and their childs                       */
		/*cout << "Top Info:" << top->info << "  Top Freq:" << top->freq << endl;
		cout << "Left Child:" << top->left->info << "-" << top->left->freq << "  Right Child:" << top->right->info << "-" << top->right->freq << endl << endl;
		cout << endl;*/

	}
	
	return top;                                                            //return the root
}

template <class Type>
void unorderedLinkedList<Type>::HuffmanCode(HuffmanNode<Type> *root, string code, Type c, int count)
{
	if (root != NULL)                                                           //check if Huffman tree exist
	{
		if (root->left != NULL)                                                 //check if there is left child
			HuffmanCode(root->left, code + "0", c, count);                      //function calls itself to check the left child of node  
		if (root->right != NULL)                                                //check if there is right child
			HuffmanCode(root->right, code + "1", c, count);                     //function calls itself to check the left child of node
		if (root->left == NULL && root->right == NULL&&root->info == c)         //check if item that is searched for is found and leaf
		{
			ofstream outputFile;                                                
			outputFile.open("huffman.txt", fstream::app);                       //open existing file and append to its existing content
			outputFile << code << " ";                                          //write to file
			if (count % 14 == 0)                                                //for visual  
				outputFile << endl;
		}
	}
}


template<class Type>
void unorderedLinkedList<Type>::convertToHuffman()
{
	if (first != NULL)
	{
		int count = 1;                                                   //count to send HuffmanCode function for visual
		nodeType<Type> *current;                                         //node to traverse list
		current = first;                                                 //node points to the first element of list
		HuffmanNode<Type> *root = (*this).freqList().buildTree();        //root is generated from sending frequency list of the list to buildTree function
		ofstream outputFile;           
		outputFile.open("huffman.txt");                                  //open new file to store Huffman codes
		outputFile << "huffman.txt" << endl;
		string code = ""; 
		while (current != NULL)                                          //until current reaches the end of the list
		{
			HuffmanCode(root, code, tolower(current->info), count);	     //call HuffmanCode function to generate Huffman code for info of node pointed by current
			count++;                                                     //increment count for generated code
			current = current->link;                                     //current proceeds to next node
		}
		outputFile.close();                                              //close file
	}
	else                                                                 //list is empty
		cout << "No characters to be converted!";
}

#endif
