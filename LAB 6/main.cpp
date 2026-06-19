/**
 * @author Khalid Mengal
 * @description AVL Tree implementation in C++
 * @date 2022-11-03
 */
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include "avl.hpp"
//==========================================================
void listCommands()
{
			
	cout<<"________________________________________________________"<<endl;
	cout<<"display            :Display the AVL Tree"<<endl
		<<"height             :Find the height of the Tree"<<endl
		<<"min                :Find the node with minimum key in AVL"<<endl
		<<"max                :Find the node with maximum key in AVL"<<endl
		<<"find <key>         :Find a node with a given key in AVL"<<endl
		<<"insert <key>       :Insert a new node in AVL"<<endl
		<<"remove <key>       :Remove the node from AVL "<<endl
		<<"inorder            :Print the AVL in Inorder"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( AVL &myAVL)
{
	myAVL.insert(myAVL.getRoot(),12);
	myAVL.insert(myAVL.getRoot(),15);
	myAVL.insert(myAVL.getRoot(),10);
	myAVL.insert(myAVL.getRoot(),5);
	myAVL.insert(myAVL.getRoot(),4);
	myAVL.insert(myAVL.getRoot(),7);
	myAVL.insert(myAVL.getRoot(),13);
	myAVL.display();
}
//==========================================================
int main(void)
{
	AVL myAVL;
	listCommands();


	while(true)
	{
		string user_input="";
		string command="";
		string key="";
		try
		{
			cout<<">";
			getline(cin,user_input);

			// parse user input into command and parameter(s)
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,key);
			
			Node* root = myAVL.getRoot();	//get the root of the tree
			if( user_input =="display")	myAVL.display();
			else if( command =="height")	cout<<"Height = "<<myAVL.height(root)<<endl;
			else if( command =="min")	
			{
				Node* min = myAVL.findMin(root);
				cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
			}
			else if( command =="max")	
			{
				Node* max = myAVL.findMax(root);
				cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
			}
			else if( command =="find" or command =="f")	
			{
				Node *node = myAVL.find(root,stoi(key));
				if(node==nullptr)
					cout<<key<<" not found"<<endl;
				else
					cout<<"("<<key<<")"<<endl;
			}
			else if( command =="insert" or command=="i")	{ myAVL.insert(root, stoi(key)); myAVL.display();} 
			else if( command =="remove" or command=="r")	{ myAVL.remove(root,stoi(key)); myAVL.display();}
			else if( command =="inorder")	{myAVL.printInorder(root); cout<<endl;}
			else if( command == "demo") demo(myAVL); 
			else if( command == "help") listCommands();
			else if( command =="exit" or command =="quit" or command =="q") { break;}

			else cout<<"Invalid command !!!"<<endl;
		}
		catch(exception &ex)
		{
			cout<<ex.what()<<endl;
		}

	}
	return 0;
}
