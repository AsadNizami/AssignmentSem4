#include <fstream>
#include <bits/stdc++.h>
using namespace std;
const int size = 10000000;
static int arr[size];
static int arr_b[size];
const int dig = 5;

void print(int heap[], int size){
	int *ptr = heap;
	for(int i=0; i<size; i++)
		cout << *(ptr+i) << " ";
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
	int k=10000+10, arr_c[k];
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
	bool to_print = false;
	for(int i=0; i<dig; i++)
		counting_sort(arr, size, i, to_print);
	print(arr, size);
}

int main(){
	freopen(".\\Datasheet\\size10000000.txt", "r", stdin);
	freopen(".\\Output\\size10000000.txt", "w", stdout);

	int max_dig = 5;
	for (int i=0; i<size; i++) cin >> arr[i];
	
	int option = 3;
	if (option==1) 	heap_sort(arr, size);
	else if(option==2) 	counting_sort(arr, size, 10000, true);
	else if(option==3)	radix_sort(arr, size);
		
}
