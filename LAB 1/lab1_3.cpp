// C Program: Checks how many prime numbers are smaller than the given number n
// Author: Aashish Shrestha
// May 22, 2026
// Description: The program prompts the user to enter a positive number. The program counts how many prime numbers are less than the given input, not inlcuding the given number.
#include <iostream>

using namespace std;

int main(){
    int N;
    bool isPrime;
    
    // Prompting the user to enter a positive number
    cout<<"Please enter a positive number: ";
    cin>>N;
    
    // Initializing a counter to number of primes less than N
    int counter = 0;

    //Iterating from 2 to N-1 to look for prime numbers
    for (int num=2; num<N; num++){
        // Determining the upper limit for the loop to check factors
        int upper_limit = sqrt(num);
        
        // Initializing the flag as prime
        isPrime = true;
        
        for(int i = 2; i <= upper_limit; i++){
            if (num % i == 0){
                // If the number has factors other than 1 and itself, it is not a prime number
                isPrime = false;
                break;
            }
        }
        if (isPrime){
            counter += 1;
        }
    }
    
    // Displaying the output
    cout<<"Number of prime numbers smaller than "<<N<<" are: "<<counter<<endl;

    // Return 0 to indicate successful execution
    return 0;
}

