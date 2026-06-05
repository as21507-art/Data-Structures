/**
 * @file lab5.cpp
 * @author Khalid Mengal
 * @description This program convert an Infix expression to PostFix and then evaluate it
 * @date 
 */
//starter_code_begins
#include<iostream>
#include<string>
#include<exception>
#include "mystack.hpp"
using namespace std;
//=============Main funciton ==============
int main()
{
	while(true)
	{
		string infix;  		//Infix expression

		//prompt the user for infix expression
		cout<<"Enter an Infix Expression: ";
		cin>>infix;


		try
		{
			//if user decides to exit the program
			if(infix=="exit") 
				break;
			
			//in case if the expression is not balanced then print an error message
			//and skip Infix to Postfix conversion and evaluation of the expression.
			else if(!isBalanced(infix)) 
			{
				cout<<"Expression is not Balanced "<<endl;
				continue;
			}

			//convert Infix expression to PostFix expression.
			string postfix = infix2postfix(infix);

			//print the Postfix expression	
			cout<<"The postfix form is: "<<postfix<<endl;

			//evaluate the Postfix expression
			float ans=evaluate(postfix);

			//print the result
			cout<<infix<<"="<<ans<<endl;
		}
		//if an exception was thrown
		catch (exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}
	}

	return EXIT_SUCCESS;
}