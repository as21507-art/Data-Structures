//============================================================================
// Name         : Polynomial Calculator 
// Author       : Aashish Shrestha
// Date Created : June 2, 2026
// Date Modified: June 5, 2026
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
        Node(int coef = 0, int expo = 0) : coef(coef), expo(expo), next(nullptr) {};
		
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
    
    void removeZero());
		
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
LinkedList::LinkedList(): head(NULL) {}

// isEmpty Method: Checks if the linked list is empty by testing if head pointer points to null
// Input: Void
// Output: True if the list is empty, otherwise False
bool LinkedList::isEmpty(){
    return head == NULL;
}

// removeZero method: Removes all the nodes having coefficent zero
void LinkedList::removeZero(){
    
    // Declaring node pointers to traverse the list
    Node* v = head;
    Node* u = NULL;
    
    // f
}

// insert Method: Creates a new node adds it to the existing linked list in current order
// Input: Coefficent and Exponent of the new term of the polynomial
// Return: Void
void LinkedList::insert(int coef, int expo){
    
    // Checking if the list is empty, then insertion is simple
    if (isEmpty()){
        
        // Creating a new node dynamically using a pointer
        Node* v = new Node(coef, expo);
        
        // Updating the pointers to add the new node in the list
        head = v;
        v->next = NULL;
        
        // Exiting the function after the node has been added
        return;
    }
    
    // If it is not empty, use pointer to traverse the list and find correct insertion point
    // Declaring the traversing pointer
    Node* temp = head;
    
    // Since a node does not store information about its previous node, we need a second pointer to actually insert the list
    Node* prevTemp = NULL;
    
    // Traversing the list until the end (i.e. the null pointer)
    while (temp != NULL){
        
        // If the exponent is already present then it only adds the value of the exponent without using any nodes
        if (temp->expo == expo){
            temp->coef += coef;
            
            // Exit the function after the term has been updated to the polynomial, no insertion required
            return;
        }
        
        // Inserting the node before the first exponent that is smaller than the new exponent
        if (temp->expo < expo){
            // Insertion point has been found
            break;
        }
        
        // Moving to the next node
        prevTemp = temp;
        temp = temp->next;
    }
    // If the loop exits without break then value is added at the end of the list, the following code still handles this case
    
    // Creating a new node dynamically using a pointer
    Node* v = new Node;
    
    // Adding the coefficent and exponent values to the node
    v->coef = coef;
    v->expo = expo;
    
    // If prev was NULL, then the node is added to the begining of the list
    if (prevTemp == NULL){
        v->next = head;
        head = v;
    }
    
    // Otherwise, updating the node pointers to insert the node in its correct position
    else{
        v->next = temp;
        prevTemp->next = v;
    }
    
    // Exiting the function after the value has been inserted
    return;
}

// print Method: Displays the polynomial in a specific format
// Input: ostream& os
// Ouput: returns void (but displays the polynomial in its appropriate format
void LinkedList::print(ostream &os) const{
    // Using the string stream
    stringstream ss;
    
    // Zero Polynomial: Stores true if the polynomial is just zero polynomial
    bool noTerms = true;
    
    // Declaring a pointer to traverse through the list
    Node* current = head;
    
    // Traversing the list and formatting the terms of the polynomial
    while (current != NULL){
        
        // If the coefficent is 0, it is skipped
        if (current->coef == 0) {
            current = current->next;
            continue;
        }
        
        // If there is a single non-zero term then it is no longer a zero polynomial
        if (noTerms){
            noTerms = false;
        }
        
        // If there were existing terms then that requires separation by ' '
        else{
            ss << ' ';
        }
        
        // If the coefficent is neagtive then it needs to add minus symbol
        if (current->coef < 0){
            ss<<"-";
            
            // Add the rest of the terms in proper formatting, coefficent is multiplied by minus to prevent double negatives
            ss << -current->coef << 'x' << '^' << current->expo;
        }
        
        // If the coefficent is positive then it needs to add the plus symbol
        else {
            ss<<"+";
            
            // Add the rest of the terms in proper formatting
            ss << current->coef << 'x' << '^' << current->expo;
        }
        
        // Traversing to the next node
        current = current->next;
    }
    
    // Zero Polynomial shows a literal '0'
    if (noTerms){
        ss << 0;
    }
    
    // Seding the string stream to the os
    os << ss.str();
}

// removeAll method: Deletes all the nodes of the linked list with only head pointing to NULL remaining
// Input: void
// Output: void
void LinkedList::removeAll(){
    
    // Creating a temporary pointer to store deleted nodes
    Node* temp;
    
    while (!isEmpty()){
        
        // Stroring the first node in temp for deletion
        temp = head;
        
        // Unlinking the first node from the linked list
        head = temp-> next;
        
        // Releasing the memory
        delete temp;
    }
}

