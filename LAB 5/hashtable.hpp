//============================================================================
// Name         : hashtable.hpp
// Author       : Aashish Shrestha
// Version      : 1.0
// Date Created : 
// Date Modified: 12/6/2025
// Description  : HashTable Implementation using C++
//============================================================================
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<iomanip>
#include<string>
#include<list>
using std::string;
using std::cout;
using std::endl;

class Entry
{
	private:
		string key;
		string value;
		bool deleted; 	//Is the bucket available to be reused (after deletion)
	public:
		Entry(string key, string value)
		{
			this->key = key;
			this->value = value;
			this->deleted = false;
		}
		friend class HashTable;
};

class HashTable
{
	private:
		Entry **buckets;		        			// Array of Pointers to Entries
		unsigned int capacity;				    	// Total Capacity of Hash Table
		unsigned int size;					   		// Current # of entries in the Hash Table
		unsigned int collisions; 					// Total Number of Collisions
	public:
		HashTable(int capacity);
		unsigned int getSize();
		unsigned int getCollisions();
		unsigned long hashCode(const string key);
		void insert(const string key, const string value);
		void remove(string key);
		string get(const string key);
		~HashTable();
};
//===================================================
//Starter-code ends.
//Please add your code below this line.


// Constructor Method: Creates an array (bucket) of enrty pointers and initializes all of them to NULL
// Takes capacity as the parameter which defines the maximum size of the buckets array; it also initializes the size to 0
HashTable::HashTable(int cap){
    
    // Initializing capacity and using it to dynamically create an array of that size
    capacity = cap;
    buckets = new Entry* [capacity];
    size = 0;
    collisions = 0;
    
    // Traversing each element in the array and setting them to NULL
    for (int i = 0; i < capacity; i++){
        buckets[i] = NULL;
    }
    
}


// getSize Method: Returns the number of entries currently stored in the hash table
// Ouput: Returns an unsigned integer representing the number of entries
unsigned int HashTable::getSize(){
    return size;
}


// getCollision Method: Returns the number of collisions that occured while attempting to insert data into the hash table
// Ouput: Returns an unsigned integer representing the number of entries
unsigned int HashTable::getCollisions(){
    return collisions;
}


// hashCode Function: Takes a key parameter and calculates its corresponding hash code that can be used to find its location in the hash table
// Input: A read only key parameter whose hashCode is calculated
// Ouput: An unsigned long integer representing the hash code
unsigned long HashTable::hashCode(const string key){
    
    // Constant for polynomial hashing and an exponent that the constant will be raised to
    int a = 13;
    int expo = 0;
    
    // A variable to store the resulting value after applying the hash function
    unsigned long code = 0;
    
    // Accessing each character of the string
    for(char c : key){
        
        // Using polynomial hashing
        code += c * (int)pow(a, expo);
        
        // Incrementing the exponent for the next value
        expo += 1;
    }
    
    return code;
    
}


// insert Method: Takes a key and its value and attempts to insert it into the hash table at the index determined by the hash function
// Input: Two string representing key and its value respectively
void HashTable::insert(const string key, const string value){
    
    // Find the index at which it should be stored
    unsigned long hash_code = hashCode(key);
    
    // Use the compression function (mod) to find the index
    int index = hash_code % capacity;
    
    // Flag to detect if the data was successfully inserted into the hash table or not
    bool failed = false;
    
    // A variable to be used as an offset for quadratic probing if needed
    int offset = 0;
    int probe;
    
    // Boolean to check if it was an update or it was an insert
    bool update = false;
    
    // Finds the optimal position of insertion in the hash table
    int optimal_index = -1;
    
    // Collisions for current index
    int curr_collision = 0;
    
    // Traverse the hash table to search for an empty space
    while (not failed){
        
        probe = (index + offset * offset) % capacity;
        
        // Check if the current index is empty, if it is then no need to search further
        if (buckets[probe] == NULL) break;
        
        // Checks if the keys match, the only value needs to be updated, and find this index
        else if (buckets[probe]->key == key){
            
            // If it was not deleted then it is just an update, temporarily delete this record to prevent duplicates
            if (buckets[probe]->deleted == false){
                update = true;
            }
            
            // If a key was found, then it must be inserted in this same location to prevent duplicate keys
            optimal_index = probe;
            curr_collision = offset;
            
            // No need to search further if key was found
            break;
        }
        
        // If it is not NULL & keys don't match then check if it is a lazily deleted node, store it as optimal index if it was not found previously
        else if (buckets[probe]->deleted == true){
            if (optimal_index == -1) {
                optimal_index = probe;
                curr_collision = offset;
            }
            offset += 1;
        }
        
        // If not then increment the offset to search for next index and record the collision
        else {
            offset += 1;
        }
        
        // Preventing infinite loop (in case it occurs)
        if (offset >= capacity) failed = true;
    }
    
    // Display a message if the insertion was failed (if there was no null space but there was a deleted entry, the it is a pseudo-failed case)
    if (failed == true && optimal_index == -1){
        cout << "Failed to insert into the hash table." << endl;
        return;
    }
    
    // If insertion did not fail, then insert the key value pair in its appropriate location
    if (update == true){
        cout << "Existing record has been updated." << endl;
    }
    else{
        size += 1;
        cout << "New record has been added successfully." << endl;
    }
    
    // If optimal index was -1, the the first available space must have been an empty space
    if (optimal_index == -1){
        buckets[probe] = new Entry(key, value);
    }
    
    // If optimal index was an actual index, then the first available space was not empty
    else {
        buckets[optimal_index]->key = key;
        buckets[optimal_index]->value = value;
        buckets[optimal_index]->deleted = false;
    }
}


