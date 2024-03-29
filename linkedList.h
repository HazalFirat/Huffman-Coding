#ifndef H_LinkedListType
#define H_LinkedListType
 
#include <iostream> 
#include <cassert>

using namespace std;



template <class Type>
struct nodeType
{
	Type info;
	int frequency;
	nodeType<Type> *link;
};

template <class Type>
class linkedListIterator
{
public:
   linkedListIterator();
     
   linkedListIterator(nodeType<Type> *ptr);
     
   Type operator*();
     
   linkedListIterator<Type> operator++();    
    
   bool operator==(const linkedListIterator<Type>& right) const; 
     
   bool operator!=(const linkedListIterator<Type>& right) const; 
     
private:
   nodeType<Type> *current; 
};

template <class Type>
linkedListIterator<Type>::linkedListIterator()
{
    current = NULL;
}

template <class Type>
linkedListIterator<Type>::
                  linkedListIterator(nodeType<Type> *ptr)
{
    current = ptr;
}

template <class Type>
Type linkedListIterator<Type>::operator*()
{
    return current->info;
}

template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++()   
{
    current = current->link;
    return *this;
}

template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type>& right) const
{
    return (current == right.current);
}

template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type>& right) const
{    
	return (current != right.current);
}


//*****************  class linkedListType   ****************

template <class Type>
class linkedListType
{
public:
    const linkedListType<Type>& operator=(const linkedListType<Type>&);  
  
    void initializeList(); 
      
    bool isEmptyList() const;
      
    void print() const;
      
    int length() const;
      
    void destroyList();
      
    Type front() const; 
      
    Type back() const; 
      
    virtual bool search(const Type& searchItem) const = 0;
     
    virtual void insertFirst(const Type& newItem) = 0;
      
    virtual void insertLast(const Type& newItem) = 0;
     
    virtual void deleteNode(const Type& deleteItem) = 0;
     
    linkedListIterator<Type> begin();

    linkedListIterator<Type> end();

    linkedListType(); 

    linkedListType(const linkedListType<Type>& otherList); 

    ~linkedListType();   
      

protected:
    int count;   
    nodeType<Type> *first; 
    nodeType<Type> *last; 

private: 
    void copyList(const linkedListType<Type>& otherList); 
      
};


template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
    return(first == NULL);
}

template <class Type>
linkedListType<Type>::linkedListType() //default constructor
{
    first = NULL;
    last = NULL;
    count = 0;
}

template <class Type>
void linkedListType<Type>::destroyList()
{
    nodeType<Type> *temp;   //pointer to deallocate the memory
                            //occupied by the node
    while (first != NULL)   //while there are nodes in the list
    {
        temp = first;        //set temp to the current node
        first = first->link; //advance first to the next node
        delete temp;   //deallocate the memory occupied by temp
    }
    last = NULL; //initialize last to NULL; first has already
                 //been set to NULL by the while loop
    count = 0;
}

template <class Type>
void linkedListType<Type>::initializeList()
{
	destroyList(); //if the list has any nodes, delete them
}

template <class Type>
void linkedListType<Type>::print() const
{
    nodeType<Type> *current; //pointer to traverse the list

    current = first;    //set current so that it points to 
                        //the first node
	
	
    while (current != NULL) //while more data to print
    {
		cout <<  current->info << "-" << current->frequency<<" ";
        current = current->link;
    }

}//end print

template <class Type>
int linkedListType<Type>::length() const
{
    return count;
}  //end length

template <class Type>
Type linkedListType<Type>::front() const
{   
    assert(first != NULL);

    return first->info; //return the info of the first node	
}//end front

template <class Type>
Type linkedListType<Type>::back() const
{   
    assert(last != NULL);

    return last->info; //return the info of the last node	
}//end back

template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin()
{
    linkedListIterator<Type> temp(first);

    return temp;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::end()
{
    linkedListIterator<Type> temp(NULL);

    return temp;
}

template <class Type>
void linkedListType<Type>::copyList(const linkedListType<Type>& otherList) 
{
    nodeType<Type> *newNode; //pointer to create a node
    nodeType<Type> *current; //pointer to traverse the list

    if (first != NULL) //if the list is nonempty, make it empty
       destroyList();

    if (otherList.first == NULL) //otherList is empty
    {
        first = NULL;
        last = NULL;
        count = 0;
    }
    else
    {
        current = otherList.first; //current points to the 
                                   //list to be copied
        count = otherList.count;

            //copy the first node
        first = new nodeType<Type>;  //create the node

        first->info = current->info; //copy the info
		first->frequency = current->frequency; //copy the frequency
        first->link = NULL;        //set the link field of 
                                   //the node to NULL
        last = first;              //make last point to the
                                   //first node
        current = current->link;     //make current point to
                                     //the next node

           //copy the remaining list
        while (current != NULL)
        {
            newNode = new nodeType<Type>;  //create a node
            newNode->info = current->info; //copy the info
			newNode->frequency = current->frequency; //copy the frequency
            newNode->link = NULL;       //set the link of 
                                        //newNode to NULL
            last->link = newNode;  //attach newNode after last
            last = newNode;        //make last point to
                                   //the actual last node
            current = current->link;   //make current point 
                                       //to the next node
        }//end while
    }//end else
}//end copyList

template <class Type>
linkedListType<Type>::~linkedListType() //destructor
{
   destroyList();
}//end destructor

template <class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type>& otherList)
{
   	first = NULL;
    copyList(otherList);
}//end copy constructor

        
template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=(const linkedListType<Type>& otherList)
{ 
    if (this != &otherList) //avoid self-copy
    {
        copyList(otherList);
    }//end else

     return *this; 
}

#endif
