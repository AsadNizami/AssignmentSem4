#include <iostream>
#include <sstream>
using namespace std;

int main(){
	freopen("size1000.txt", "r", stdin);
	int size;
	cin >> size;
	cout << size << endl;
	int arr[size];
	for(int i=0; i<size; i++)	cin >> arr[i];
	
	for (int i=0; i<size; i++)	cout << arr[i] << " " ;
	
}

