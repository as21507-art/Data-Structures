//============================================================================
// Name         : main.cpp
// Author       : Khalid Mengal
// Date Created : 
// Date Modified: 
// Description  : HashTable Implementation using C++
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include "hashtable.hpp"

using namespace std;

//======================================================
int main(void)
{
	string inputfile="zipcodes.csv";
	ifstream fin;
	fin.open(inputfile);
	if(!fin){
		cout<<"Can not open "<<inputfile<<" !"<<endl;
		exit(-1);
	}
	
	string line;
	HashTable myHashTable(28859);// Prime number 30% bigger than >25844 (19880*1.3);
	getline(fin,line);  //skip first line
	while(!fin.eof())
	{
		string key, value;
		getline(fin,key,',');
		getline(fin,value);
		//cout<<key<<":"<<value<<endl;
		std::cout.setstate(std::ios_base::failbit); //don't print any thing on terminal until the failbit is cleared again.
		myHashTable.insert(key,value);
		std::cout.clear();							//clear the failbit
	}
	fin.close();
	cout<<"==================================================="<<endl;
	cout<<"Hash Table size = "<<myHashTable.getSize()<<endl;
	cout<<"Total Number of Collisions = "<<myHashTable.getCollisions()<<endl;
	cout<<"Avg. # collisions/entry = "<<setprecision(2)<<float(myHashTable.getCollisions())/myHashTable.getSize()<<endl;	
	cout<<"==================================================="<<endl;

	string user_input, command, argument1, argument2;

	while(true)
	{
	
		cout<<">";
		getline(cin,user_input);

		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,argument1,',');
		getline(sstr,argument2);

		if(command == "get")      
		{
			string result = myHashTable.get(argument1);
			if      (result == "Record not found!")      cout<<result<<endl;
			else    cout<<"Zip code for "<<argument1<<" is: "<<result<<endl;
		}
		else if(command == "insert")   myHashTable.insert(argument1,argument2);
		else if(command == "remove")   myHashTable.remove(argument1);
		else if(command == "help")	   cout<<"Available Commands:\ninsert <key,value>\nremove <key>\nget <key>"<<endl;
		else if(command == "exit")	   break;
		else cout<<"Invalid command !!!"<<endl;
	}
	return 0;
}