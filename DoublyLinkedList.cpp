#include "DoublyLinkedList.h"
#include <stdexcept>

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll){
	DListNode* curr = dll.getFirst();           //Pointer to keep track of the currently viewed node
        header.next = &trailer;                     //Assigns header pointer.
	trailer.prev = &header;                     //Assigns trailer pointer.
	while(curr != dll.getAfterLast()){                        //While the list is within scope
		insertLast(curr->obj);                  //Insert the currently viewed object into the new list
		curr = curr->next;                      //Assign the pointer to the next object in the list
	}                                           //All items should be copied here.
	return;                                     //Work's done!
}

// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll){
	DoublyLinkedList* tem= new DoublyLinkedList;//New temporary linked list
	DListNode* curr = this->getFirst();           //Pointer to keep track of currently viewed node
/*	while(curr != nullptr){                        //While the currently viewed node is not the last node in the list
		tem->insertLast(curr->obj);             //Insert the currently viewed node into the temporary list
		curr = curr->next;                      //Point the pointer to the next node in the linked list
	}                                           //Repeat until all nodes are copied into temp*/
	while(!this->isEmpty()){
		this->removeFirst();
	}
	curr = dll.getFirst();
	while(curr != dll.getAfterLast()){
		this->insertLast(curr->obj);
		curr = curr->next;
	}
	return *this;                                //Returns, all memory has been reassigned and freed.
}

// insert the new object as the first one
void DoublyLinkedList::insertFirst(int newobj){ 
    DListNode* temp = new DListNode(newobj);    //New temportary DListNode
    temp->prev = &header;                       //Sets the new node's previous value
    temp->next = header.next;                   //Sets the new node's next value
    header.next = temp;                         //Sets the header's next value to the new node
    temp->next->prev = temp;                    //Accesses the intended next node after the new node, and assigns prev pointer.
    return;                                     //That's all four pointer assignments! Whew.
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj){
 	DListNode* temp = new DListNode(newobj);    //New temporary DListNode
 	temp->prev = trailer.prev;                  //Sets the new node's previous value
 	temp->next = &trailer;                      //Sets the new node's next value
 	temp->prev->next = temp;                    //Sets the new node's intended previous node's next to new node.
 	trailer.prev = temp;                        //Sets the trailer's previous value to the temporary node.
 	return;                                     //Whew! Done again.
}

// remove the first object from the list
int DoublyLinkedList::removeFirst(){ 
	if(this->isEmpty()){ throw runtime_error("Cannot remove from an empty list.");}
	DListNode* temp = header.next;              //Creates a pointer to the memory address of the first node
	int removed = temp->obj;                    //Left whitespace because I don't think this should be here.
	header.next = temp->next;                   //Sets the header's next value to the value after the pointer
	temp->next->prev = &header;                 //Sets the value after the pointer's previous value to the header
	delete temp;                                //At this point, temp is free floating memory, so we delete it.
	return removed;                             //All done, with memory cleaned up.
}

// remove the last object from the list
int DoublyLinkedList::removeLast(){
	if(this->isEmpty()){ throw runtime_error("Cannot remove from an empty list.");}
	DListNode* temp = trailer.prev;             //Creates a pointer to the memory address of the last node
	
	int removed = temp->obj;                    //Left whitespace because I don't think this should be here.
	
	trailer.prev = temp->prev;                  //Sets the trailer's previous value to the value before the pointer
	temp->prev->next = &trailer;                //Sets the value before the pointer's next value to the trailer
	delete temp;                                //At this point, temp is free floating memory, so we delete it.
	return removed;                             //And again, all done. Good time.
}

// destructor
DoublyLinkedList::~DoublyLinkedList(){
	DListNode* left = header.next;                  //Sets an initial pointer to the header node.
	DListNode* rigt = header.next;                  //Sets an iterative pointer to the next node thereafter.
	rigt = rigt->next;                          //Compiler was being fussy, had to do this.
	while(rigt != nullptr){                        //While the currently viewed node isn't a nullptr,
		delete left;                            //Delete the left operond, or lefternmost available value
		left = rigt;                            //Set the left value to the known next value
		rigt = left->next;                      //Set the right value to the known value next to left.
	}                                           //There you go! Zips right through the doubly linked list.
	return;	                                    //Returns home. One small step for compsci major, one giant step for 221
}

// return the first object
int DoublyLinkedList::first() const{
	if(this->isEmpty()){ throw runtime_error("Cannot see first from an empty list.");}
	return header.next->obj;                    //I'm guessing this is what it wants with an int return value.
}

