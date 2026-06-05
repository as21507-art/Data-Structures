/**
 * @file queue.hpp
 * @author 
 * @data
 * @Array Based Circular Queue implementation in C++
 */
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include<iostream>
#include<exception>	 
//=========== Queue Class =========================
template <typename T>
class Queue
{
	private:
		T *array;
		int capacity;	//Max Capacity of the Queue
		int size;		//current number of elements in the Queue
		int front;		//front of the Queue
		int rear;		//index where a new element will be added
	public:
		Queue(int cap=0);
		~Queue();
		void enqueue(T); 
		T dequeue();
		bool isEmpty() const;
		bool isFull() const;

		/* Required for Autograder — Do not remove */
		friend void display();
		friend void run_tests();
};
//=============================================================
//Please define/implement the required methods below this line
//=============================================================


// Constructor Method
template <typename T>
Queue<T>::Queue(int cap) {
    capacity = cap;
    size = 0;
    front = 0;
    rear = 0;
    // Creating the array of the given capacity
    array = new T [capacity];
}

// Destructor Method
template <typename T>
Queue<T>::~Queue(){
    // Deallocating the dynamically created array
    delete [] array;
}

// Enqueue Method: Takes a new data to add to the queue if the queue has available space, throws an exception if the queue is full
template <typename T>
void Queue<T>::enqueue(T data){
    // Queue is full case
    if (isFull()) throw std::runtime_error("Queue is Full");
    else{
        array[rear] = data;
        rear = (rear + 1) % capacity;
        size += 1;
    }
}
// Dequeue Method: Removes a data from the front of the queue and returns that value, if the queue is empty, it throws an exception
template <typename T>
T Queue<T>::dequeue(){
    // Queue is empty case
    if (isEmpty()) throw std::runtime_error("Queue is Empty");
    else{
        T temp = array[front];
        front = (front + 1) % capacity;
        size -= 1;
        return temp;
    }
}

// isEmpty Method: Checks if the queue is empty, returns true if it is, otherwise it returns false
template <typename T>
bool Queue<T>::isEmpty() const {
    return (size == 0);
}

// isFull Method: Checks if the queue is full, returns true if it is, otherwise it returns false
template <typename T>
bool Queue<T>::isFull() const {
    return (size == capacity);
}


//=============================================================
//Do not write any code below this line
#endif
