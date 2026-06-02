/**
 * @file dlinkedlist.hpp
 * @author Khalid Mengal
 * @description Doubly LinkedList implementation in C++
 * @date 2023-03-22
 */

// Co-Author: Aashish Shrestha
// Date: 2026-06-02
// Description: The program contains various methods that is required in the implementation of doubly linked list. Namely, constructor, destructor, isEmpty, addFront, addBack, front, back, removeFront, removeBack, reverseList and isPalindrome

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Node {
private:
	/* Data element (type string in this case) */
	string elem;

	/* Pointer to the next node */
	Node* next;

	/* Pointer to the previous node */
	Node* prev;

	/* Declaring DLinkedList as a friend class */
	friend class DLinkedList;

public:
	/* Default constructor */
	Node() : next(NULL), prev(NULL) {}

	/* Constructor with element initialization */
	Node(string elem) : elem(elem), next(NULL), prev(NULL) {}

	/* Required for Autograder — Do not remove */
	friend void run_tests();
};

//==============================================================

class DLinkedList {
private:
	/* Pointer to the dummy head node */
	Node* head;

	/* Pointer to the dummy tail node */
	Node* tail;

public:
	/* Constructor to create dummy head and tail nodes */
	DLinkedList();

	/* Destructor to clean up all nodes */
	~DLinkedList();

	/* Returns true if the list is empty */
	bool isEmpty() const;

	/* Returns the front element; throws an exception if list is empty */
	const string& front() const;

	/* Returns the back element; throws an exception if list is empty */
	const string& back() const;

	/* Adds a new node to the front of the list (after head) */
	void addFront(const string& elem);

	/* Adds a new node to the back of the list (before tail) */
	void addBack(const string& elem);

	/* Removes the front node; throws an exception if list is empty */
	void removeFront();

	/* Removes the back node; throws an exception if list is empty */
	void removeBack();

	/* Reverses the list */
	void reverseList();

	/* Returns true if the list is a palindrome, false otherwise */
	bool isPalindrome() const;

	/* Displays all elements of the list */
	void display() const;

	/* Required for Autograder — Do not remove */
	friend void run_tests();
};

//============================================================