// Destructor Method: Deletes everything about the linked list including all nodes and head pointer and releases the memory
LinkedList::~LinkedList(){
    
    // Removes all the ndoes from the list until head is NULL
    removeAll();
    
}


// input Method: Prompts the user to enter two polynomial expressions
// Input: void
// Output: void
void PolyCalculator::input(){
    
    // Declaring variable to store the input polynomials
    string pol;
    
    // Clearing the linked list before storing
    list1.removeAll();
    list2.removeAll();
    
    while(true){
        // Prompting the user to enter the first polynomial expression and storing it in pol
        cout << "Enter first Polynomial expression: ";
        
        // Processes the entire line including the spaces
        getline(cin, pol);
        
        // Parsing the string to check validity of polynomial
        if (parse(pol, list1)) break;
        
        // If invalid, the prompt the user to enter a valid expression
        else cout<<"Invalid expression"<<endl;
    }
    
    while(true){
        // Prompting the user to enter the second polynomial expression and storing it in pol
        cout << "Enter second Polynomial expression: ";
        
        // Processes the entire line including the spaces
        getline(cin, pol);
        
        // Parsing the string to check validity of polynomial
        if (parse(pol, list2)) break;
        
        // If invalid, the prompt the user to enter a valid expression
        else cout << "Invalid expression" << endl;
    }
    
}


// parse Method: Takes a polynomial expression and converts it into a linked list if the expression is valid
// Input: A string representing a polynomial
// Output: True if the expression was valid and it is stored in the linked list, False if the expression was invalid
bool PolyCalculator::parse(string str, LinkedList& list){
    
    // Creating a string strem
    stringstream ss(str);
    
    // Declaring the components of a single term in the polynomial
    int coef;
    char variable;
    char power;
    int expo;
    
    // A flag to ensure that the list has at least one valid term
    bool zero_terms = true;
    
    // Iterating through the string to extract terms
    while (ss >> coef >> variable >> power >> expo){
        
        zero_terms = false;
        
        // Checking validity of the extracted term & inserting it to the list
        if (variable == 'x' && power == '^'){
            list.insert(coef, expo);
        }
        
        // If not valid then do not add anything to the list and return false
        else{
            list.removeAll();
            return false;
        }
    }
    
    // If the loop ends because of incorrect formatting and has not reach the end then it is invalid
    if (!ss.eof() || zero_terms){
        list.removeAll();
        return false;
    }
    
    return true;
}


// display Method: Displays the polynomials represented by list1 and list2 in the following format
// Exp1: +4x^3 + 2x^2 + 8x^0 <list1>
// Exp2: +5x^2 + 1x^0 <list2>
void PolyCalculator::display(std::ostream &os){
    
    // Printing expression 1 using the print method for linked lists that builds polynomial from the contents of its nodes
    os << "Exp1: ";
    list1.print(os);
    os << endl;
    
    // Printing expression 2
    os <<"Exp2: ";
    list2.print(os);
    os << endl;
    
}

// add Method: Adds the two polynomials stored in list1 and list2 and stores the result in list 3
// Input: void
// Output: void
void PolyCalculator::add(){
    
    // Clears list3 to ensure there is no existing data interfering
    list3.removeAll();
    
    // Declaring a pointer to traverse the lists
    Node* current = list1.head;
    
    // Traversing list 1 and copying and inserting its nodes to list3
    while (current != NULL){
        list3.insert(current->coef, current->expo);
        current = current->next;
    }
    
    // Traversing list 2 and inserting its nodes to list3 (because insert automatically adds if they have same x^n term!)
    current = list2.head;
    
    while (current != NULL){
        list3.insert(current->coef, current->expo);
        current = current->next;
    }
    
    // Displaying the result
    cout << "Exp1 + Exp2 = ";
    list3.print(cout);
    cout << endl;
}


// sub Method: Subtracts polynomial stored in list2 from list1 and stores the result in list3
// Input: void
// Output: void
void PolyCalculator::sub(){
    
    // Clears list3 to ensure there is no existing data interfering
    list3.removeAll();
    
    // Declaring a pointer to traverse the lists
    Node* current = list1.head;
    
    // Traversing list 1 and copying and inserting its nodes to list3
    while (current != NULL){
        list3.insert(current->coef, current->expo);
        current = current->next;
    }
    
    // Traversing list 2 and inserting its nodes to list3 (because insert automatically adds if they have same x^n term!)
    current = list2.head;
    
    while (current != NULL){
        // Subtracting list2 is same as adding the polynomial after multiplying it with -1
        list3.insert(-current->coef, current->expo);
        current = current->next;
    }
    
    // Displaying the result
    cout << "Exp1 - Exp2 = ";
    list3.print(cout);
    cout << endl;
}


