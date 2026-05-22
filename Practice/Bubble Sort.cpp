#include <iostream>
#include <string>
 using namespace std;

 int main(){
 	int i, j, p, n;
 	int x[] = {4, 2, 7, 3, 8, 5, 9, 1, 6};
 	n = sizeof(x) / sizeof(x[0]);

 	for (i=0; i < n; i++) 
 		cout<<x[i]<<" ";
 	cout<<endl;

 	for(i=0; i < n; i++){
 		for (j=0; j<(n-i-1); j++){
 			if (x[j] > x[j+1]){
 				p = x[j];
 				x[j] = x[j+1];
 				x[j+1] = p;
 			}
 		}
 	}
 	
 	for (i=0; i < n; i++) 
 		cout<<x[i]<<" ";
 	cout<<endl;

 	return 0;
 }