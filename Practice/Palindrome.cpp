#include <iostream>
#include <string>
using namespace std;

int main(){
    string user_word;
    int counter, len;
    bool flag = true;
    cout<<"Enter a word";
    cin>>user_word;   
    
    len = user_word.length();
    counter = 0;

    while (counter < len){
        if (user_word[counter] != user_word[len - counter - 1]){
            cout<<endl<<"Not palindrome";
            flag = false;
            break;
        }
        counter += 1;
    }
    if (flag){
        cout<<endl<<"Palindrome";
    }
    return 0;
}