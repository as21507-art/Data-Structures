/**
 * @file lab11.hpp
 * @author Aashish Shrestha
 * @description BST Tree implementation in C++
 * @date 2022-11-03
 */
#ifndef BST_HPP
#define BST_HPP
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<math.h>
#include<queue>
#include<vector>

using namespace std;

class Node
{
    private:
        int key;
        Node* left;
        Node* right;
        Node* parent;
    public:
        Node(int key): key(key),left(nullptr),right(nullptr), parent(nullptr) {}
        ~Node()
        {
            if(this->left !=nullptr)
                delete this->left;
            if(this->right!=nullptr)
                delete this->right;
        }
        int getKey() { return this->key;}
        friend class BST;
};
//=============================================================================
class BST
{
    private:
        Node *root;
    public:
        BST();                                    //constructor
        ~BST();                                    //destructor
        Node* getRoot();                        //returns the root of the Tree
        void insert(Node* ptr,int key);            //Insert key into tree/subtree with root ptr
        int height(Node *ptr);                    //Find the height of a tree/subtree with root ptr
        Node* find(Node *ptr,int key);            //Find and returns the node with key
        Node* findMin(Node *ptr);                //Find and return the Node with minimum key value from a tree/subtree with root ptr
        Node* findMax(Node *ptr);                //Find and return the Node with Max key value from a tree/subtree with root ptr
        void remove(Node *ptr,int key);            //Remove a node with key from the tree/subtree with root
        void printInorder(Node* ptr);            //Traverse (inorder) and print the key of a tree/subtree with root ptr
        void display();                            //Print 2D Tree

        // Helper Methods
        void copyKey(Node* ptr1, Node* ptr2);
    
        //Required for the Autograder. DO NOT remove or implement it
        void inorder(Node *ptr,ostream &sstr);
};
//===============================================================
//Print a 2D Tree
void BST::display()
{
    cout<<"Tree:"<<endl;

    int levels = height(this->root);
    int max_nodes = pow(2,levels+1)-1;
    queue<Node*> myQueue;
    vector<Node*> myVector;
    myQueue.push(this->root);

    // Traverse the tree in Breadth First Order and store each node into myVector
    for(int i=0; i<max_nodes; i++)
    {
        Node* cur = myQueue.front();
        myQueue.pop();
        myVector.push_back(cur);
        if(cur != nullptr)
        {
            myQueue.push(cur->left);
            myQueue.push(cur->right);
        }
        else //For Empty nodes push nullptr(placeholder) in Queue
        {
            myQueue.push(nullptr);
            myQueue.push(nullptr);
        }
    }

    if(max_nodes >0)            //if a non-empty tree
    {
        int *spaces = new int[levels+1];
        spaces[levels]=0;
        int level=0;

        for(int j=levels-1; j>=0; j--)
            spaces[j]=2*spaces[j+1]+1;
        
        for (int i=0; i<max_nodes; i++)
        {
            if(i == (pow(2,level)-1))    // if first node of a level
            {
                cout<<endl<<endl;        // go to next line
                for(int k=0; k<spaces[level]; k++)    //print sufficient spaces before printing the first node of a level
                   cout<<"   ";
                
                level++;
            }
            if(myVector[i]!=nullptr)     cout<<std::left<<setw(3)<<myVector[i]->getKey();
            else                         cout<<std::left<<setw(3)<<" ";
            if(level>1)
                for(int k=0; k<spaces[level-2]; k++)    // print spaces between two nodes on same level
                    cout<<"   ";
        }

        cout<<endl;
        for(int i=0; i<pow(levels,2.5); i++)    //Add last line with ----
            cout<<"___";
        
        cout<<endl;
        delete[] spaces;
    }
}

//=====================================================================
//Please add your code below this line.


// Constructor Method: Creates an empty binary tree (initializes root pointer to null)
BST::BST(){
    root = nullptr;
}


// Destructor Method: Uses the destructor of root Node to delete all nodes recursively
BST::~BST(){
    delete root;
}


// getRoot Method: Returns the pointer to the root of the tree
Node* BST::getRoot(){
    return root;
}


// insert Method: Adds a new node to the binary tree
// Input: A pointer to the root of the subtree where the key is to be added and an integer representing the key of the new element
void BST::insert(Node* ptr, int key){
    
    // Check if tree itself is empty
    if (root == nullptr){
        root = new Node(key);
        return;
    }
    
    // If the current ptr is nullptr, set it to root to start the insertion process
    if (ptr == nullptr){
        ptr = this->root;
    }
    
    // Check for duplicates and reject them
    if (ptr->key == key){
        cout << "Duplicate keys are not allowed." << endl;
        return;
    }
    
    // If the key is smaller, attempt to insert it to the left subtree
    else if (ptr->key > key){
        
        // If the current pointer has no left child, insert the new key here
        if (ptr->left == nullptr){
            
            // Create a new node pointer
            Node* u = new Node(key);
            
            // Update the parent-child edges
            ptr->left = u;
            u->parent = ptr;
            
            return;
        }
        
        // If the current pointer has a left child, recursively insert in the left subtree
        else return insert(ptr->left, key);
    }
    
    // If the key is larger, attempt to insert it to the right subtree
    else if (ptr->key < key){
        
        // If the current pointer has no right child, insert the new key here
        if (ptr->right == nullptr){
            
            // Create a new node pointer
            Node* u = new Node(key);
            
            // Update the parent-child edges
            ptr->right = u;
            u->parent = ptr;
            
            return;
        }
        
        // If the current pointer has a right child, recursively insert in the right subtree
        else return insert(ptr->right, key);
    }
}