// return the last object
int DoublyLinkedList::last() const{
	if(this->isEmpty()){ throw runtime_error("Cannot see last from an empty list.");}
	return trailer.prev->obj;                   //Again, I'm guessing this is what is wanted.
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode &p, int newobj){
    DListNode* temp = new DListNode(newobj);    //Creates a temporary pointer with the new value
    cout << "Assigning pointers" << endl;
    temp->next = p.next;                        //Sets the new node's next value to p's next.
    temp->prev = &p;                            //Sets the new node's prev value to p
    cout << "Temp's pointers assigned" << endl;
    if(temp->next != nullptr){
        temp->next->prev = temp;                    //Sets the intended next node after temp's prev to temp
    }
    cout << "Happened after me" << endl;
	p.next = temp;                              //Sets p's next to temp
    cout << "Pointers to temp assigned" << endl;
    return;                                     //All four pointers done!

///////////////////I realize this may not be what is intended, but this is what I came up with, and it works if you flip the node to being a new one you wanna enter/////////////
/*   DListNode* curr = this->getFirst();
   while(curr != this->getAfterLast()){
	if(curr->obj == newobj){
		p.prev = curr;
		p.next = curr->next;
		curr->next = &p;
		p.next->prev = &p;
		return;
	}
	curr = curr->next;
   }
   cout << "Insertion failed, node to add after not found" << endl;
   return;*/
}

// insert the new object before the node p
void DoublyLinkedList::insertBefore(DListNode &p, int newobj){
    DListNode* temp = new DListNode(newobj);    //Creates a temporary pointer with the new value
    temp->next = &p;                            //Sets the new node's next value to p
    temp->prev = p.prev;                        //Sets the new node's prev value to p's prev
    temp->prev->next = temp;                    //Sets the intended previous node before temp's next to temp
    p.prev = temp;                              //Set p's prev to temp
    return;                                     //All four done again! Woohoo! And look at that comment symmetry
///////////////////I realize this may not be what is intended, but this is what I came up with, and it works if you flip the node to being a new one you wanna enter/////////////
 /*  DListNode* curr = this->getFirst();
   while(curr != this->getAfterLast()){
	if(curr->obj == newobj){
		p.prev = curr->prev;
		p.next = curr;
		curr->prev->next = &p;
		curr->prev = &p;
		return;
	}
	curr = curr->next;
   }
   cout << "Insertion failed, node to add after not found" << endl;
   return;*/
}

// remove the node after the node p
void DoublyLinkedList::removeAfter(DListNode &p){
    if(p.next == &trailer){throw runtime_error("Cannot delete after the end node.");}
    DListNode* temp = p.next->next;             //Creates a temporary pointer holding the intended next val after the deletion
    delete p.next;                              //Deletes the node to be deleted
    p.next = temp;                              //Sets p's next to the next value after the old node is deleted
    p.next->prev = &p;                          //Sets p's next's previous to p, completing the bidirectionality
    return;                                     //Work done, memory freed.
}

// remove the node before the node p
void DoublyLinkedList::removeBefore(DListNode &p){
	if(p.prev == &header){throw runtime_error("Cannot delete before the beginning node.");}
	DListNode* temp = p.prev->prev;             //Creates a temporary pointer holding the intended prev val after the deletion
	delete p.prev;                              //Deletes the node to be deleted
	p.prev = temp;                              //Sets p's prev to the previous value after the old node is deleted
	p.prev->next = &p;                          //Sets p's prev's next to p, completing the bidirectionality
	return;                                     //Work done, memory freed.
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll){
	if(dll.isEmpty()){return 0;}
	DListNode* temp = dll.getFirst();           //Creates a temporary pointer to the DLL's first node
    int counter = 0;                            //Creates a counting variable to hold number of nodes
    while(temp != dll.getAfterLast()){                        //While the list is still within scope
	cout << "Object being checked for length: " << temp << " with value: " << temp->obj << endl;
    	counter++;                              //Add one to the number of nodes seen
    	temp = temp->next;                      //Set the current node to the next node
	}                                           //All nodes will be counted
    return counter;                             //Return the number of nodes.
}

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll){
  	DListNode* temp = dll.getFirst();           //Creates a temporary pointer to the DLL's first node.
  	while(temp->obj != 0){                        //While the list is still within scope
  		out << temp->obj << ", ";               //Output the currently viewed object, and courtesies
  		temp = temp->next;                      //View the next object
	}                                           //After this, all objects should be outputted.
	out << endl;                                //End the current line for courtesies 
	return out;                                 //Returns the ostream to its home. Goodbye!
}
