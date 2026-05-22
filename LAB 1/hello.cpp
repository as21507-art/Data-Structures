#include <iostream>

using namespace std;
// Not a good practice, using namespace std::cin; using namespace std::cout; are better practices.

int main(){
    cout<<"Hello World"<<endl;
    //cout,operator<<("Hello world")
    // Inserts something to the standard output screen
    // cout is an object of ostream and operator<< is a method defined by overloading
    
    // Difference between endl and \n
    // \n adds \r\f, newline and begining of the next line
    // endl does \n and flushes the buffer stream
    return 0;
}