#ifdef _WIN32
void DLinkedList::display() const {
	Node* curr = head;
	while (curr != NULL) {
		cout << "+------";
		curr = curr->next;
	}
	cout << "+" << endl << "|";

	curr = head;
	while (curr != NULL) {
		if (curr == head)         cout << " Head |";
		else if (curr == tail)    cout << " Tail |";
		else                      cout << setw(5) << curr->elem << " |";
		curr = curr->next;
	}

	cout << endl;
	curr = head;
	while (curr != NULL) {
		cout << "+------";
		curr = curr->next;
	}
	cout << "+" << endl;
}
#else
void DLinkedList::display() const {
	Node* curr = head;
	while (curr != NULL) {
		cout << "╔══════╗    ";
		curr = curr->next;
	}
	cout << endl << "║";

	curr = head;
	while (curr != NULL) {
		if (curr == head)         cout << " Head ║<══>║";
		else if (curr == tail)    cout << " Tail ║";
		else                      cout << setw(6) << curr->elem << "║<══>║";
		curr = curr->next;
	}

	cout << endl;
	curr = head;
	while (curr != NULL) {
		cout << "╚══════╝    ";
		curr = curr->next;
	}
	cout << endl;
}
#endif
//startercode_ends
//===========================================================
//Constructor to create Sentinel (dummy) nodes
DLinkedList::DLinkedList ()
{
	// Creating dummy nodes for head and tail
    head = new Node;
    tail = new Node;
    
    // Head and Tail do not contain any data and just point to each other
    head->next = tail;
    tail->prev = head;
}
//============================================================
// Destructor to delete every node inclduing the sentinel nodes for head and tail
DLinkedList::~DLinkedList ()
{
	// Removing all the nodes until the list is empty
    while (!isEmpty()) removeFront();
    
    // When the list is empty, only head and tail remain
    delete head;
    delete tail;
}
//============================================================
// A function that return true if there are no nodes in the list other than head or tail
bool DLinkedList::isEmpty() const
{
    // If head points to tail then the list is empty
    return head->next == tail;
}
//============================================================
// A function that returns the contents of the first node of the list
const string& DLinkedList::front() const
{
    // Checking if the list is empty
    if (isEmpty()) throw runtime_error("List is empty");
    
    // If it is not empty, return the node next of head
    else return head->next->elem;
}
//============================================================
// A function that reutrns the contencts from the last node of the list
const string& DLinkedList::back() const
{
    //Checking if the list is empt
    if (isEmpty()) throw runtime_error("List is empty");
    
    // If it is not empty, return the node previous of the tail
    else return tail->prev->elem;
}
//============================================================
// A function that adds new node at the begining of the list
void DLinkedList::addFront(const string& elem)
{
    // Allocating Memory for new node
    Node* v = new Node;
    
    // Initializing the elem for the new node
    v->elem = elem;
    
    // New node's next pointer points to the first node
    v->next = head->next;
    
    // New node's previous pointer points to the head
    v->prev = head;
    
    // Updating the head's next pointer to point to v
    head->next = v;
    
    // Updating the original first node's previous pointer to point to v
    v->next->prev = v;
}
//============================================================
// A function that adds node at the end of the list
void DLinkedList::addBack(const string& elem)
{
	//Allocating the Memory space for new node
    Node* v = new Node;
    
    // Initializing the elem for the new node
    v->elem = elem;
    
    // New node's next pointer points to the tail
    v->next = tail;
    
    // New node's previous pointer points to the last node
    v->prev = tail->prev;
    
    // Updating the original last node's next pointer to point to v
    v->prev->next = v;
    
    // Updating the tail's previous pointer to point to v
    tail->prev = v;
}
//============================================================
// A function that removes the first node of the list
void DLinkedList::removeFront()
{
    // Checking if the list is empty
    if (isEmpty()) throw runtime_error("List is empty");
    
	// Storing the node to delete in a temporary variable
    Node* temp = head->next;
    
    // Changing the head's next pointer to point to the second node
    head->next = temp->next;
    
    // Changing the second node's previous pointer to point to head
    temp->next->prev = head;
    
    // Deleting the node after the pointers have been updated
    delete temp;
}
//============================================================
// A function that removes the last node of the list
void DLinkedList::removeBack()
{
    // Checking if the list is empty
    if (isEmpty()) throw runtime_error("List is empty");
    
	// Storing the node to delete in a temporary variable
    Node *temp = tail->prev;
    
    // Changing the tail's previous pointer to point to second last node
    tail->prev = temp->prev;
    
    // Changing the second last node's next pointer to point to tail
    temp->prev->next = tail;
    
    // Deleting the node after the pointers have been updated
    delete temp;
    
}
//============================================================
// A function that reverses the order of the list
void DLinkedList::reverseList()
{
    // Checking if the list is empty
    if (isEmpty()) throw runtime_error("List is empty");
    
    // Defining the pointer that traverses the list
    Node* v = head->next;
    
    // Declaring the temporary pointer for swapping
    Node* temp;
    
    // Using a loop to traverse through the list
    while (v != tail){
        // Swapping the next and previous pointers
        temp = v->next;
        v->next = v->prev;
        v->prev = temp;
        
        // Traversing to the next element (which was temp)
        v = temp;
    }
    
    // Storing the first node in temporary pointer
    temp = head->next;
    
    // Last node and head connected to each other
    tail->prev->prev = head;
    head->next = tail->prev;
    
    // Conneecting the first node and the tail
    tail->prev = temp;
    temp->next = tail;
}
//============================================================
bool DLinkedList::isPalindrome() const
{
    // Checking if the list is empty
    if (isEmpty()) throw runtime_error("List is empty");
    
    // Defining two pointers that traverse from the front and the back
    Node* fp = head->next;
    Node* bp = tail->prev;
    
    while (fp->elem == bp->elem){
        // Odd number of elements like 1-2-1 mean that at the middle, fp == bp
        // Even number of elements like 1-2-2-1 mean that at the middle, fp.next == bp
        if (fp == bp || fp->next == bp) return true;
        // Traversing the list (fp goes to next and bp goes to prev)
        fp = fp->next;
        bp = bp->prev;
    }
    
    // If the loop exits, it was not a palindrome
    return false;
}
