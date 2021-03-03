#include<iostream>
#include<cstdlib>
using namespace std;

struct node{
	struct node* left;
	struct node* right;
	int data;
};

struct node* insert(struct node* root, int x){
	if(root == NULL){
		struct node* new_node = (struct node*)malloc(sizeof(struct node));
		new_node->data = x;
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

struct node* create(struct node* root){
	int num, data;
	cout << "Enter the number of elements" << endl;
	cin >> num;
	cout << "Enter the elements" << endl;
	for(int i=0; i<num; i++){
		cin >> data;
		root = insert(root, data);
	}
	return root;
}

void preOrder(struct node* root){
	if(root == NULL){
		return;
	}
	cout << root->data << " ";
	preOrder(root->left);
	preOrder(root->right);
}

bool search(struct node* root, int data){
	if (root==NULL){
		return false;
	}
	else{
		if(root->data==data){
			return true;
		}
		return search(root->left, data) || search(root->right, data);
	}
}

struct node* min_node(struct node* root){
	struct node* temp = root;
	while(root && root->left){
		temp = temp->left;
	}
	return temp;
}

struct node* delete_node(struct node* root, int data){
	struct node* temp;
	if(root->data == data){
		if(root->left == NULL && root->right != NULL){
			temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL && root->left != NULL){
			temp = root->left;
			free(root);
			return temp;
		}
		else if(root->left == NULL && root->right == NULL){
			free(root);
			return NULL;
		}
		else{
			temp =  min_node(root->right);
			root->data = temp->data;
			root->right = delete_node(root->right, temp->data);
		}
	}
	else if(root->data > data){
		root->left = delete_node(root->left, data);
	}
	else if(root->data < data){
		root->right = delete_node(root->right, data);
	}
	else{
		return NULL;
	}
}

int menu(){
	int option;
	cout << "1: Create " << endl;
	cout << "2: Insert a node" << endl;
	cout << "3: Display" << endl;
	cout << "4: Search" << endl;
	cout << "5: Delete a node" << endl;
	cin >> option;
	return option;
}

int main(){
	struct node* root = NULL;
	while (true){
		int option = menu();
		if (option == 1){
			root = create(root);
		}
		else if(option == 2){
			int data;
			cin >> data;
			root = insert(root, data); 
		}
		else if(option == 3){
			preOrder(root);
			cout << endl;
		}
		else if(option == 4){
			int data;
			cout << "Enter the element to be searched";
			cin >> data;
			if (search(root, data))	cout << "Found" << endl;
			else cout << "Not found" << endl;
		}
		else if(option == 5){
			int data;
			cout << "Enter the element to be deleted";
			cin >> data;
			root = delete_node(root, data);
		}
		else break;
	}
}
