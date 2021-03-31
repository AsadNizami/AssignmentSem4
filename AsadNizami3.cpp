//#include<iostream>
#include <bits/stdc++.h>
using namespace std;

void print(int heap[], int size){
	for(int i=0; i<size; i++)
		cout << heap[i] << " ";
	cout << endl;
}

void max_heapify(int heap[], int i, int heap_size){
	int left = 2*i+1;
	int right = 2*i+2;
	int max = i;
	
	if(left<heap_size && heap[left]>heap[max])		max = left;

	if(right<heap_size && heap[right]>heap[max])	max = right;
	if(max!=i){
		swap(heap[i], heap[max]);
		max_heapify(heap, max, heap_size);
	}
}

void heap_sort(int heap[], int heap_size){
	for(int i=heap_size/2; i>=0; i--)
		max_heapify(heap, i, heap_size); 
	for (int i=0; i<heap_size-1; i++){
		swap(heap[0], heap[heap_size-i-1]);
		max_heapify(heap, 0, heap_size-i-1);
	}
	print(heap, heap_size);
}


void counting_sort(int arr[], int size, int digit, bool to_print){
	int d = pow(10, digit);
	int k=10000+10, arr_c[k], arr_b[size];
	for(int i=0; i<10; i++)	arr_c[i] = 0;
	for(int j=0; j<size; j++)	arr_c[(arr[j]/d) % 10]++;
	for(int i=1; i<k; i++)	arr_c[i] = arr_c[i]+arr_c[i-1];
	
	for(int j=size-1; j>=0; j--){
		arr_b[arr_c[(arr[j]/d)%10]-1] = arr[j];
		arr_c[(arr[j]/d)%10]--;
	}
	for(int i=0; i<size; i++)	arr[i] = arr_b[i];
	
	if(to_print)
		print(arr, size);
}

void radix_sort(int arr[], int size){
	int dig = 5;
	bool to_print = false;
	for(int i=0; i<dig; i++)
		counting_sort(arr, size, i, to_print);
	print(arr, size);
}
int menu(){
	int option;
	cout << "Menu:" << endl;
	cout << "1: Heap Sort" << endl;
	cout << "2: Counting Sort" << endl;
	cout << "3: Radix Sort" << endl;
	cin >> option;
	return option;
}

int main(){
	int size;
	cout << "Enter the number of elements" << endl;
	cin >> size;
	int arr[size];
	int max_dig = 5;
	for (int i=0; i<size; i++) cin >> arr[i];
	while (true){
		int option = menu();
		if (option==1) 	heap_sort(arr, size);
		else if(option==2) 	counting_sort(arr, size, 10000, true);
		else if(option==3)	radix_sort(arr, size);
		else	break;		
	}
}
