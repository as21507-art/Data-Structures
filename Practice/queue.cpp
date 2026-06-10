#include<iostream>

using namespace std;


class Queue{
public:
    int num = 0;
    int front;
    int back;
    int* array;
    Queue(){
        array = new int [4];
        front = 0;
        back = 0;
    }
    ~Queue(){
        delete [] array;
    }
    void Enqueue(int x){
        if (num < 4) {
            array[back] = x;
            back = (back + 1) % 4;
            num += 1;
        }
    }
    int Dequeue(){
        if (num > 0){
            int temp = array[front];
            front = (front + 1) % 4;
            num -= 1;
            return temp;
        }
        return - 99;
    }
    
    void display(){
        int ptr = front;
        for (int i = 0; i < num; i++){
            cout << array[ptr];
            ptr = (ptr + 1) % 4;
        }
        cout << endl;
    }
};

int main(){
    Queue Q1;
    Queue Q2;
    
    for (int i=1; i<5; i++){
        Q1.Enqueue(i);
    }
    
    cout << "Before" << endl;
    Q1.display();
    Q2.display();
    
    Q1.Enqueue(Q1.Dequeue());
    Q1.Enqueue(Q1.Dequeue());
    Q1.Enqueue(Q1.Dequeue());
    Q2.Enqueue(Q1.Dequeue());
    
    Q1.Enqueue(Q1.Dequeue());
    Q1.Enqueue(Q1.Dequeue());
    Q2.Enqueue(Q1.Dequeue());
    
    Q1.Enqueue(Q1.Dequeue());
    Q2.Enqueue(Q1.Dequeue());
    
    Q2.Enqueue(Q1.Dequeue());
    
    
    cout << "After" << endl;
    Q1.display();
    Q2.display();
    
    return 0;
}
