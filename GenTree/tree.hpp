#ifndef TREE_HPP
#define TREE_HPP
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<vector>
using namespace std;

class Node
{
	private:
		string name;				//name of the Node
		vector<Node*> children;		//Children of Node
		Node* parent; 				//link to the parent 

	public:
		Node(string name, Node* parent = nullptr) : name(name), parent(parent)
		{ }
		string getName()
		{
			return this->name;
		}
    ~Node() {};
		friend class Tree;
};
//==========================================================
class Tree
{
	private:
		Node *root;				//root of the Tree
		Node *curr_Node;		//current Node
		
	public:	
		//Methods that are part of the starter-code	
		Tree();	
		~Tree();
		Node* getRoot();
		Node* getCurrentNode();
		void cd(string name);
		void print();			//Print entire tree
	private:	//Helper methods
		void print_helper(string padding, string pointer,Node *node);
		bool isLastChild(Node *ptr);
	public:
		//Required Methods
		void add(Node* parent,string child_name);
    void remove(Node* parent,string child_name){};
		bool isExternal(Node* node);
		bool isInternal(Node* node);
		int size(Node* node);
    int depth(Node* node) {return 0;};
    int height(Node *node) {return 0;};
    int treeHeight() {return 0;};
    void preorder(Node *node){};
    void postorder(Node *node){};
	public:
		/* Required for Autograder — Do not remove or implement */
		void display2(stringstream&, Node*);
};
//========================================================================
Tree::Tree()
{
	this->root = new Node("root");
	this->curr_Node = this->root;
}
Tree::~Tree()
{
	delete this->root;
}
//========================================================================
Node* Tree::getRoot()
{
	return root;
}
//========================================================================
Node* Tree::getCurrentNode()
{
	return curr_Node;
}
//========================================================================
void Tree::cd(string name)
{
	if(name=="..")
	{
		if(curr_Node!=root)	curr_Node = curr_Node->parent;
	}
	else
	{
		for(int i=0; i<curr_Node->children.size(); i++)
			if(name == curr_Node->children[i]->name)
			{
				curr_Node = curr_Node->children[i];						//update current working directory
				return;
			}

		cout<<name<<": child not found"<<endl;
	}
}
//==========================================================================
void Tree::print()
{
	print_helper("","",root);
}
//==========================================================================
void Tree::print_helper(string padding, string pointer,Node *node)
{
    if (node != nullptr) 
    {
        if(node == curr_Node)	//print current Node in blue color
        	cout <<padding<<pointer<<"\x1B[33m"<<node->name<<"\x1B[0m"<<endl;
        else 
        	cout <<padding<<pointer<<node->name<<endl;

		if(node!=root)	padding+=(isLastChild(node)) ? "   " : "│  ";


        for(int i=0; i<node->children.size(); i++)
		{
			string marker = isLastChild(node->children[i]) ? "└──" : "├──";
			print_helper(padding,marker, node->children[i]);

		}
    }
}
//==========================================================================
bool Tree::isLastChild(Node *ptr)
{
	if(ptr!=root and ptr == ptr->parent->children[ptr->parent->children.size()-1])
		return true;
	return false;
}
//==========================================================================
// Implement/define required methods below this line


// isExternal Method: Takes a node and returns true if it has no children
bool Tree::isExternal(Node* node){
    return node->children.size() == 0;
}


// isInternal Method: Takes a node and returns true if it has at lease one child
bool Tree::isInternal(Node* node){
    return node->children.size() != 0;
}


// size Method: returns the number of nodes in the tree
// Input: A node representing a null pointers
int Tree::size(Node* node){
    if (node == nullptr) return 0;
    
    int count = 1;
    for(int i = 0; i < node->children.size(); i++) count += size(node->children[i]);
    return count;
}


// add Method: Adds a new node to the tree based on the given parent pointer
// Input: A node pointer to the parent of the new node and a string containing the value of child's element
// Ouput: Void
void Tree::add(Node* parent, string child_name){
    
    // Checking if the duplicate entry already exists
    for(int i = 0; i < parent->children.size(); i++){
        if (child_name == parent->children.at(i)->name){
            cout << "The node with same name already exists." << endl;
            return;
        }
    }
    
    // Defining and intializing a new node
    Node* newChild= new Node(child_name, parent);
    
    // Adding the new node as a child of the parent
    parent->children.push_back(newChild);
}


//Do not write any code below this line
//==========================================================================
#endif
