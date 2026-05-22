// C++ Program to convert the temperature from Celsius to Fahrenheit
// Author: Aashish Shrestha
// May 22, 2026
//Description: This programs prompts the user to input temperature in Celsius then converts it into Fahrenheit and displays it.
#include <iostream>

using namespace std;

int main(){
    
    // Declaring variables of float type for Fahrenheit and Celsius
    float f, c;
    
    // Taking the input from the user in Celsius
    cout<<"Enter Temperature in Celsius: ";
    cin >> c;
    
    // Converting the temperature from celsius to Fahrenheit
    f = c * 1.8 + 32;
    
    //Displaying the output temperature in Fahrenheit
    cout<<"Temperature in Fahrenheit is: "<<f<<endl;
    
    // Return 0 to indicate successful execution
    return 0;
}
