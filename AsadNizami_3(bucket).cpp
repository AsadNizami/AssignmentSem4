#include <iostream>
#include <stdlib.h>
using namespace std;

struct list{
	struct node* head;
};
struct node{
	float data;
	struct node* link;	
};

void print(struct list* arr_head){
	struct node* temp;
	for(int i=0; i<10; i++){
		temp = arr_head[i].head;
//		cout << "bucket " << i << " : ";
		while(temp!=NULL){
			cout << temp->data << " ";
			temp = temp->link;
		}
//		cout << endl;
	}
	cout << endl;
}

void bucket_sort(float arr[], int size){
	struct node* temp2;
	struct node* temp;
	struct list* arr_head = (struct list*)malloc(10*sizeof(struct list));
	for(int i=0; i<10; i++)	arr_head[i].head = NULL; 

	for (int i=0; i<size; i++){
		struct node* new_node = (struct node*)malloc(sizeof(struct node)); 
		int index = arr[i]*10;
		temp = arr_head[index].head;
		new_node->data = arr[i];
//		print(arr_head);
		if(temp==NULL){ //inserting in the beginnig
			arr_head[index].head = new_node;
			new_node->link = NULL;
		}
		else if(new_node->data<temp->data){
			arr_head[index].head = new_node;
			new_node->link = temp;
		}
		else{
			while(temp->link!=NULL){
//				cout << new_node->data << " " << temp->data << endl;
				if(temp->link==NULL ||new_node->data<temp->data)	break;
				temp = temp->link;
			}
			if(temp->link!=NULL){ // insertion somewhere in the middle
				temp2 = temp->link;
				temp->link = new_node;
				new_node->link = temp2;
			}
			else{ //insertion at the end 
				temp->link = new_node;
				new_node->link = NULL;
			}
		}
	}
	print(arr_head);
}

int main(){
//	float arr[] = { 0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434 };
//	int size = 6;
	int size;
	cout << "Enter the size of the array" << endl;
	cin >> size;
	float arr[size];
	for(int i=0; i<size; i++) cin >> arr[i];
	bucket_sort(arr, size);
}
