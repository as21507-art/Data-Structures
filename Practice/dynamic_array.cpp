#include <iostream>
using namespace std;

int main(){
    int i, j;
    int nRows = 5;
    int nCols = 2;

    /* Declaring a dynamic 2D array*/
    int** table;
    table = new int* [nRows];       // Create n Rows
    for(i=0;i<nRows;i++){
        table[i] = new int [nCols];
    }                               // Create n Cols

    /* Accessing each element */
    for(i=0; i<nRows;i++){
        for(j=0; j<nCols;j++){
            table[i][j] = i * j;
        }
    }

    for(i=0; i<nRows;i++){
        for(j=0; j<nCols;j++){
            cout<<table[i][j];
        }
        cout<<endl;
    }

    /* Clearing Memory Space after using */
    for (i=0; i<nRows;i++){
        delete [] table[i];
    }
    delete [] table;

    return 0;
}
