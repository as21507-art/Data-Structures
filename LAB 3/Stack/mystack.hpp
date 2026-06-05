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


// Defining the MyStack Class
template <typename T>
class MyStack {
    
    private:
        // A pointer that dynamically allocates memory
        T* array;
    
        // Number of elements in the array
        int size;
    
    public:
        // Constructor Method
        MyStack(int n = 0);
    
        // Destructor Method
        ~MyStack();
    
        void push (T elem);
        void pop ();
        T& top();
        int size();
        bool isEmpty();
};

// Constructor Method: Initializes the size to 0 and allocates a dynamic array of given size to be used as a stack (Default size of array is 0)
MyStack::MyStack(int n){
    size = 0;
    array = new int [n];
}

// Destructor Method: Deallocates the memory space for the array and deletes every attributes
MyStack::~MyStack(){
    delete [] array;
}

// push Method: Takes a data and attempts to add it to the stack, 




//=============================================
//Do Not write code below this line
#endif
