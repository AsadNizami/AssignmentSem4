#include<iostream>
#include<cstdlib>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

struct node{
	struct node* left;
	struct node* right;
	int data;
};

struct node* new_node(){
	struct node* root = (struct node*)malloc(sizeof(struct node));
	root->left = NULL;
	root->right = NULL;
	return root;	
}

struct node* construct(int arr[]){
//	cout <<"Hi";
	if(arr[0] == -1){
//		cout<< "Returning";
		return NULL;
	}
	int left[100], right[100], l=0, r=0, k=1;
	for (int j=0; j<100; j++)	left[j] = -1;
	for (int j=0; j<100; j++)	right[j] = -1;
	
	struct node* temp = new_node();
	temp->data = arr[0];
	
	while(arr[k]!=-1){
		if(arr[k] < temp->data){
			left[l] = arr[k];
			l++;
		}
		else{
			right[r] = arr[k];
			r++;
		}
		k++;
	}
	
	temp->left = construct(left);
	temp->right = construct(right);
	return temp;
}

struct node* construct_util(){
	string str;
	int num, arr[100];
	
	for (int i=0; i<100; i++)	arr[i] = -1;
	
	ifstream inf("sample.txt");
	getline(inf, str);	stringstream iss(str);
	
	int i=0;
	while(iss>>num){
		arr[i] = num;	
		i++;
	}
//	for(int i=0 ;i<15; i++)	cout << arr[i] <<" ";
	struct node* root = construct(arr);
	return root;
}

int menu(){
	int option;
	cout << "1: Read from a file" << endl;
	cout << "2: Write to a file" << endl;
	cout << "3: Display" << endl;
//	cout << "4: Reset" << endl;

	cin >> option;
	return option;
}
void write(){
	string file_name, data;
	ofstream new_file("new.txt");
	cout << "Input the preorder traversal of a tree\n";
	fflush(stdin);
	getline(cin, data);
	new_file << data;
	cout << "Written to a file" << endl;
	new_file.close();
}

void preOrder(struct node* root){
	if(root == NULL || root->data == -1){
		return;
	}
	cout << root->data << " ";
	preOrder(root->left);
	preOrder(root->right);
}

int main(){
	struct node* root = NULL;
	while(true){
		int option = menu();
		if (option == 1)	root = construct_util();
		else if(option == 2)	write();
		else if(option == 3)	{preOrder(root); cout << endl;}
//		else if(option == 4)	{free(root); root=NULL;}
		else break;
	}
}

