
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

// Methods for Translation Class

// Constructor Method: Takes a string of meanings and language as parameter and extracts each distinct meaning
// Input: A string representing a list of meanings and the language the meaning is of
Translation::Translation(string meanings, string language){
    this->language = language;
    string current_meaning = "";
    
    // Traversing through the string to extract each word
    for (char c : meanings){
        
        // Meanings are separated by semicolon
        if (char == ';'){
            this->meanings.push_back(meanings);
            current_meaning = "";
            continue;
        }
        else current_meaning += c;
    }
}


// addMeaning Method: Takes a new meaning(s), separated by semicolon and attemps to add it to the meanings list if it is not already present
// Input: A string representing a new meaning or meanings
void Translation::addMeaning(string newMeanings){
    
    string_current_meaning = "";
    
    // A flag to detect if the word is already present in the vector
    bool duplicate;
    
    // Traversing through the string to extract each word
    for (char c : newMeanings){
        
        // Meanings are separated by semicolon
        if (char == ';'){
            
            // Searching for the meaning in the vector
            for(int i = 0; i < this->meanings.size(); i++){
                
                // If duplicate is found, raise the flag and skip searching
                if (this->meanings.at(i) == current_meaning){
                    duplicate = true;
                    break;
                }
            }
            
            // Add the new meaning if and only if it was not duplicate
            if (not duplicate) this->meanings.push_back(current_meaning);
            
            // Reset the values for next word
            current_meaning = "";
            duplicate = false;
            continue;
        }
        
        // If semi colon is not found, continue adding the characters to form the word
        else current_meaning += c;
    }
}


//==============================================================================
// Methods for Entry Class

// Constructor Method: Initializes the word to the parameter value and sets the deleted flag to false, it also creates a translation object of given languages and adds it to the list of translation in translation vector
Entry::Entry(string word, string meanings, string language){
    this->word = word;
    this->deleted = false;
    
    // Adding a new translation object to the vector of translations
    this->translation.push_back(Translation(meanings, language));
}


// add Translation Method: Adds a new language and list of meanings
// Input: A string representing a list of meanings separated by semi colons, string representing a new language
void Entry::addTranslation(string newMeanings, string language){
    
    // Searching if the language is already present, if so then only add meanings to the existing language
    for(int i = 0; i < this->translations.size(); i++){
        if (this->translations.language == language){
            this->translations.addMeaning(newMeanings);
            return;
        }
    }
    
    // If the lanugage did not already exist then add a new translation object of that language
    this->translations.push_back(Translation(newMeanings, language));
}


// print Method: displays the word and all of its translations in different languages
void Entry::print(){
    
    // Traversing through the different translation languages
    for(int i = 0; i < this->translations.size(); i++){
        
        // Displaying the langugage of the translation
        cout << this->translations[i].language << " : ";
        
        // Traversing through the list of meanings and displaying them in a single line separated by semi colons
        for(int j = 0; j < this->translations[i].meanings.size(); j++){
            cout << this->translations[i].meanings[j] <<"; ";
        }
        
        // Begin a new line for each language
        cout << endl;
    }
}



//==============================================================================
// Methods for HashTable Class

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


// import Method: Attempts to read the file in the given path (a dictionary) and inserts them into the hash table
// Input: A file path representing the dictonary of translation
void import(string path){
    
    // Trying to read from the file of given path
    ifstream dictFile(path)
    
    // If the file does not exist then display the message and do nothing
    if (!inFile.is_open()) {
        cout << "File not found error" << endl;
        return;
    }
    
    // Declaring the entry (a line from the file) key and value(s)
    string entry;
    string key;
    string values;
    
    // An integer to find the index from where the value starts in the string representing the entry
    int val_index;
    
    // First line of the file is read to determine the language
    string language;
    getline(dictFile, language);
    
    // Extracting each line from the file as a unique word-translation entry
    while (getline(dictFile, entry)){
        
        // Initializing the parameters
        key = "";
        values = "";
        val_index = 0;
        
        // Traversing through the string to find key and values
        for (char c : entry){
            
            val_index += 1;
             
            // If a colon is found then it separates key from value and the colon is ignored
            if (c == ':') {
                
                // The rest of the string represents the values
                values = entry.substr(val_index);

                // Exit the loop after determining the key value strings
                break;
            }
            
            // If key is not found then append the character to the key
            else key += c;
            
        }
        
        // Inserting them to the hash table using the insert method
        insert(key, value, language)
    }
    
}


