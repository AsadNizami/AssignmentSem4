#include <iostream>
using namespace std;

void init(int* lst, int size){
	for(int i=0; i<size; i++)
		lst[i] = -1; 
}	

void display_list(int* lst, int size){
	for(int i=0; i<size; i++)
		cout << i << ": " << lst[i] << endl;
	cout << endl;
}

void insertion(int* lst, int size, int element){
	int ind = element % size;
	for(int i=0; i<size; i++){
		if(lst[ind] == -1){
			lst[ind] = element;
			return;
		}
		ind += 1;
	}
	cout << "No space to insert" << endl;
}

bool search(int* lst, int size, int element){
	cout << element << " ";
	for(int i=0; i<size; i++){
		if(lst[i] == element)	return true;
	}
	return false;
}

void delete_node(int* lst, int size, int element){
	for(int i=0; i<size; i++){
		if(lst[i] == element){
			lst[i] = -1;
			return;
		}
	}
}

int main(){
	int size, element;
	cin >> size;
	int* lst = new int[size];
	init(lst, size);
	int insert_num;
	cin >> insert_num;
	for(int i=0; i<insert_num; i++){
		cin >> element;
		insertion(lst, size, element);
	}

	display_list(lst, size);

	int search_num;
	cin >> search_num;
	for(int i=0; i<search_num; i++){
		cin >> element;
		bool ans = search(lst, size, element);
		cout << ans << endl;
	}

	int delete_num;
	cin >> delete_num;
	for(int i=0; i<delete_num; i++){
		cin >> element;
		delete_node(lst, size, element);
	}
	display_list(lst, size);
}

// Sample test case
// 5  # size of hash table

// 10  # number of element to be inserted
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 10

// 3  # number of element to be searched
// 4
// 9
// 0 

// 2  # number of element to be deleted
// 4
// 1
