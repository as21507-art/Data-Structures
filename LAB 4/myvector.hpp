//============================================================================
// Name         : myvector.hpp
// Author       : 
// Date Created : 
// Date Modified: 
// Description  : Vector implementation in C++
//============================================================================
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

// start_code+begins
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include <stdexcept>
#include<sstream>


using namespace std;
template <typename T>
class MyVector
{
	private:
		T *array;						//pointer to an array to store elements
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		MyVector(int cap=0);			//Constructor
		~MyVector();					//Destructor
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		void reserve(int new_cap);		//increase the capacity of the vector
		bool isEmpty() const; 			//Returns true if the vector is empty, False otherwise
		const T& front();				//Returns reference of the first element in the vector
		const T& back();				//Returns reference of the Last element in the vector
		void push_back(T element);		//Add an element at the end of vector
		void insert(int index, T element); //Add an element at the index 
		void erase(int index);			//Removes an element from the index
		T& operator[](int index);			//Returns the reference of an element at given index
		T& at(int index); 				//return reference of the element at given index
		void shrink_to_fit();			//Reduce vector capacity to fit its size
		void display();
		void display2(stringstream&);
};
#ifndef _WIN32
//======================================
template <typename T>
void MyVector<T>::display()
{
	cout<<"╔";
	
	for(int i=0; i<v_capacity; i++)
	{	
		cout<<"════";
		if(i!=v_capacity-1) cout<<"╦";
	}
	cout<<"╗ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"║";
		if(i<v_size)
			cout<<setw(4)<<array[i];
		else
			cout<<setw(4)<<" ";		
	}
	if(v_capacity==0) cout<<"║";
	cout<<"║"<<endl<<"╚";
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"════";
		if(i != v_capacity-1) cout<<"╩";
	}
	cout<<"╝ capacity = "<<v_capacity<<endl;	
}
//======================================
#else
template <typename T>
void MyVector<T>::display()
{
	cout<<"+";
	
	for(int i=0; i<v_capacity; i++)
	{	
		cout<<"----";
		if(i!=v_capacity-1) cout<<"+";
	}
	cout<<"+ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"|";
		if(i<v_size)
			cout<<setw(4)<<array[i];
		else
			cout<<setw(4)<<" ";		
	}
	if(v_capacity==0) cout<<"|";
	cout<<"|"<<endl<<"+";
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"----";
		if(i != v_capacity-1) cout<<"+";
	}
	cout<<"+ capacity = "<<v_capacity<<endl;	
}
#endif
//starter_code_ends
//========================================
//Please add your code below this line =============


// Exception class for vector empty case
class VectorEmpty: public exception {
    private:
        const char* message;
    public:
        VectorEmpty(const char* msg);
        virtual const char* what() const throw(){
            return message;
        }
};

// Constructor Method for VectorEmpty class
VectorEmpty::VectorEmpty(const char* msg) : message(msg){}


// Constructor Method: Initializes the capacity to the value provided as the argument and creates an array of that size. If no value is passed then the defaulty size is 0. It also sets the value of size to be 0
// Input: An integer value representing the initial capacity of the vector
template<typename T>
MyVector<T>::MyVector(int cap){
    v_capacity = cap;
    v_size = 0;
    array = new T [v_capacity];
}

// Destructor Method: Deallocates memory space used by the dynamically created array
template<typename T>
MyVector<T>::~MyVector(){
    delete [] array;
}

// reserve Method: Takes an integer value and resizes the vector and updates the capacity to the new value of the capacity if the new capcity is greater than the current capacity
// Input: An integer greater than the current capacity representing the new capacity
template<typename T>
void MyVector<T>::reserve(int new_cap){
    
    // Checking if the new capacity is greater
    if (new_cap > v_capacity){
        
        // Creating a new array of new capacity
        v_capacity = new_cap;
        T *new_array = new T [v_capacity];
        
        // Copying all the elements from the old array
        for(int i=0; i< v_size; i++){
            new_array[i] = array[i];
        }
        
        // Releasing the memory space for the old array and changing the array pointer to point to the new array
        delete [] array;
        array = new_array;
    }
    // Do nothing if the new capacity is not greater
    return;
}


