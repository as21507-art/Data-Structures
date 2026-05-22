// C Program: Check if a positive integer is prime or not
// Author: Aashish Shrestha
// May 22, 2026
// Description: The program prompts the user to enter a positive number. The progrqm validates if the number is positive and then prints prime number is the number is prime otherwise it prints that it is not prime.

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int user_input, i;
    
    // Initializing the flag for a prime number
    bool is_prime = true;
    
    // Prompt message and take input number from the user
    cout<<"Please enter a positive number: ";
    cin>>user_input;
    
    // Checking if the number is 1 and returning that it is not prime
    if (user_input == 1){
        cout<<user_input<<" is not a prime number."<<endl;
        is_prime = false;
    }
    
    // Finding the upper limit of the loop using square root
    int u_limit = sqrt(user_input);
    
    // Iterates over all smaller number to check for the factor
    for (i=2; i<=u_limit; i++){
        if (user_input % i == 0){
            // A number with factors other than 1 and itself is not prime
            cout<<user_input<<" is not a prime number."<<endl;
            // Setting the flag to false to record that it was not a prime
            is_prime = false;
            // Exiting the loop after finding at least one non trivial factor which is sufficient to conclude it was not prime
            break;
        }
    }
    
    // Checking the flag to see if the number was prime
    if (is_prime){
        cout<<user_input<<" is a prime number."<<endl;
    }
    
    // Return 0 to indicate successful execution
    return 0;
}
