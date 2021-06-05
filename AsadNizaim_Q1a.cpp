#include <iostream>
using namespace std;

struct list{
	struct node* head;
};
struct node{
	int data;
	struct node* link;
};

void init(struct list* lst, int size){
	for(int i=0; i<size; i++)
		lst[i].head = NULL; 
}	

void display_list(struct list* lst, int size){
	for(int i=0; i<size; i++){
		struct node* temp = lst[i].head;
		printf("\n%d: ", i);
		while(temp){
			cout << temp->data << "  "; 
			temp = temp->link;
		}
	}
	cout << "\n" << endl;
}

void insertion(struct list* lst, int size){
	struct node* new_temp = (struct node*)malloc(sizeof(struct node));
	cin >> new_temp->data;
	int ind = new_temp->data % size;
	struct node* temp = lst[ind].head;
	new_temp->link = temp;
	lst[ind].head = new_temp;
}

bool search(struct list* lst, int size, int element){
	cout << element << " ";
	int ind = element % size;
	struct node* temp = lst[ind].head;
	while(temp){
		if(temp->data == element)	return true;
		temp = temp->link;
	}
	return false;
}

void delete_node(struct list* lst, int size, int element){
	if(search(lst, size, element)){
		int ind = element % size;
		struct node* temp = lst[ind].head;
		struct node* new_temp;
		if(temp->data == element){
			new_temp = temp;
			lst[ind].head = temp->link;
			free(new_temp);
			return;
		}

		while(temp->link->data != element)	temp = temp->link;
		new_temp = temp->link;
		temp->link = new_temp->link;
		free(new_temp);
	}
}

int main(){
	int size;
	cin >> size;
	struct list* lst = (struct list*)malloc(size*sizeof(struct list));
	init(lst, size);
	int insert_num;
	cin >> insert_num;
	for(int i=0; i<insert_num; i++)
		insertion(lst, size);

	display_list(lst, size);

	int search_num;
	cin >> search_num;
	for(int i=0; i<search_num; i++){
		int element;
		cin >> element;
		bool ans = search(lst, size, element);
		cout << ans << endl;
	}

	int delete_num;
	cin >> delete_num;
	for(int i=0; i<delete_num; i++){
		int element;
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
// 9
