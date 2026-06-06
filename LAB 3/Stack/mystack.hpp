/**
 * @fiile
 * @author Aashish Shrestha
 * @description: A program that implements stack for converting a string of mathematical expressions of single digit to postfix notation for simple evaluation algorithm
 * @date June 5, 2026
 */
#ifndef MY_STACK_H
#define MY_STACK_H
#include<iostream>
#include<string>
#include<exception>
#include<ctype.h>
#include<cmath>
//===========================================================================
//Helper function that checks if the parameter is an operator or not
bool isOperator(char ch)
{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
		return true;
	else
		return false;

}
//Helper method that converts operators into int so their precdence can be compared
int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/') return 2;
    if (ch=='^') return 3;
    return 0;
}
//Helper method that compares two operators and return true if first operator
//has greater or equal predence than the second operator
bool isgeq(char opA, char opB)
{
	return (convertOpToInt(opA)>=convertOpToInt(opB));
}
//===========================================================================
//Define the MyStack class and other required methods and functions below.

// Defining the exceptions

// StackFull Exception
// Usage: When the array is filled with max number of elements but a push method attempts to add more data to the stack
class StackFull : public std::exception {
    public:
        StackFull(const char* m = "Stack is Full");
        
        // Redefining what method
        virtual const char* what() const throw(){
            return message;
        }

    private:
        const char* message;
};

// Constructor method for StackFull
StackFull::StackFull(const char* m): message(m){}


// StackEmpty Exception
// Usage: When stack is empty and a pop method attempts to remove data from stack
class StackEmpty : public std::exception {
    public:
        StackEmpty(const char* m = "Stack is Empty");
        // Redefining what method
        virtual const char* what() const throw(){
            return message;
        }
    private:
        const char* message;
};

// Constructor method for StackEmpty
StackEmpty::StackEmpty(const char* m): message(m){}


// Defining the MyStack Class
template <typename T>
class MyStack {
    
    private:
        // A pointer that dynamically allocates memory
        T* array;
    
        // A variable that stores the next available space in the stack
        int top_ptr;
    
        // A constant that stores the max capacity of the stack
        int max;
    
    public:
        // Constructor Method
        MyStack(int n = 0);
    
        // Destructor Method
        ~MyStack();
    
        void push (T elem);
        void pop ();
        const T& top() const;
        int size();
        bool isEmpty();
};

// Constructor Method: Allocates a dynamic array of given size to be used as a stack (Default size of array is 0)
template <typename T>
MyStack<T>::MyStack(int n) : max(n), top_ptr (0){
    array = new T[n];
}

// Destructor Method: Deallocates the memory space for the array and deletes every attributes
template <typename T>
MyStack<T>::~MyStack(){
    delete [] array;
}

// push Method: Takes a data and attempts to add it to the stack
template <typename T>
void MyStack<T>::push(T elem){
    // Checking StackFull Case
    if (top_ptr >= max) throw StackFull();
    else{
        // Adding the data to the stack
        array[top_ptr] = elem;
        
        // Updating the top pointer
        top_ptr += 1;
    }
}

// pop Method: Removes the element at the top of the stack (only changes the pointer to disconnect it from stack)
template <typename T>
void MyStack<T>::pop(){
    // Checking StackEmpty Case
    if (top_ptr <= 0) throw StackEmpty();
    else{
        // Only changing the top pointer;
        top_ptr -= 1;
    }
}

// top Method: Can only view to contents at the top of the stack
template <typename T>
const T& MyStack<T>::top() const {
    // Checking the empty case
    if (top_ptr <= 0) throw StackEmpty();
    return array[top_ptr - 1];
}

// size Method: Returns the number of elements currently stored int the array which are the part of the stack
template <typename T>
int MyStack<T>::size(){
    return top_ptr;
}

// isEmpty() Method: Returns true if the stack is empty, false if otherwise
template <typename T>
bool MyStack<T>::isEmpty(){
    return top_ptr == 0;
}


