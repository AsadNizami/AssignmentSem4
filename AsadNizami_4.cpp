#include<iostream>
#include<cstdlib>
#include<fstream>
#include<bits/stdc++.h>
#include<cstring>

using namespace std;

struct node{
	struct node* left;
	struct node* right;
	char data[100];
	int total;
	int arr[100];
};

struct node* new_node(string word, int line){

	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->left = NULL;
	temp->right = NULL;
	temp->total = 1;
	strcpy(temp->data, word.c_str());
//	temp->data = word;

	for(int i=0; i<100; i++)	temp->arr[i] = -1;
	temp->arr[0] = line;
	return temp;
}

void modify(struct node* root, int line){
	root->total++;
	int i=0;
	while(root->arr[i]!=-1)
	{
		if(root->arr[i] == line)
			return;
		i++;
	}
	root->arr[i] = line;
}

struct node* insert(struct node* root, string word, int line){
	if(root==NULL){
		struct node* temp = new_node(word, line);
		return temp;
	}
	else if(root->data==word){
		modify(root, line);
		return root;
	}
	else{
		if(root->data < word){
			root->right = insert(root->right, word, line);
		}
		else{
			root->left = insert(root->left, word, line);
		}
	}

	return root;
}

struct node* constructUtil(struct node* root){
	string file, data, word;
	int line = 1;
//	struct node* temp;
	ifstream in("Question4.txt");
	
	while(getline(in, data)){
		
		stringstream iss(data);
		while(iss >> word)
			root = insert(root, word, line);
		
		line++;
	}	
	return root;
}

void preOrder(struct node* root){
	if(root == NULL)	return;
	cout << root->data << endl;
	cout << root->total << endl;
	preOrder(root->left);
	preOrder(root->right);
}

void find(struct node* root, string word){
	if(root==NULL){
		return;
	}
	else if(root->data == word){
		cout << root->data <<endl;
		cout << "Total occurence: " << root->total << endl;
		cout << "Present in line: ";
		int i=0;
		while(root->arr[i] != -1){
			cout << root->arr[i] << " "; 
			i++;
		}
		cout << endl;
	}
	else{
		if(root->data > word)
			find(root->left, word);
		else
			find(root->right, word);
	}
}

void write(struct node* root){
	if(root==NULL)return;
	ofstream new_file("new4.txt", ios_base::app);

	fflush(stdin);
	new_file<<root->data<<" ";
	write(root->left);
	write(root->right);
}
void write_util(struct node* root){
	write(root);
}

int main(){
	struct node* root = NULL;
	string word;
	root = constructUtil(root);
	write_util(root);
//	preOrder(root);
	while(true){
		cout << "Enter the word to find or -1 to exit" << endl;
		cin >> word;
		if(word=="-1")	break;
		find(root, word);
	}
}
