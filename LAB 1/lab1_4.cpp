#include <iostream>
#include <cstdlib>

using namespace std;


//Function that takes an array input and finds the maximum and minimum values
//Input: an array of integers
//Output: None, only prints max and min values
void findMinMax(int this_arr[], int this_arr_size){
    // Initializing the Max and Min variables
    int max = this_arr[0];
    int min = this_arr[0];

    // Iterating over the array and comparing the values
    for (int j=1; j<this_arr_size; j++){
        if (max < this_arr[j]) max = this_arr[j];
        if (min > this_arr[j]) min = this_arr[j];
    }
    
    // Displaying the extreme values of the array
    cout<<"min: "<<min<<endl;
    cout<<"max: "<<max<<endl;
}


int main(){
    // Declaring a variable to define array size
    int arr_size = 0;
    
    // Prompting the user to enter the array size
    cout<<"Enter Size of the Array: ";
    cin>>arr_size;
    
    // Dynamically allocating space for an array
    int* my_arr = new int[arr_size];
    
    // Accessing each array index and storing data
    for (int i=0; i<arr_size; i++){
        my_arr[i] = rand() % 101;
        cout<<"array["<<i<<"]="<<my_arr[i]<<endl;
    }
    
    // Calling the function to find max or min values
    findMinMax(my_arr, arr_size);
    
    // Deallocating the memory space for the array
    delete [] my_arr;
    
    // return 0 to indicate successful execution
    return 0;
}
