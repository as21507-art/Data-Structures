//============================================================================
// Name         : main.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Description  : Array Based Circular Queue Testing Program
//============================================================================
#include<iostream>
#include<iomanip> //for setw() manipulator
#include<sstream>
#include "queue.hpp"
using namespace std;

Queue<int> q1(5);
//===========================================
void display()
{
	
	cout<<"+";
	for(int i=0; i<q1.capacity; i++)
		cout<<"---+";
	cout<<endl;
	for(int i=0; i<q1.capacity; i++)
	{
		string str="|";
		if(i==q1.front)
			str+="F";
		if(q1.rear==i)
			str+="R";
		str+=" ";
		cout<<left<<setw(4)<<str;

	}
	cout<<"|";
	cout<<endl<<"+";
	for(int i=0; i<q1.capacity; i++)
		cout<<"---+";	
		cout<<endl;
	for(int i=0; i<q1.capacity; i++)
	{
		if(((q1.front<q1.rear) and (i>=q1.front and i<q1.rear)) or ((q1.front > q1.rear) and (i>=q1.front or i<q1.rear )) or q1.size==q1.capacity)
		{cout<<"|"<<setw(3)<<q1.array[i];
		}
		else
			cout<<"|   ";	
	}
	cout<<"|"<<endl<<"+";
	for(int i=0; i<q1.capacity; i++)
		cout<<"---+";	

	cout<<endl<<endl;

}
//===========================================
void help()
{
	cout<<"List of Commands:"<<endl
		<<"enqueue <elem> : Enqueue (insert) an element in the Queue."<<endl
		<<"dequeue        : Dequeue (remove) an element from the Queue."<<endl
		<<"isEmpty        : Check if the Queue is empty or not."<<endl
		<<"isFull         : Check if the Queue is Full or not."<<endl
		<<"display        : Display the Queue."<<endl
		<<"exit"<<endl;
}
//===========================================

int main()
{
	help();
	string user_input;
	string command;
	string parameter;

	while(true)
	{
		try
		{
			cout<<">";
			getline(cin,user_input);

			// parse user-input into command and parameter(s)
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,parameter);


				 if(command=="enqueue" or command=="e" or command=="en")				q1.enqueue(stoi(parameter)),display();
			else if(command=="dequeue" or command=="d" or command=="de")					q1.dequeue(),display();
			else if(command=="isEmpty" or command=="isempty" or command=="empty")	 	cout<<"Queue is "<<(q1.isEmpty()?"empty.":"not empty.")<<endl;
			else if(command=="isFull" or command=="isfull" or command=="full") 			cout<<"Queue is "<<(q1.isFull()?"full.":"not full.")<<endl;
			else if(command=="display" )												display();
			else if(command == "exit" or command=="quit")								break;
			else																		cout<<"Invalid input !!! Please try again"<<endl;
		}
		catch(exception &ex)
		{	cout<<"Exception: "<<ex.what()<<endl; }
	
	}

	return EXIT_SUCCESS;
}
