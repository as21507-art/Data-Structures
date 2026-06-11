#include<iostream>

using namespace std;

int BinarySearch(int arr[], int val, int low, int up, int& calls){
    calls += 1;
    if (low > up) return -1;
    int mid = (low + up) / 2;
    if (arr[mid] == val) return mid;
    else if (arr[mid] < val) return BinarySearch(arr, val, mid + 1, up, calls);
    else return BinarySearch(arr, val, low, mid - 1, calls);
}

int main() {
    int c, total;
    int low = 0;
    int up = 9;
    int Myarray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    total = 0;
    for (int i=1; i < 10; i++){
        c = 0;
        BinarySearch(Myarray, i, low, up, c);
        cout << c <<endl;
        total += c;
    }
    
    cout <<"Total is" << total <<endl;
    return 0;
}
