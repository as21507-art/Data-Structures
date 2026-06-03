//============================================================================
// Name         : Polynomial Calculator 
// Author       : Aashish Shrestha
// Date Created : June 2, 2026
// Date Modified:
// Description  : Polynomial Calculator in C++ using Singly Linked-List
//============================================================================

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<sstream>

using namespace std;

class Node
{
	private:
		// coefficient of a term
		int coef; 
		
		// exponent of a term
		int expo; 
		
		// Link (pointer) to the next Node
		Node* next; 
		
	public:
		Node(int coef, int expo) : coef(coef), expo(expo), next(nullptr)
		{}
		
		friend class LinkedList;
		friend class PolyCalculator;
		
	public:
		/* Required for Auto-grader — Do not remove - Do not implement */
		friend void run_tests();
};
//=============================================================================
class LinkedList
{
	private:
		// pointer to the head of the Singly Linked list
		Node* head; 
		
	public:
		// empty list constructor
		LinkedList (); 
		
		// add a new Node (term) at the right place in the Linked List
		void insert(int coef,int expo); 
		
        
		void print(ostream& os=std::cout) const;
		
		// clean up (delete) all nodes
		void removeAll();	 
		
		// destructor to clean up all nodes
		~LinkedList ();
    
        /* Adding some helper functions */
        bool isEmpty();
		
	public:
		friend class PolyCalculator;
		
		/* Required for Autograder — Do not remove */
		friend void run_tests();
	};

//=======================================
class PolyCalculator
{
	private:
		LinkedList list1;
		LinkedList list2;
		LinkedList list3;
		
	public:
		// take input the values of polynomial expressions
		void input(); 
		
		// Parses a string and saves the terms to a linked list. 
		// Returns true if valid, false otherwise
		bool parse(std::string expr,LinkedList& list);	
		
		// display both polynomials (list1 and list2)
		void display(std::ostream &os=std::cout); 
		
		// Adds list1 and list2 and stores the result in list3
		void add();  
		
		// Subtract list2 from list1 and stores the result in list3
		void sub();  
		
		// Multiplies list1 and list2 and stores the result in list3
		void mul(); 
		
		// evalutes both polynomials for a given value of x
		void evaluate(int expID, int x); 
		
		// returns the degree of a polynomial
		int getDegree(int expID);	
		
		// read a file and load the data into the linked lists (list1 and list2)
		void read(std::string path); 
		
		// You can add more methods or helper functions if needed.
		
	public:
		/* Required for Autograder — Do not remove */
		friend void run_tests();
};
//======================================================
//Add your implementations below this line


// Constructor Method for LinkedList class
// Initializes an empty linked by setting the head pointer to null
LinkedList::LinkedList(): head(NULL);

// isEmpty Method: Checks if the linked list is empty by testing if head pointer points to null
// Input: Void
// Output: True if the list is empty, otherwise False
bool LinkedList::isEmpty(){
    return head == NULL;
}

// insert Method: Creates a new node adds it to the existing linked list in current order
// Input: Coefficent and Exponent of the new term of the polynomial
// Return: Void
void LinkedList::insert(int coef, int expo){
    
    // Checking if the list is empty, then insertion is simple
    if (isEmpty()){
        
        // Creating a new node dynamically using a pointer
        Node* v = new Node;
        
        // Adding the coefficent and exponent values to the node
        v->coef = coef;
        v->expo = expo;
        
        // Updating the pointers to add the new node in the list
        head->next = v;
        v->next = NULL;
        
        // Exiting the function after the node has been added
        return;
    }
    
    // If it is not empty, use pointer to traverse the list and find correct insertion point
    // Declaring the traversing pointer
    Node* temp = head->next;
    
    // Since a node does not store information about its previous node, we need a second pointer to actually insert the list
    Node* prevTemp = head;
    
    // Traversing the list until the end (i.e. the null pointer)
    while (temp != NULL){
        
        // If the exponent is already present then it only adds the value of the exponent without using any node
        if (temp.expo == expo){
            
            temp->coef += coef
            
            // Exit the function after the term has been updated to the polynomial, no insertion required
            return;
        }
        
        // Inserting the node before the first exponent that is smaller than the new exponent
        if (temp.expo < expo){
            // Insertion point has been found
            break;
        }
    }
    // If the loop exits without break then value is added at the end of the list, the following code still handles this case
    
    // Creating a new node dynamically using a pointer
    Node* v = new Node;
    
    // Adding the coefficent and exponent values to the node
    v->coef = coef;
    v->expo = expo;
    
    // Updating the pointers to insert the node in its correct position
    prevTemp->next = v;
    v-next> = temp;
    
    // Exiting the function after the value has been inserted
    return;
}

// print Method: Displays the polynomial in a specific format
// Input: ostream& os
// Ouput: returns void (but displays the polynomial in its appropriate format
void LinkedList::print(ostream &os) const{
    string pol;
    
    
}

// removeAll method: Deletes all the nodes of the linked list with only head pointing to NULL remaining
// Input: void
// Output: void
void removeAll(){
    
    // Creating a temporary pointer to store deleted nodes
    Node* temp;
    
    while (!isEmpty()){
        
        // Stroring the first node in temp for deletion
        temp = head->next;
        
        // Unlinking the first node from the linked list
        head->next = temp-> next;
        
        // Releasing the memory
        delete temp;
    }
}

// Destructor Method: Deletes everything about the linked list including all nodes and head pointer and releases the memory
LinkedList::~LinkedList(){
    
    // Removes all the ndoes from the list
    removeAll();
    
    // Removes the head pointer
    delete head;
}


// input Method: Prompts the user to enter two polynomial expressions
// Input: void
// Output: void
void PolyCalculator::input(){
    
    // Declaring variable to store the input polynomials
    string pol
    
    // Clearing the linked list before storing
    list1.removeAll()
    list2.removeAll()
    
    while(true){
        // Prompting the user to enter the first polynomial expression and storing it in pol
        cout<<"Enter first Polynomial expression: ";
        cin>>pol;
        
        // Parsing the string to check validity of polynomial
        if parse(pol, list1) break;
        
        // If invalid, the prompt the user to enter a valid expression
        else cout<<"Invalid expression"<<endl;
    }
    
    while(true){
        // Prompting the user to enter the second polynomial expression and storing it in pol
        cout<<"Enter second Polynomial expression: ";
        cin>>pol;
        
        // Parsing the string to check validity of polynomial
        if parse(pol, list2) break;
        
        // If invalid, the prompt the user to enter a valid expression
        else cout<<"Invalid expression"<<endl;
    }
    
}


// parse Method: Takes a polynomial expression and converts it into a linked list if the expression is valid
// Input: A string representing a polynomial
// Output: True if the expression was valid and it is stored in the linked list, False if the expression was invalid
