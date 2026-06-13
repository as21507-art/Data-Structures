#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<vector>
#include "tree.hpp"
using namespace std;


//==================================================================
void help(void)
{
	cout<<"print               : Print the Tree"<<endl
	    <<"add <child-name>    : Add a new node as a child of the current node"<<endl
	    <<"remove <child-name> : Removes a given child from the current node"<<endl
	    <<"treeSize            : Print the total number of nodes in the Tree"<<endl
	    <<"height              : Print the height of the current node"<<endl
	    <<"depth               : Print the depth of the current node"<<endl
	    <<"treeHeight          : Print the height(Max-depth) of the Tree"<<endl
	    <<"isExternal          : Check if the current node is an external node or not"<<endl
	    <<"isInternal          : Check if the current node is an internal node or not"<<endl
	    <<"preorder            : Traverse/Print the Tree in pre-order"<<endl
	    <<"postorder           : Traverse/Print the Tree in post-order"<<endl
	    <<"help                : Display the list of available commands"<<endl
	    <<"exit                : Exit the Program"<<endl;
}
//==================================================================
int main()
{
	Tree tree;
	help();
	while(true)
	{
		string user_input;
		string command;
		string parameter;
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);

		try
		{
				 if(command=="add" or command=="a")		    tree.add(tree.getCurrentNode(),parameter); 	
			else if(command=="remove" or command=="r")		tree.remove(tree.getCurrentNode(),parameter);
			else if(command=="cd")							tree.cd(parameter);
			else if(command=="treeSize")						cout<<"Size of the Tree is :"<<tree.size(tree.getRoot())<<endl;
			else if(command=="depth")						cout<<"The depth of the current node("<<tree.getCurrentNode()->getName()<<") is: "<<tree.depth(tree.getCurrentNode())<<endl;
			else if(command=="height")						cout<<"The height of the current node("<<tree.getCurrentNode()->getName()<<") is: "<<tree.height(tree.getCurrentNode())<<endl;
			else if(command=="treeHeight")					cout<<"The height(max-depth) of the Tree is: "<<tree.treeHeight()<<endl;
			else if(command=="print") 	                    tree.print();		//print the tree
			else if(command=="preorder")					tree.preorder(tree.getRoot()),cout<<endl;
			else if(command=="postorder")					tree.postorder(tree.getRoot()),cout<<endl;
			else if(command=="help")                        help();
			else if(command=="exit")						break;
			else if(command=="isExternal")					cout<<"Current node("<<tree.getCurrentNode()->getName()<<") is "<<((tree.isExternal(tree.getCurrentNode())==true) ? "":"not ")<<"an external node of the tree."<<endl;
			else if(command=="isInternal")					cout<<"Current node("<<tree.getCurrentNode()->getName()<<") is "<<((tree.isInternal(tree.getCurrentNode())==true) ? "":"not ")<<"an internal node of the tree."<<endl;
			else 											cout<<command<<": command not found"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}
}