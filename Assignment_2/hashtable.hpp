
#ifndef _HASHTABLE_HPP
#define _HASHTABLE_HPP
#include <vector>
#include <string>
using namespace std;


class Translation
{
	private:
		string language;
		vector<string> meanings;
	public:
		Translation(string meanings,string language);
		void addMeaning(string newMeanings);
		friend class Entry;
		friend class HashTable;
};

class Entry
{
	private:
		string word;
		vector<Translation> translations;
		bool deleted;  // is the bucket is available to be reused after being deleted
	public:
		Entry(string word, string meanings,string language);
		void addTranslation(string newMeanings, string language);
		void print();
		friend class HashTable;
};

class HashTable
{
	private:
		Entry **buckets;		        			// Array of Pointers to Entries for Linear and Quadratic Probing
		unsigned int size;					   		//Current Size of HashTable
		unsigned int capacity;				    	// Total Capacity of HashTable
		unsigned int collisions; 					// Total Number of Collisions
	public:
		HashTable(int capacity);
		unsigned long hashCode(string word);
		unsigned int getSize();
		unsigned int getCollisions();
		void import(string path);
		void insert(string word, string meanings,string language);
		void delWord(string word);
		void delTranslation(string word, string language);
		void delMeaning(string word, string meaning, string language);
		void exportData(string language, string filePath);
		void find(string word);
		~HashTable();
		//You may add more helper methods however you are not allowed to change the 
		//signature of the already given methods. 
};
//================================================================================
//Define the methods below this line

// Constructor Method: Takes an integer representing the capacity as the parameter and initializes the capacity to this value, then dynamically creates an array of Entry pointers of this capacity, initializes size and collisions to 0;
HashTable::HashTable(int cap){
    this->capacity = cap;
    this->size = 0;
    this->collisions = 0;
    
    buckets = new Entry* [capacity];
    
    // Traversing every index of the bucket array and initializing them to nullptr
    for (int i = 0; i < capacity; i++){
        buckets[i] = nullptr;
    }
}


// getSize Method: Returns the number of elements currently stored in the hash table
unsigned int getSize() {
    return size;
}


// getCollision Method: Returns the number of collisions that have occurred during insertion
unsigned int getCollisions(){
    return collisions
}


// hashCode Method: Computes the hash code of the given key
// Input: A string representing a key of an entry
// Output: An unsigned long integer representing the hash code of the function
unsigned long hashCode(string key){
    
    // Initializing the parameters for polynomial hashing
    int a = 3;
    int expo = 0;
    
    unsigned long hash_code = 0;
    
    // Accessing each character of the key
    for (char c: key){
        hash_code += c * (int)pow(a, expo);
        
        // Go to the next exponent
        expo += 1;
    }
    
    return hash_code;
}


// import Method:
void import(string path);


// insert Method:
void insert(string word, string meanings,string language);


// delWord Method:
void delWord(string word);


// delTranslation Method:
void delTranslation(string word, string language);


// delMeaning Method:
void delMeaning(string word, string meaning, string language);


// exportData Method:
void exportData(string language, string filePath);


// find Method:
void find(string word);


// Destructor Method: Deletes the dynamically allocated array of pointers to release memory space
HashTable::~HashTable(){
    
    // Releasing memory space from each pointer in bucket array
    for (int i = 0; i < capacity; i++){
        delete buckets[i];
    }
    
    delete [] buckets;
}


// Do not add code below this line
#endif
