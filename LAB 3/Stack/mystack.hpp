/**
 * @file 
 * @author 
 * @description 
 * @date
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
// Usage: If the array functioning as stack has reached the maximum number of elements it can add.
class StackFull : public exception {
    public:
        StackFull(string m = "Stack is Full");
        virtual const char* what() const throw();
    private:
        string message;
}

// Constructor method for StackFull
StackFull::StackFull(string m): message(m){}

// Redefining what method
virtual const char* StackFull::what() const throw(){
    return message;
}

// StackEmpty Exception
// Usage:
class StackEmpty : public exception {
    public:
        StackEmpty(string m = "Stack is Empty");
        virtual const char* what() const throw();
    private:
        string message;
}

// Constructor method for StackEmpty
StackEmpty::StackEmpty(string m): message(m){}

// Redefining what method
virtual const char* StackEmpty::what() const throw(){
    return message;
}



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
    array = new int [n];
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
isBalanced(string expression){
    // Stack to store the paranthesis with capacity expression.size() because any string can have brackets at most equal to its whole length
    char MyStack<char> para_stack(expression.size());
    
    try{
        // Traversing through the string
        for (int i = 0; i < expression.size(); i++){
            
                // Push if an opening bracket is found
                if (expression[i] == '(') para_stack.push('(');
                
                // Remove the most recent opening bracket if a closing bracket is found
                else if (expression[i] == ')') para_stack.pop();
                
                // Go to next char if the expression is
                else continue;
        }
        
        // If stack is not empty then opening bracket does not have a closing bracket
        if (!para_stack.isEmpty()) return false;
        
        else return true;
    }
    catch (exception &e){
        return false;
    }
}


//
string convert(string expression){
    
    // Stack to perform the postfix algorithm
    MyStack<int> post_stack(expression.size());
    
    // String variable to store the postfix expression
    string postfix_exp = "";
    
    // Traversing through the string
    for (int i = 0; i < expression.size(); i++){
        if (expression[i] == '('){
            post_stack.push('(');
        }
        else if (expression[i] == ')'){
            // Checking if the
            while (true){
                postfix_exp += post_stack.top();
                post_stack.pop();
                if (post_stack.top() == '('){
                    post_stack.pop();
                    break;
                }
            }
        }
        else if (isOperator(expression[i])){
            while (!post_stack.isEmpty() && post_stack.top() != '('){
                
            }
        }
        else {
            postfix_exp += expression[i];
        }
    }
    
    return postfix_exp;
}

float evaluate(string postfix_exp){
    
    // A stack to evaluate the postfix notation
    MyStack<float> eval_stack(postfix_exp.size());
    
    // Variables to store the popped contents of the stack during evaluation
    float right;
    float left;
    
    // Traversing through the postfix notation
    for (int i = 0; i < postfix_exp.size(); i++){
        
        if (isOperator(postfix_exp[i])){
            right = eval_stack.top();
            eval_stack.pop();
            left = eval_stack.top();
            eval_stack.pop();
        
            eval_stack.push(operate(postfix_exp[i], left, right));
        }
        
        else{
            eval_stack.push(postfix_exp[i]);
        }
        
    }
    return eval_stack.top();
}

float operate(char op, float left, float right){
    if (op=='+'){
        return left + right;
    }
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
        return left ^ right;
    }
    else{
        throw runtime_error("Invalid math symbol")
    }
}


//=============================================
//Do Not write code below this line
#endif
