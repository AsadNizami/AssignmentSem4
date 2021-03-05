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

struct node* insert(struct node* root, int x){
	if(root == NULL){
		struct node* new_node = (struct node*)malloc(sizeof(struct node));
		new_node->data = x;//error
		new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}

	else{
		if(x > root->data){
			root->right = insert(root->right, x);
		}
		else{
			root->left = insert(root->left, x);
		}
		return root;
	}
}


void preOrder(struct node* root){
	if(root == NULL){
		return;
	}
	cout << root->data << " ";
	preOrder(root->left);
	preOrder(root->right);
}

struct node* readUtility(struct node* root){
	string file, line, raw_word;
	int word=0;
//	cout << "Enter the name of the file";
//	cin >> file;
	ifstream in("sample.txt");
	while(getline(in, line, ' ')){
			stringstream iss(line);
			while(iss >> word)
				root = insert(root, word);
		}
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
//	cout << "Input the name of the file" << endl;
//	cin >> file_name;
	ofstream new_file("new.txt");
	cout << "Input the preorder traversal of a tree\n";
	fflush(stdin);
	getline(cin, data);
//	stringstream new_data(raw_data);
//	new_data >> data;
	new_file << data;
	cout << "Written to a file" << endl;
	new_file.close();
}

int main(){
	struct node* root = NULL;
	while(true){
		int option = menu();
		if (option == 1)	root = readUtility(root);
		else if(option == 2)	write();
		else if(option == 3)	{preOrder(root); cout << endl;}
//		else if(option == 4)	{free(root); root=NULL;}
		else break;
	}
}
