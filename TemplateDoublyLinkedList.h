#ifndef TEMPLATEDOUBLYLINKEDLIST_H
#define TEMPLATEDOUBLYLINKEDLIST_H

#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;
template<class T> class DoublyLinkedList;

// list node
template<typename T>
struct DListNode{
  T obj;
  DListNode<T> *prev, *next;
  DListNode(DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : prev(nullptr), next(nullptr) {}
  DListNode(T e, DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list
template<class T>
class DoublyLinkedList{
private:
  DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(0), trailer(0) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList<T>(const DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList<T>(); // destructor
  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  DListNode<T> *getLast() { return trailer.prev; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void insertAfter(DListNode<T> &p, T newobj);  //Took out const
  void insertBefore(DListNode<T> &p, T newobj); //Took out const
  void removeAfter(DListNode<T> &p); //Took out const
  void removeBefore(DListNode<T> &p); //Took out const
  void remove(DListNode<T>* p);       //Self-made remove that allows pointers.
};

// copy constructor
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll){
	DListNode<T>* curr = dll.getFirst();        //Pointer to keep track of the currently viewed node
        header.next = &trailer;                     //Assigns header pointer.
	trailer.prev = &header;                     //Assigns trailer pointer.
	while(curr != dll.getAfterLast()){                        //While the list is within scope
		insertLast(curr->obj);                  //Insert the currently viewed object into the new list
		curr = curr->next;                      //Assign the pointer to the next object in the list
	}                                           //All items should be copied here.
	return;                                     //Work's done!
}

// assignment operator
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll){
	DListNode<T>* curr = this->getFirst();        //Pointer to keep track of currently viewed node
	while(!this->isEmpty()){
		this->removeFirst();
	}
	curr = dll.getFirst();
	while(curr != dll.getAfterLast()){
		this->insertLast(curr->obj);
		curr = curr->next;
	}
	return *this;
}

// insert the new object as the first one
template <class T>
void DoublyLinkedList<T>::insertFirst(T newobj){ 
    DListNode<T>* temp = new DListNode<T>(newobj);//New temportary DListNode
    temp->prev = &header;                       //Sets the new node's previous value
    temp->next = header.next;                   //Sets the new node's next value
    header.next = temp;                         //Sets the header's next value to the new node
    temp->next->prev = temp;                    //Accesses the intended next node after the new node, and assigns prev pointer.
    return;                                     //That's all four pointer assignments! Whew.
}

// insert the new object as the last one
template <class T>
void DoublyLinkedList<T>::insertLast(T newobj){
 	DListNode<T>* temp = new DListNode<T>(newobj);//New temporary DListNode
 	temp->prev = trailer.prev;                  //Sets the new node's previous value
 	temp->next = &trailer;                      //Sets the new node's next value
 	temp->prev->next = temp;                    //Sets the new node's intended previous node's next to new node.
 	trailer.prev = temp;                        //Sets the trailer's previous value to the temporary node.
 	return;                                     //Whew! Done again.
}

// remove the first object from the list
template <class T>
T DoublyLinkedList<T>::removeFirst(){ 
	//if(this->isEmpty()){ throw runtime_error("Cannot remove from an empty list.");}
	DListNode<T>* temp = header.next;           //Creates a pointer to the memory address of the first node
	T removed = temp->obj;                    //Left whitespace because I don't think this should be here.
	header.next = temp->next;                   //Sets the header's next value to the value after the pointer
	temp->next->prev = &header;                 //Sets the value after the pointer's previous value to the header
	delete temp;                                //At this point, temp is free floating memory, so we delete it.
	return removed;                             //All done, with memory cleaned up.
}

// remove the last object from the list
template <class T>
T DoublyLinkedList<T>::removeLast(){
	//if(this->isEmpty()){ throw runtime_error("Cannot remove from an empty list.");}
	DListNode<T>* temp = trailer.prev;          //Creates a pointer to the memory address of the last node
	T removed = temp->obj;                    //Left whitespace because I don't think this should be here.
	trailer.prev = temp->prev;                  //Sets the trailer's previous value to the value before the pointer
	temp->prev->next = &trailer;                //Sets the value before the pointer's next value to the trailer
	delete temp;                                //At this point, temp is free floating memory, so we delete it.
	return removed;                             //And again, all done. Good time.
}

// destructor
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList<T>(){
	DListNode<T>* left = header.next;               //Sets an initial pointer to the header node.
	DListNode<T>* rigt = header.next;               //Sets an iterative pointer to the next node thereafter.
	rigt = rigt->next;                          //Compiler was being fussy, had to do this.
	while(rigt != nullptr){                        //While the currently viewed node isn't a nullptr,
		delete left;                            //Delete the left operond, or lefternmost available value
		left = rigt;                            //Set the left value to the known next value
		rigt = left->next;                      //Set the right value to the known value next to left.
	}                                           //There you go! Zips right through the doubly linked list.
	return;	                                    //Returns home. One small step for compsci major, one giant step for 221
}

// return the first object
template <class T>
T DoublyLinkedList<T>::first() const{
	//if(this->isEmpty()){ throw runtime_error("Cannot see first from an empty list.");}
	return header.next->obj;                    //I'm guessing this is what it wants with an int return value.
}

// return the last object
template <class T>
T DoublyLinkedList<T>::last() const{
	//if(this->isEmpty()){ throw runtime_error("Cannot see last from an empty list.");}
	return trailer.prev->obj;                   //Again, I'm guessing this is what is wanted.
}

// insert the new object after the node p
template <class T>
void DoublyLinkedList<T>::insertAfter(DListNode<T> &p, T newobj){
    DListNode<T>* temp = new DListNode<T>(newobj);//Creates a temporary pointer with the new value
    temp->next = p.next;                        //Sets the new node's next value to p's next.
    temp->prev = &p;                            //Sets the new node's prev value to p
    temp->next->prev = temp;                    //Sets the intended next node after temp's prev to temp
	p.next = temp;                              //Sets p's next to temp
    return;                                     //All four pointers done!
}

// insert the new object before the node p
template <class T>
void DoublyLinkedList<T>::insertBefore(DListNode<T> &p, T newobj){
    DListNode<T>* temp = new DListNode<T>(newobj);//Creates a temporary pointer with the new value
    temp->next = &p;                            //Sets the new node's next value to p
    temp->prev = p.prev;                        //Sets the new node's prev value to p's prev
    temp->prev->next = temp;                    //Sets the intended previous node before temp's next to temp
    p.prev = temp;                              //Set p's prev to temp
    return;                                     //All four done again! Woohoo! And look at that comment symmetry
}

// remove the node after the node p
template <class T>
void DoublyLinkedList<T>::removeAfter(DListNode<T> &p){
    //if(p.next == &trailer){throw runtime_error("Cannot delete after the end node.");}
    DListNode<T>* temp = p.next->next;          //Creates a temporary pointer holding the intended next val after the deletion
    delete p.next;                              //Deletes the node to be deleted
    p.next = temp;                              //Sets p's next to the next value after the old node is deleted
    p.next->prev = &p;                          //Sets p's next's previous to p, completing the bidirectionality
    return;                                     //Work done, memory freed.
}

// remove the node before the node p
template <class T>
void DoublyLinkedList<T>::removeBefore(DListNode<T> &p){
	//if(p.prev == &header){throw runtime_error("Cannot delete before the beginning node.");}
	DListNode<T>* temp = p.prev->prev;          //Creates a temporary pointer holding the intended prev val after the deletion
	delete p.prev;                              //Deletes the node to be deleted
	p.prev = temp;                              //Sets p's prev to the previous value after the old node is deleted
	p.prev->next = &p;                          //Sets p's prev's next to p, completing the bidirectionality
	return;                                     //Work done, memory freed.
}

// return the list length
template <class T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll){
    if(dll.isEmpty()){return 0;}
    DListNode<T>* temp = dll.getFirst();        //Creates a temporary pointer to the DLL's first node
    int counter = -1;                            //Creates a counting variable to hold number of nodes
    while(temp != NULL){                        //While the list is still within scope
    	counter++;                              //Add one to the number of nodes seen
    	temp = temp->next;                      //Set the current node to the next node
	}                                           //All nodes will be counted
    return counter;                             //Return the number of nodes.
}

// output operator
template <class T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll){
  	DListNode<T>* temp = dll.getFirst();        //Creates a temporary pointer to the DLL's first node.
  	while(temp != dll.getAfterLast()){                        //While the list is still within scope
  		out << temp->obj << ", ";               //Output the currently viewed object, and courtesies
  		temp = temp->next;                      //View the next object
	}                                           //After this, all objects should be outputted.
	out << endl;                                //End the current line for courtesies 
	return out;                                 //Returns the ostream to its home. Goodbye!
}

// self-made remove to allow pointers
template <class T>
void DoublyLinkedList<T>::remove(DListNode<T>* p){
	DListNode<T>* temp = p;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	cout << "Deleting: " << temp->obj << endl;
	delete temp;
	return;
}
#endif