// isBalanced Function: Checks if the paranthesis in the given mathematical expression is balanced (each opening bracket has corresponding closing bracket to the right of the expression, or not)
// Input: String representing a mathematical expression
// Output: True if the expression is balanced and false if it is not balanced
bool isBalanced(std::string expression){
    // Stack to store the paranthesis with capacity expression.size() because any string can have brackets at most equal to its whole length
    MyStack<char> para_stack(expression.size());
    
    try{
        // Traversing through the string
        for (int i = 0; i < expression.size(); i++){
            
                // Push if an opening bracket is found
                if (expression[i] == '(') para_stack.push('(');
                
                // Remove the most recent opening bracket if a closing bracket is found
                else if (expression[i] == ')') para_stack.pop();
                
                // Go to next char if the expression is not a paranthesis
                else continue;
        }
        
        // If stack is not empty then opening bracket does not have a closing bracket
        if (!para_stack.isEmpty()) return false;
        
        // Balanced iff stack is empty at the end of the expression
        else return true;
    }
    // If a closing bracket has no opening bracket and attempts to pop from the empty stack, it is not a balanced expression
    catch (StackEmpty &e){
        return false;
    }
}


// infix2postfix function: Takes an infix notation and implements stack to convert it into a postfix notation
// Input: string representing an expression in infix notation
// Ouput: string representing an expression in postfix notation
std::string infix2postfix(std::string infix){
    
    // Stack to perform the postfix algorithm
    MyStack<char> post_stack(infix.size());
    
    // String variable to store the postfix expression
    std::string postfix = "";
    
    // Traversing through the string
    for (int i = 0; i < infix.size(); i++){
        if (infix[i] == '('){
            post_stack.push('(');
        }
        else if (infix[i] == ')'){
            // Finding the corresponding opening bracket, appending the operators to postfix along the way
            while (true){
                
                // Insurance to avoid infinite loop
                if (post_stack.isEmpty()){
                    throw StackEmpty();
                }
                
                // Exit condition is finding a corresponding opening bracket
                if (post_stack.top() == '('){
                    post_stack.pop();
                    break;
                }
                
                // Adds all the operators between the paranthesis
                postfix += post_stack.top();
                post_stack.pop();
                
            }
        }
        
        // Checking the operator case
        else if (isOperator(infix[i])){
            
            // Adding operators of same or higher precedence or until "(" is found or it is empty
            while (!post_stack.isEmpty() && post_stack.top()!= '(' && isgeq(post_stack.top(), infix[i])){
                
                // Add operator to postfix
                postfix += post_stack.top();
                
                // Check the next operator (or paranthesis) of the stack
                post_stack.pop();
            }
            
            // Pushing the current operator to the stack
            post_stack.push(infix[i]);
        }
        
        // This is reached if the character was a operand and it is added to the postfix expression
        else {
            postfix += infix[i];
        }
    }
    
    // Adding the remaining operators to the postfix notation until the stack is empty
    while (!post_stack.isEmpty()){
        postfix += post_stack.top();
        post_stack.pop();
    }
    
    return postfix;
}


// operate funtion: Takes a char representing an operator and two numbers and applies the operation on the two input numbers
// Input: (char op, float left, float right) representing the operation :: left op right
// Output: The answer to the operation in float
float operate(char op, float left, float right){
    if (op=='+'){
        return left + right;
    }
    else if (op=='-'){
        return left - right;
    }
    else if (op=='*'){
        return left * right;
    }
    else if (op=='/'){
        return left / right;
    }
    else if (op=='^'){
        return std::pow(left, right);
    }
    else{
        throw std::runtime_error("Invalid math symbol");
    }
}



// evaluate function: Takes postfix expression and evaluates the value of the mathematical expression implementing a stack
// Input: String representing a postfix notation
// Output: An answer of type float to the given expression
float evaluate(std::string postfix){
    
    // A stack to evaluate the postfix notation
    MyStack<float> eval_stack(postfix.size());
    
    // Variables to store the popped contents of the stack during evaluation
    float right;
    float left;
    
    // Traversing through the postfix notation
    for (int i = 0; i < postfix.size(); i++){
        
        // Operator case
        if (isOperator(postfix[i])){
            
            // Popping two elements from the stack
            right = eval_stack.top();
            eval_stack.pop();
            
            left = eval_stack.top();
            eval_stack.pop();
        
            // Pushing the result of applying the operator in the stack
            eval_stack.push(operate(postfix[i], left, right));
        }
        
        // Operand case
        else{
            // Pushing the operand in the stack (converting ascii value to corresponding number using - '0')
            eval_stack.push(postfix[i] - '0');
        }
        
    }
    
    // The only remaining value in the stack is the answer
    return eval_stack.top();
}

//=============================================
//Do Not write code below this line
#endif
