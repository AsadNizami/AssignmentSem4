#include <iostream>
#include <sstream>
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
	if (left<heap_size && heap[left]>heap[max])	max = left;

	if(right<heap_size && heap[right]>heap[max])	max = right;

	if(max!=i){
		swap(heap[i], heap[max]);
		max_heapify(heap, max, heap_size);
	}
}

void max_heapify_insert(int heap[], int i, int heap_size){
	int parent = (i-1)/2;

	int largest = i;
	if(heap[parent]<heap[i]){
		swap(heap[parent], heap[i]);
		max_heapify_insert(heap, parent, heap_size);
	}
}

void max_heap_insert(int heap[], int heap_size){
	for(int i=0; i<heap_size; i++){
		max_heapify_insert(heap, i, i+1);
	}
}

void build_max_heap(int heap[], int heap_size){
	for(int i=heap_size/2; i>=0; i--)
		max_heapify(heap, i, heap_size); 
}
 
int main(){
	int size;
	cout << "Enter the size of array" << endl;
	cin >> size;
	int heap[size], heap1[size];
	cout << "Enter the element" << endl;
	for(int i=0; i<size; i++){
		cin >> heap[i];
		heap1[i] = heap[i];		
	}

	build_max_heap(heap, size);
	cout << "Build max heap :" << endl;
	print(heap, size);
	max_heap_insert(heap1, size);
	cout << "Insert in max heap :" << endl;
	print(heap1, size);
}