// insert Method: creats an entry with the given word and a string representing a list of entries and inserts them to the hash table
// Input: String represnting a word in English, String represnting a list of meanings in another language, a third string specifying the language
void insert(string word, string meanings,string language){
    
    // Find the index at which it should be stored
    unsigned long hash_code = hashCode(word);
    
    // Use the compression function (mod) to find the index
    int index = hash_code % capacity;
    
    // Flag to detect if the data was successfully inserted into the hash table or not
    bool failed = false;
    
    // A variable to be used as an offset for quadratic probing if needed
    int offset = 0;
    int probe;
    
    // Boolean to check if it was an update or it was an insert
    bool update = false;
    
    // If this is not a update insert, then the optimal position is this one
    int optimal_index = -1;
    
    // Traverse the hash table to search for an empty space
    while (not failed){
        
        probe = (index + offset * offset) % capacity;
        
        // Check if the current index is empty, if it is then no need to search further
        if (buckets[probe] == nullptr) break;
        
        // Checks if the keys match, the only value needs to be updated, and find this index
        else if (buckets[probe]->word == word){
            
            // If it was not deleted then it is just an update, temporarily delete this record to prevent duplicates
            if (buckets[probe]->deleted == false){
                update = true;
                buckets[probe]->deleted = true;
            }
            
            // If it was the first encountered spot then change the optimal state and then ensure it remains undeleted
            if (optimal_index == -1){
                optimal_index = probe;
                buckets[probe]->deleted = false;
            }
            
            // No need to search further if key was found
            break;
        }
        
        // If it is not NULL & keys don't match then check if it is a lazily deleted node, store it as optimal index if it was not found previously
        else if (buckets[probe]->deleted == true){
            if (optimal_index == -1) optimal_index = probe;
            offset += 1;
        }
        
        // If not then increment the offset to search for next index
        else offset += 1;
    
        // Preventing infinite loop (in case it occurs)
        if (offset >= capacity) failed = true;
    }
    
    // Display a message if the insertion was failed
    if (failed == true){
        cout << "Failed to insert into the hash table." << endl;
    }
    
    // If it was inserted, record the collisions
    else {
        
        // If it was not updated then increase the size and
        if (not update){
            size += 1;
            collision += offset;
        }
        
        // If optimal index was -1, the the first available space must have been an empty space
        if (optimal_index == -1){
            buckets[probe] = new Entry(word, meanings, language);
        }
        
        // If optimal index was an actual index, then the first available space was not empty
        else {
            buckets[optimal_index]->word = word;
            
            // A boolean value to check if the language already existed
            bool lang_existed = false;
            
            // Searching if the translation already exists in that langauge
            for (int i = 0; i < buckets[optimal_index]->translation.size(); i++){
                
                // If it does exist then only add the meanings at that language and mark the language as already existing
                if (buckets[optimal_index]->translations[i].language == language){
                    buckets[optimal_index]->translations[i].addMeaning(meanings);
                    lang_existed = true;
                    break;
                }
            }
            
            // If the language did not exist, then add the new language and its meanings
            if (not lang_existed) buckets[optimal_index]->translations.push_back(Translation(meanings, language));
            
            // Ensure the record is NOT DELETED at all
            buckets[optimal_index]->deleted = false;
        }
    }
}


// delWord Method:
void delWord(string word);
s

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