// remove Method: Takes a key and removes any occurence of the key form the hash table, searching its location using the hash function followed by quadratic probing if required
// Input: A key whose entry needs to be removed from the hash table
void HashTable::remove(string key){
    
    // Find the index at which it should have been stored by using hashing function followed by compression function
    unsigned long hash_code = hashCode(key);
    int index = hash_code % capacity;
    
    // Flag to detect if the record was not found in the hash table
    bool notFound = false;
    
    // An offest to be used in quadratic probing
    int offset = 0;
    int probe;
    
    // Traversing through the hash table to find the corresponding keys
    while (not notFound){
        
        probe = (index + offset * offset) % capacity;
        
        // If the entry was NULL then that means it does not exist (if it did, it should have been there instead of NULL)
        if (buckets[probe] == NULL) notFound = true;
        
        // Entry is found if the keys match and the entry was not deleted
        else if (buckets[probe]-> key == key && buckets[probe]-> deleted == false) {
            
            // Delete the record lazily and decrement the size
            buckets[probe] -> deleted = true;
            size -= 1;
            
            cout << key << " has been successfully removed!" << endl;
            break;
        }
        
        // if record is not found then change the offset and search again
        else{
            offset += 1;
            
            // Do nothing if the index is not found, this line prevents infinite loop
            if (offset >= capacity) {
                notFound = true;
            }
        }
    }
    
    if (notFound) cout << key << " not found." << endl;
}


// get Method: Takes a key, searches for the key in the has table and returns the value
// Input: A string representing the key to be searched
// Ouput: Corresponding value to the key or the message "Record not found!" if it was not found
string HashTable::get(const string key){
    
    // Find the index at which it should have been stored by using hashing function followed by compression function
    unsigned long hash_code = hashCode(key);
    int index = hash_code % capacity;
    
    // Flag to detect if the record was not found in the hash table
    bool notFound = false;
    
    // An offest to be used in quadratic probing
    int offset = 0;
    int probe;
    
    // Traversing through the hash table to find the corresponding keys
    while (not notFound){
        
        probe = (index + offset * offset) % capacity;
        
        // If the entry was NULL then that means it does not exist (if it did, it should have been there instead of NULL)
        if (buckets[probe] == NULL) notFound = true;
        
        // Entry is found if the keys match and the entry was not deleted
        else if (buckets[probe]-> key == key && buckets[probe]-> deleted == false) {
            
            // Displaying the collisions
            cout << "comparisions = " << offset + 1 << endl;
            return buckets[probe]->value;
        }
        
        // if record is not found then change the offset and search again
        else{
            offset += 1;
            
            // Preventing infinite loop if the index is not found
            if (offset >= capacity) notFound = true;
        }
    }
    
    // If it was not found, return a message with the pronmpt
    return "Record not found!";
    
}


// Destructor Method: Deletes the dynamically allocated double pointer array
HashTable::~HashTable(){
    
    // Deleting all the entry pointers within the 2D buckets array
    for (int i = 0; i < capacity; i++){
        delete buckets[i];
    }
    
    // Deleting the main array
    delete [] buckets;
}


//Please do not add any code below this line.
//======================================================
#endif
