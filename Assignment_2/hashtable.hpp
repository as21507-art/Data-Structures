
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
        // is the bucket is available to be reused after being deleted
		bool deleted;
	public:
		Entry(string word, string meanings,string language);
		void addTranslation(string newMeanings, string language);
		void print();
		friend class HashTable;
};

class HashTable
{
	private:
        // Array of Pointers to Entries for Linear and Quadratic Probing
		Entry **buckets;
        //Current Size of HashTable
		unsigned int size;
        // Total Capacity of HashTable
		unsigned int capacity;
        // Total Number of Collisions
		unsigned int collisions;
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

// Helper function to convert a single string into all lower case characters, this helps in hashing variants of a word into the same bucket regardless of their cases
string toLower(string str){

    for (char &c : str){
        c = tolower(c);
    }
    
    return str;
}


// Helper function to compare two strings that ignores their cases (upper-case, lower-case does not matter)
// Input: Two strings having same alphabets but may differ in upper or lower case
// Output: Compares the string case insensitively and returns true if they are the same
bool compare(string string_1, string string_2){
    
    // Determine the boolean value from unequal length directly
    if (string_1.length() != string_2.length()) return false;
    
    // If they have equal length then only convert both of them to lower case and compare
    return toLower(string_1) == toLower(string_2);
}


// Helper function to check if the given string has garbage values (ie. only combination of spaces and semicolons)
// Input: A string
// Output: True if it only contains spaces and ;, false if it has even one character that is not semi colons and spaces
bool check_nonsense(string str){
    
    for(char c : str){
        if (c == ' ' || c == ';') continue;
        return false;
    }
    
    return true;
}


// Methods for Translation Class

// Constructor Method: Takes a string of meanings and language as parameter and extracts each distinct meaning
// Input: A string representing a list of meanings and the language the meaning is of
Translation::Translation(string meanings, string language){
    this->language = language;
    string current_meaning = "";
    
    // Traversing through the string to extract each word
    for (char c : meanings){
        
        // Meanings are separated by semicolon
        if (c == ';'){
            this->meanings.push_back(current_meaning);
            current_meaning = "";
            continue;
        }
        else current_meaning += c;
    }
    
    // Add the last meaning to the list if it is not an empty string
    if (current_meaning != ""){
        this->meanings.push_back(current_meaning);
    }
}


// addMeaning Method: Takes a new meaning(s), separated by semicolon and attemps to add it to the meanings list if it is not already present
// Input: A string representing a new meaning or meanings
void Translation::addMeaning(string newMeanings){
    
    string current_meaning = "";
    
    // A flag to detect if the word is already present in the vector
    bool duplicate = false;
    
    // Traversing through the string to extract each word
    for (char c : newMeanings){
        
        // Meanings are separated by semicolon
        if (c == ';'){
            
            // Searching for the meaning in the vector
            for(int i = 0; i < this->meanings.size(); i++){
                
                // If duplicate is found, raise the flag and skip searching
                if (compare(this->meanings.at(i), current_meaning)){
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
    
    // Adding the last word into the list of meanings
    if (current_meaning != ""){
        
        // Searching for the meaning in the vector
        for(int i = 0; i < this->meanings.size(); i++){
            
            // If duplicate is found, raise the flag and skip searching
            if (compare(this->meanings.at(i), current_meaning)){
                duplicate = true;
                break;
            }
        }
        
        // Add the new meaning if and only if it was not duplicate
        if (not duplicate) this->meanings.push_back(current_meaning);
    }
}


//==============================================================================
// Methods for Entry Class

// Constructor Method: Initializes the word to the parameter value and sets the deleted flag to false, it also creates a translation object of given languages and adds it to the list of translation in translation vector
Entry::Entry(string word, string meanings, string language){
    this->word = word;
    this->deleted = false;
    
    // Adding a new translation object to the vector of translations
    this->translations.push_back(Translation(meanings, language));
}


// add Translation Method: Adds a new language and list of meanings
// Input: A string representing a list of meanings separated by semi colons, string representing a new language
void Entry::addTranslation(string newMeanings, string language){
    
    // Searching if the language is already present, if so then only add meanings to the existing language
    for(int i = 0; i < this->translations.size(); i++){
        if (compare(this->translations[i].language,language)){
            this->translations[i].addMeaning(newMeanings);
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
            if (j >= this->translations[i].meanings.size() - 1){
                
                // Do not display semi colon after the last word
                cout << this->translations[i].meanings[j];
            }
            else{
                
                // Display semi colon to separate words in the middle
                cout << this->translations[i].meanings[j] <<"; ";
            }
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
unsigned int HashTable::getSize() {
    return size;
}


// getCollision Method: Returns the number of collisions that have occurred during insertion
unsigned int HashTable::getCollisions(){
    return collisions;
}


// hashCode Method: Computes the hash code of the given key
// Input: A string representing a key of an entry
// Output: An unsigned long integer representing the hash code of the function
unsigned long HashTable::hashCode(string key){
    
    // Converting the key to all lowercase
    key = toLower(key);
    
    // Initializing the parameters for polynomial hashing
    int a = 33;
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
void HashTable::import(string path){
    
    // Trying to read from the file of given path
    ifstream dictFile(path);
    
    // If the file does not exist then display the message and do nothing
    if (not dictFile.is_open()) {
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
    
    // Counting the number of words in the dictionary
    unsigned int count = 0;
    
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
        insert(key, values, language);
        
        // Updating the count
        count += 1;
    }
    
    // Displaying the number of words imported from the dictionary file
    cout << count << " " << language << " words have been imported succcessfully." << endl;
    
}


// insert Method: creats an entry with the given word and a string representing a list of entries and inserts them to the hash table
// Input: String represnting a word in English, String represnting a list of meanings in another language, a third string specifying the language
void HashTable::insert(string word, string meanings,string language){
    
    // Check if the word, string and language have empty values and nonsense combination of ;; ;;; ;; only
    if (check_nonsense(word) || check_nonsense(meanings) || check_nonsense(language)) return;
    
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
        else if (compare(buckets[probe]->word, word)){
            
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
    
    // If insertion did not fail then run the following code to insert
    else {
        
        // If it was not updated then increase the size and count the collisions
        if (not update){
            size += 1;
            collisions += offset;
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
            for (int i = 0; i < buckets[optimal_index]->translations.size(); i++){
                
                // If it does exist then only add the meanings at that language and mark the language as already existing
                if (compare(buckets[optimal_index]->translations[i].language, language)){
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
void HashTable::delWord(string word){

    // Find the index at which it should have been stored by using hashing function followed by compression function
    unsigned long hash_code = hashCode(word);
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
        if (buckets[probe] == nullptr) notFound = true;
        
        // Entry is found if the keys match and the entry was not deleted
        else if (compare(buckets[probe]-> word, word) && buckets[probe]-> deleted == false) {
            
            // Delete the record lazily and decrement the size
            buckets[probe] -> deleted = true;
            size -= 1;
            
            cout << word << " has been successfully deleted from the Dictionary." << endl;
            
            // Exit the function immediately after successful deletion
            return;
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

    // Display a not found message if the record was not found in the dictionary
    if (notFound){
        cout << word << " not found in the Dictionary." << endl;
    }
}



// delTranslation Method: Deletes the translations of a word in the given language
// Input: A string representing the word and the language in which its translation needs to be deleted
void HashTable::delTranslation(string word, string language){
    
    // Find the index at which it should have been stored by using hashing function followed by compression function
    unsigned long hash_code = hashCode(word);
    int index = hash_code % capacity;

    // Flag to detect if the word was not found in the hash table
    bool word_notFound = false;

    // An offest to be used in quadratic probing
    int offset = 0;
    int probe;

    // Traversing through the hash table to find the corresponding keys
    while (not word_notFound){
        
        probe = (index + offset * offset) % capacity;
        
        // If the entry was NULL then that means it does not exist (if it did, it should have been there instead of NULL)
        if (buckets[probe] == nullptr) word_notFound = true;
        
        // Entry is found if the keys match and the entry was not deleted
        else if (compare(buckets[probe]-> word, word) && buckets[probe]-> deleted == false) {
            
            // Check if the language is present and delete it
            for (int i = 0; i < buckets[probe]->translations.size(); i++){
                if (compare(buckets[probe]->translations[i].language, language)){
                    buckets[probe]->translations.erase(buckets[probe]->translations.begin() + i);
                    
                    // Check if there are any translations remaining, if not then delete the entire word
                    if (buckets[probe]->translations.size() == 0) delWord(word);
                    
                    cout << "Translation has been successfully deleted from the Dictionary." << endl;
                    
                    // Exit the function immediately after successful deletion
                    return;
                }
            }
            
            // If translation not found, do nothing
            return;
        }
        
        // if record is not found then change the offset and search again
        else{
            offset += 1;
            
            // Do nothing if the index is not found, this line prevents infinite loop
            if (offset >= capacity) {
                word_notFound = true;
            }
        }
    }

    // Display a not found message if the word was not found in the dictionary
    if (word_notFound) cout << word << " not found in the Dictionary." << endl;

}


// delMeaning Method: Deletes the meaning of a word in the given language
// Input: A string representing the word, another representing its meaning and a third string of language of the meaning
void HashTable::delMeaning(string word, string meaning, string language){
    
    // Find the index at which it should have been stored by using hashing function followed by compression function
    unsigned long hash_code = hashCode(word);
    int index = hash_code % capacity;

    // Flag to detect if the word was not found in the hash table
    bool word_notFound = false;

    // An offest to be used in quadratic probing
    int offset = 0;
    int probe;

    // Traversing through the hash table to find the corresponding keys
    while (not word_notFound){
        
        probe = (index + offset * offset) % capacity;
        
        // If the entry was NULL then that means it does not exist (if it did, it should have been there instead of NULL)
        if (buckets[probe] == nullptr) word_notFound = true;
        
        // Entry is found if the keys match and the entry was not deleted
        else if (compare(buckets[probe]-> word, word) && buckets[probe]-> deleted == false) {
            
            // Check if the language is present
            for (int i = 0; i < buckets[probe]->translations.size(); i++){
                if (compare(buckets[probe]->translations[i].language, language)){
                    
                    // Now search for the word in the given language
                    for (int j = 0; buckets[probe]->translations[i].meanings.size(); j++){
                        
                        // If the meaning is found, delete it from the list of meanings
                        if (compare(buckets[probe]->translations[i].meanings[j], meaning)){
                            
                            // Erase method only accepts iterator so convert the index to iterator by using ___.begin() + j
                            buckets[probe]->translations[i].meanings.erase(buckets[probe]->translations[i].meanings.begin() + j);
                            
                            // If the translation has no meanings left then delete the translation
                            if (buckets[probe]->translations[i].meanings.size() == 0) delTranslation(word, language);
                            
                            return;
                        }
                    }
                    
                    // If the meaning is not found in translation, do nothing
                    return;
                }
            }
            
            // If translation not found, do nothing
            return;
        }
        
        // If record is not found then change the offset and search again
        else{
            offset += 1;
            
            // Do nothing if the index is not found, this line prevents infinite loop
            if (offset >= capacity) {
                word_notFound = true;
            }
        }
    }

    // Display a not found message if the word was not found in the dictionary
    if (word_notFound) cout << word << " not found in the Dictionary." << endl;

}



// exportData Method:
void HashTable::exportData(string language, string filePath){
    
    // Creating a new file of the given path
    ofstream LangFile(filePath);
    
    // If file could not be created then display the message and exit the function
    if (not LangFile.is_open()){
        cout << "Unable to create a file." << endl;
        return;
    }
    
    // Adding the language name to the file
    LangFile << language << endl;
    
    // A string to store the meanings of all the words in a given format
    string meanings_string = "";
    string file_line = "";
    
    // Traverse through the entire bucket arrays to find if the language exists
    for(int i = 0; i < capacity; i++){
        
        // Ignore Null pointers and deleted entries
        if (buckets[i] != nullptr && buckets[i]->deleted == false){
            
            // Check if the given word has any translations in that language
            for (int j = 0; j < buckets[i]->translations.size(); j++){
                if (compare(buckets[i]->translations[j].language, language)){
                    
                    // Extract all the translations and then create a single string
                    meanings_string = "";
                    file_line = "";
                    
                    // Semi colons are placed after the word until the second-to-last meaning
                    for (int k = 0; buckets[i]->translations[j].meanings.size() - 1; k++){
                        meanings_string += buckets[i]->translations[j].meanings[k];
                        meanings_string += ";";
                    }
                    
                    // Adding the last word to the string
                    meanings_string += buckets[i]->translations[j].meanings[buckets[i]->translations[j].meanings.size() - 1];
                    
                    // Adding the root word to form a single line in the file
                    file_line = buckets[i]->word + ":" + meanings_string;
                    
                    // Adding the line in the file
                    LangFile << file_line << endl;
                    
                    // Exit the loop after the translation in the given language is found
                    break;
                }
            }
        }
    }
}


// find Method: Searches for a word in the dictionary, displays the number of comparisons made to find the word and all of its translations
// Input: A string representing a word to search for
void HashTable::find(string word){
    
    // Find the index at which it should have been stored by using hashing function followed by compression function
    unsigned long hash_code = hashCode(word);
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
        if (buckets[probe] == nullptr) notFound = true;
        
        // Entry is found if the keys match and the entry was not deleted
        else if (compare(buckets[probe]->word, word) && buckets[probe]->deleted == false) {
            
            // Displaying the collisions
            cout << word << " found in the Dictionary after " << offset + 1 << " comparisons." << endl;
            
            // Displaying the translations in all languages
            buckets[probe]->print();
            
            // Exit the function after displaying its translations
            return;
        }
        
        // If record is not found then change the offset and search again
        else{
            offset += 1;
            
            // Preventing infinite loop if the index is not found
            if (offset >= capacity) notFound = true;
        }
    }
    
    // If it was not found, then only the following code executes
    cout << word << " not found in the Dictionary." << endl;
    
}


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
