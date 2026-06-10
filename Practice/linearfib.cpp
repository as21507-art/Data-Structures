#include<iostream>
#include<string>

using namespace std;

int FibLinear(int n, int a, int b){
    if (n <= 0){
        return a;
    }
    else{
        return FibLinear(n - 1, b, a+b);
    }
}


int main(){
    for (int i=0; i<10; i++){
        cout<<FibLinear(i, 0, 1)<<endl;
    }
    return 0;
}
