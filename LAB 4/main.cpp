//============================================================================
// Name         : main.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 16-03-2019
// Date Modified: 02-06-2025 
// Copyright    : All rights are reserved
// Description  : main.cpp to test Vector implmentation in C++
//============================================================================

#include<iostream>
#include<cstdlib>
#include<iomanip>
#include <stdexcept>
#include<sstream>
#include "myvector.hpp"

using namespace std;

//=======================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display                  : Display the Vector"<<endl
		<<"push_back <element>      : Add an element to the end of the vector"<<endl
		<<"insert <index element>   : Insert an element at location index"<<endl
		<<"erase <index>            : Remove the element from index"<<endl
		<<"[index]                  : Returns a reference to an element at a specified index"<<endl
		<<"at <index>               : Returns a reference to an element at a specified index"<<endl
		<<"front                    : Return the (reference of) front element"<<endl
		<<"back                     : Returns a reference to the last element of the vector"<<endl
		<<"size                     : Returns the number of elements in the vector"<<endl
		<<"capacity                 : Returns the capacity of vector"<<endl
		<<"isEmpty                  : Tests if the vector container is empty"<<endl
		<<"shrink                   : Reduce vector capacity to fit its size (shrink_to_fit)"<<endl
		<<"exit/quit                : Exit the Program"<<endl;
}
int main()
{

	MyVector<int> myVector;
	string user_input;
	string command;
	string parameter1;
	string parameter2;
	listCommands();

	do
	{
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter1,' ');
		getline(sstr,parameter2);

		try
		{
			if(command=="display" or command=="d") 							myVector.display();
			else if(command=="push_back" or command=="p" )					myVector.push_back(stoi(parameter1)),myVector.display();
			else if(command=="insert" or command=="i")		    			myVector.insert(stoi(parameter1),stoi(parameter2)),myVector.display();
			else if(command=="erase" or command=="e")		    			myVector.erase(stoi(parameter1)),myVector.display();
			else if(command=="at" or command=="a")			    			cout<<myVector.at(stoi(parameter1))<<endl;
			else if(command[0]=='[' and command[command.length()-1]==']') 	cout<<myVector[stoi(command.substr(1,command.length()-2))]<<endl;
			else if(command=="front" or command=="f")			            cout<<myVector.front()<<endl;
			else if(command=="back" or command=="b")			            cout<<myVector.back()<<endl;
			else if(command=="size" or command=="s")                        cout<<myVector.size()<<endl;
			else if(command=="capacity" or command=="c")                    cout<<myVector.capacity()<<endl;
			else if(command=="isEmpty" or command=="ie")			        cout<<boolalpha<<myVector.isEmpty()<<endl;
			else if(command=="shrink")          				            myVector.shrink_to_fit(),myVector.display();
			else if(command == "help" or command=="?")			            listCommands();
			else if(command == "exit" or command=="quit")			        break;
			else 								                            cout<<"Invalid Command !!"<<endl;
		}
		catch(const exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}