// copyKey Method: A helper function that copies the key of the first node to the second node
// Input: Two pointers to two different nodes in the binary tree
void BST::copyKey(Node* ptr1, Node* ptr2){
    ptr2->key = ptr1->getKey();
}


// remove Method: Removes a node by swapping its value with the minimum of its right subtree and then deleting that minimum node
// Input: A pointer to the root of the subtree where the data is expected to be found and an integer representing the key that needs to be deleted
void BST::remove(Node* ptr, int key){
    
    // If the pointer is a nullptr, we cannot do anything
    if (ptr == nullptr) return;
    
    // Find and return the pointer to the node that needs to be deleted
    Node* old_node = find(ptr, key);
    
    // If the value did not exist in the BST, do nothing
    if (old_node == nullptr) return;
    
    // Find the minimum node of the right subtree
    Node* new_node = findMin(old_node->right);
    
    // Next child to determine the only child of the node with at least one nullptr child
    Node* child;
    
    // If the minimum value did not exist, then the node has only a left child (1-child case)
    if (new_node == nullptr) child = old_node->left;
    
    // If there was a minimum, copy its key and prepare to delete the minimum node
    else{
        copyKey(new_node, old_node);
        
        // Now we need to delete the place where the minimum previously was, which has only a right child if it does
        old_node = new_node;
        
        // Since it was a minimum, it does not have a left child; right is the only possible child
        child = old_node->right;
    }
    
    // At this point, one of old_node's children is null
    
    // If old_node was the root, update the root to be its child
    if (root == old_node){
        root = child;
        if (child != nullptr) {
            child->parent = nullptr;
        }
        
        // Detach the old node from the tree before deleting
        old_node->left = nullptr;
        old_node->right = nullptr;
        delete old_node;
        return;
    }
    
    // If both children are null, delete the node easily without dealing with child pointers
    if (child == nullptr){
        
        // If the key was less than its parent's key, it must have been the left child
        if (old_node->parent->key > old_node->key){
            old_node->parent->left = nullptr;
            
            delete old_node;
        }
        
        // Otherwise, it must have been the right child
        else{
            old_node->parent->right = nullptr;
         
            delete old_node;
        }
    }
    
    // If the node has only one child, update the pointers of the child and its parent
    else{
        
        // If the key was less than its parent's key, it must have been the left child
        if (old_node->parent->key > old_node->key){
            old_node->parent->left = child;
            child->parent = old_node->parent;
            
            // Remove the pointers from the old node
            old_node->left = nullptr;
            old_node->right = nullptr;
            delete old_node;
        }
        
        // Otherwise, it must have been the right child
        else{
            old_node->parent->right = child;
            child->parent = old_node->parent;
            
            // Remove the pointers from the old node
            old_node->left = nullptr;
            old_node->right = nullptr;
            delete old_node;

        }
    }
}



// height Method: Calculates the height of the given node recursively
// Input: A node pointer
// Output: Height of the node pointed by the node pointer (returns -1 for null nodes)
int BST::height(Node* ptr){
    
    // Height of a null pointer is -1
    if (ptr == nullptr) return -1;
    
    // Find the maximum height between its children
    int left_height = height(ptr->left);
    int right_height = height(ptr->right);
    
    // Return the greater height plus one for the current level
    if (left_height > right_height) return left_height + 1;
    else return right_height + 1;
}


// find Method: Searches for the node with the specific key in the binary tree
// Input: A node pointer specifying the root of subtree where it needs to be searched and an integer key
// Output: A pointer to the node with that key in the binary tree if found, else a null pointer
Node* BST::find(Node* ptr, int key){
    
    // If the pointer passed is a null pointer, the search has ended and the value is not found
    if (ptr == nullptr) return nullptr;
    
    
    // If the pointer points to the value equal to the key, we have found it and return the reference
    if (ptr->key == key) return ptr;
    
    // If the key is not equal, it must be either greater or smaller than the current node's key
    // If smaller, search the left subtree
    else if (ptr->key > key) return find (ptr->left, key);
    
    // If larger, search the right subtree
    else return find (ptr->right, key);
}


// findMin Method: Searches for the node with minimum key in the subtree
// Input: A node pointer specifying the root of the subtree whose minimum is to be found
// Output: A pointer to the node with the minimum key value in the subtree
Node* BST::findMin(Node* ptr){
    
    // If the pointer itself is nullptr, then there is no minimum value
    if (ptr == nullptr) return nullptr;
    
    // If its left child is null pointer, then this node is the minimum element
    else if (ptr->left == nullptr) return ptr;
    
    // If the left child is not null, recursively find minimum in the left subtree
    return findMin(ptr->left);
}


// findMax Method: Searches for the node with maximum key in the subtree
// Input: A node pointer specifying the root of the subtree whose maximum is to be found
// Output: A pointer to the node with the maximum key value in the subtree
Node* BST::findMax(Node* ptr){
    
    // If the pointer itself is nullptr, then there is no maximum value
    if (ptr == nullptr) return nullptr;
    
    // If its right child is null pointer, then this node is the maximum element
    else if (ptr->right == nullptr) return ptr;
    
    // If the right child is not null, recursively find maximum in the right subtree
    return findMax(ptr->right);
}


// printInorder Method: Prints all the elements of the binary tree in ascending order
// Performs inorder traversal (left subtree, node, right subtree) and prints each key
void BST::printInorder(Node* ptr){
    
    // If the pointer is null, return without doing anything
    if (ptr == nullptr) return;
    
    // Recursively traverse and print the left subtree
    printInorder(ptr->left);
    
    // Print the current node's key with a space separator
    cout << ptr->key << " ";
    
    // Recursively traverse and print the right subtree
    printInorder(ptr->right);
}

//Please do not add any code below this line.
//=================================================================
#endif
