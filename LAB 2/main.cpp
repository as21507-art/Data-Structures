/**
 * @file main.cpp
 * @author Khalid Mengal
 * @description Doubly LinkedList implementation in C++
 * @date 
 */
//startercode_begins
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include "dlinkedlist.hpp"
using namespace std;

//===================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Doubly Linked List"<<endl
		<<"front              : Display the first element of the List"<<endl
		<<"back               : Display the last element of the List"<<endl
		<<"addFront <elem>    : Add a new Node at the beginning of the List"<<endl
		<<"addBack  <elem>    : Add a new Node at the end of the List"<<endl
		<<"removeFront        : Remove the first Node of the Linked List"<<endl
		<<"removeBack         : Remove the last Node of the Linked List"<<endl	
		<<"isEmpty            : Check if the List is empty?"<<endl
		<<"reverse            : Reverse the Linked List"<<endl
		<<"isPalindrome       : Check if the List is Palindrome or not?"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//===================================
int main()
{
	DLinkedList myList;
	listCommands();
	string user_input;
	string command;
	string parameter;


	do
	{
		cout<<">";
		getline(cin,user_input);

		// parse user-input into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);

		try
		{
			if(command=="display" or command=="d") 				myList.display();
			else if(command=="front" or command=="f")			cout<<"Front = "<<myList.front()<<endl;
			else if(command=="back" or command=="b")			cout<<"Back = "<<myList.back()<<endl;
			else if(command=="addFront" or command=="af")		myList.addFront(parameter),myList.display();
			else if(command=="addBack"	or command=="ab")		myList.addBack(parameter),myList.display();
			else if(command=="removeFront" or command=="rf")	myList.removeFront(),myList.display();
			else if(command=="removeBack" or command=="rb")		myList.removeBack(),myList.display();
			else if(command=="isEmpty"	or command=="ise")		cout<<"List is "<<(myList.isEmpty()? "Empty":"Not Empty")<<endl;
			else if(command=="reverse"	or command=="r")		myList.reverseList(),myList.display();
			else if(command=="isPalindrome" or command=="isp")	cout<<"List is "<<(myList.isPalindrome()? "Palindrome":"Not Palindrome")<<endl;
			else if(command == "help" or command=="h")			listCommands();
			else if(command == "exit" or command=="e")			break;
			else 												cout<<"Invalid Commad !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}
