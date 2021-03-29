#include <iostream>
#include <sstream>
using namespace std;

void print(int heap[], int size){
	for(int i=0; i<11; i++)
		cout << heap[i] << " ";
	cout << endl;
}

void max_heapify(int heap[], int i, int heap_size){
	int left = 2*i+1;
	int right = 2*i+2;

	int largest = i;
	if (left<heap_size && heap[left]>heap[i])	largest = left;

	if(right<heap_size && heap[right]>heap[largest])	largest = right;

	if(largest!=i){
		swap(heap[i], heap[largest]);
		max_heapify(heap, largest, heap_size);
	}
}

void build_max_heap(int heap[], int heap_size){
	for(int i=heap_size/2; i>=0; i--)
		max_heapify(heap, i, heap_size); 
} 

int main(){
	int size=5, temp;
	cout << "Enter the size of array" << endl;
	cin >> size;
	int heap[size];
	cout << "Enter the element" << endl;
	for(int i=0; i<size; i++)
		cin >> heap[i];

	build_max_heap(heap, size);
	print(heap, size);
}