// push_back Method: Adds a new element to the vector, if the capacity is reached then increases the capacity and adds the new element
// Input: An element of templated type to be added to the vector
template<typename T>
void MyVector<T>::push_back(T element){
    
    // Checking if the capacity is reached, and if it is then doubling the size of the array
    if (v_size == v_capacity){
        // if size was zero then the capacity needs to be initialized otherwise it needs to be doubled
        if (v_size == 0) reserve (1);
        else reserve(v_capacity * 2);
    }
    
    // Adding the new element to the available space and increasing the index
    array[v_size] = element;
    v_size += 1;
}

// insert Method: Takes an index and element as a parameter and inserts the object in the given index. Throws exception if the index is out of range
// Input: An integer representing the index at which the element is inserted and the element of the templated data type
template<typename T>
void MyVector<T>::insert(int index, T element){
    
    // Adding at index size is the same as pushback
    if (index == v_size){
        push_back(element);
    }
    
    // Checking the range of the index
    if (index >= 0 && index < v_size){
        
        // Checking if the capacity needs to be increased
        if (v_size == v_capacity){
            reserve(2 * v_capacity);
        }
            
        // Performing the shift operation
        for (int i = v_size; i > index;i--){
            array[i] = array[i - 1];
        }
        
        // Adding the data to the index and incrementing the size
        array[index] = element;
        v_size += 1;
    }
    
    else{
        
        // Throws an exception if the index is out of range
        throw out_of_range("Index out of range");
    }
}


// erase Method: Removes an element at the given index, throws index out of bounds if the index is not within the range
// Input: An integer representing the index whose data needs to be erased
template <typename T>
void MyVector<T>::erase(int index){
    
    // Checking the validity of the index, if invalid then throw an expression and do nothing
    if (!(index >= 0 && index <v_size)){
        throw out_of_range("Index out of range");
        return;
    }
    
    // Shifting the elements
    for (int i = index; i < v_size - 1; i++){
        array[i] = array[i + 1];
    }
    
    // Decrementing the value of size
    v_size -= 1;
}


// overloading [] Method: Mimics the [] operator for the vector, takes an index and gives the value at that index, the index is the offset to the array pointer
// Input: An integer representing the index of the vector
// Output: Returns a reference to the vector element at that index
template <typename T>
T& MyVector<T>::operator[](int index){
    return array[index];
}

// at Method: Similar to the [] operator in accessing the index but throws an exception if the index is out of range
// Input: An integer representing the index of the vector
// Output: Returns a reference to the vector element at that index
template <typename T>
T& MyVector<T>::at (int index){
    
    // Checking the validity of the index
    if (index >= 0 && index < v_size){
        return array[index];
    }
    // If invalid then throw an exception
    else{
        throw out_of_range("Index out of range");
    }
}

// front Method: Returns the reference to the first index of the vector
// Output: A reference to the first index of the vector
template <typename T>
const T& MyVector<T>::front(){
    
    // If empty then throw exception
    if (isEmpty()){
        throw VectorEmpty("Vector is empty");
    }
    // Otherwise return the index at 0
    else{
        return array[0];
    }
}


// back Method: Returns the reference to the last index of the vector
// Output: A reference to the last index of the vector
template <typename T>
const T& MyVector<T>::back(){
    
    // If empty then throw exception
    if (isEmpty()){
        throw VectorEmpty("Vector is empty");
    }
    // Otherwise return the index at v_size - 1
    else{
        return array[v_size - 1];
    }
}


// size Method: returns the current size of the vector
template <typename T>
int MyVector<T>::size() const {
    return v_size;
}

// capacity Method: returns the current capacity of the vector
template <typename T>
int MyVector<T>::capacity() const {
    return v_capacity;
}

// isEmpty Method: Checks if the vector has any elements
// Output: returns true if there is at least one element in the vector, returns false otherwise
template <typename T>
bool MyVector<T>::isEmpty() const {
    // Vector is empty if its size is 0
    return v_size == 0;
}


// shrink_to_fit Method: reduces the capacity of the array to be equal to the size of the vector
template <typename T>
void MyVector<T>::shrink_to_fit() {
    
    // Create a new array only if the size and capacity are different
    if (v_size < v_capacity){
        T* new_array = new T [v_size];
        
        // Copying the elements from the old array to new array
        for (int i = 0; i < v_size; i++){
            new_array[i] = array[i];
        }
        
        // Releasing memory from the old array and changing the pointer to new array
        delete [] array;
        array = new_array;
        
        // Updating the array size
        v_capacity = v_size;
    }
    
    // If the size and capacity are already equal then do nothing and return
    return;
}


//Do not add any code below this line ===============
#endif

