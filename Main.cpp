#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;
int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DoublyLinkedList dll;
  cout << "list: " << dll << endl << endl;
  
  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertLast(i);
  }
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertFirst(i);
  }
  cout << "list: " << dll << endl << endl;
  cout << "Deleted DLL" << endl;
  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  DoublyLinkedList dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  DoublyLinkedList dll3;
  dll3=dll;
  cout << "list3: " << dll3 << endl << endl;
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeLast();
  }
  cout << "list: " << dll << endl << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeFirst();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;

  // more testing...
  // add tests for insertAfter, insertBefore
  cout << "Inserting 2048 after node 100" << endl;
  dll2.insertAfter(*dll2.getFirst(), 2048);
  cout << "Inserted." << endl;
  cout << "list: " << dll2 << endl;
  cout << "Inserting 1024 before node 100" << endl;
  dll2.insertBefore(*dll2.getLast(), 1024);
  cout << "list: " << dll2 << endl;
  // add tests for removeAfter, removeBefore
  cout << "Removing after the first" << endl;
  dll2.removeAfter(*dll2.getFirst());
  cout << "list: " << dll2 << endl;
  cout << "Removing before last" << endl;
  dll2.removeBefore(*dll2.getLast());
  cout << "list: " << dll2 << endl;
  // add tests for DoublyLinkedListLength
  cout << "The length of the list2 is: " << DoublyLinkedListLength(dll2) << endl; 
  
  return 0;
}
