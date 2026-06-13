#include <iostream>
#include <string>
using namespace std;

int main(){
    string user_word;
    int counter, len;
    bool flag = true;
    cout<<"Enter a word: ";
    cin>>user_word;   
    
    len = user_word.length();
    counter = 0;

    while (counter < len){
        if (user_word[counter] != user_word[len - counter - 1]){
            cerr<<endl<<"Not palindrome" << endl;
            flag = false;
            break;
        }
        counter += 1;
    }
    if (flag){
        cerr<<endl<<"Palindrome" << endl;
    }
    return 0;
}