// mul Method: Multiplies the polynomial represented by list1 and list2, then stores the result in list3
// Input: void
// Output: void
void PolyCalculator::mul(){
    
    // Clears list3 to ensure there is no existing data interfering
    list3.removeAll();
    
    // Declaring a pointer to traverse the first list
    Node* curr_first = list1.head;
    Node* curr_second = list2.head;
    
    // If either of them are empty (equivalent to 0), then the result is 0 (list3 empty is already 0)
    if (curr_first != NULL && curr_second != NULL){
        
        while (curr_first != NULL){
            
            // Multiplying each term of list1 with all the terms in list2
            while (curr_second != NULL){
                // Multiplication is product of coefficent and sum of exponents
                list3.insert(curr_first->coef * curr_second->coef, curr_first->expo + curr_second->expo);
                
                curr_second = curr_second->next;
            }
            
            // Traversing first list and starting the second list from the start
            curr_first = curr_first->next;
            curr_second = list2.head;
        }
    }
    
    // Displaying the results
    cout << "Exp1 * Exp2 = ";
    list3.print(cout);
    cout << endl;
}


// evaluate Method: Takes an expression ID and an integer value and evaluates the polynomial
// Input: ExpID (either 1 for first polynomial or 2 for second polynomial), x (the value for which polynomial is evaluated)
// Output: void
void PolyCalculator::evaluate(int ExprID, int x){
    
    // Variable that stores the evaluated value
    int eval_value = 0;
    
    // Selecting the list based on ExprID
    if (ExprID == 1){
        
        // Traversing the list to evaluate and add the value of x for each term
        Node* curr = list1.head;
        
        while (curr != NULL){
            // Typecasting result of pow from double to integer
            eval_value += curr->coef * static_cast<int>(pow(x, curr->expo));
            curr = curr->next;
        }
        
        // Displaying the result
        cout << "p(x) = ";
        list1.print(cout);
        cout << endl;
        cout << "p(" << x << ") = " << eval_value << endl;
        
        return;
    }
    
    if (ExprID == 2){
        
        // Traversing the list to evaluate and add the value of x for each term
        Node* curr = list2.head;
        
        while (curr != NULL){
            // Typecasting result of pow from double to integer
            eval_value += curr->coef * static_cast<int>(pow(x, curr->expo));
            curr = curr->next;
        }

        // Displaying the result
        cout << "p(x) = ";
        list2.print(cout);
        cout << endl;
        cout << "p(" << x << ") = " << eval_value << endl;
        
        return;
    }
    
    cout << "Invalid Expression ID";
}


// getDegree method: returns the highest coefficent of the polynomial
// Input: ExprID (either 1 for first polynomial or 2 for the second polynomial
// Ouput: returns an integer that is the degree of the polynomail
int PolyCalculator::getDegree(int exprID){
    
    // Since the lists are arranged in descending order of the exponent, the exponent of the first node of the list is the degree
    
    if (exprID == 1){
        
        // Checking the empty case
        if (list1.isEmpty()){
            return 0;
        }
        
        // Otherwise, returning the exponent of the first node
        return list1.head->expo;
    }
    
    if (exprID == 2){
        
        // Checking the empty case
        if (list2.isEmpty()){
            return 0;
        }
        
        // Otherwise, returning the exponent of the first node
        return list2.head->expo;
    }
    
    throw runtime_error("Invalid Expression ID");
}


// read Method: Reads polynomial expressions from a file and stores them into list1 and list2
// Input: FileName where the expressions are stored
// Output: Void
void PolyCalculator::read(string filename){
    
    // Clearing the list
    list1.removeAll();
    list2.removeAll();
    
    // Loading the file
    ifstream polyFile(filename);
    
    if (!polyFile.is_open()){
        throw runtime_error("File not found.");
    }
    
    // A variable to read the lines of the files
    string line;
    
    // Reading and parsing the first line to add it to list1
    getline(polyFile, line);
    if (!parse(line, list1)) {
        throw runtime_error("File contains invalid polynomial formats");
    }
    
    // Reading and parsing the first line to add it to list2
    getline(polyFile, line);
    if (!parse(line, list2)) {
        throw runtime_error("File contains invalid polynomial formats");
    }
    
    // Closing the file
    polyFile.close();
    
    // Displaying the expressions
    display();
}


