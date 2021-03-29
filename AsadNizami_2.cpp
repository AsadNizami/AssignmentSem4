#include<iostream>
#include<cstdlib>
using namespace std;

int max_vertices = 99;
const int queue_size = 100;
int queue[queue_size];
int front = -1;
int rear = -1;

struct graph{ 			//Structure for graph
	int V;
	int E;
	struct list* array;	//Points to the structure which stores the head of all vertices
};

struct list{ // Stores root of node
	struct node* head;
};

struct node{
	int data;
	struct node* link;
};

bool isEmpty(){
	if(rear == front)	return true;
	return false;
}

bool isFull(){
	if(rear == queue_size-1)	return true;
	return false;
}

void enqueue(int num){
	if(isFull()) cout << "Queue Overflow" << endl;
	else{
		rear++;
		queue[rear] = num;
	}
}

int dequeue(){
	int res = -1;
	if(isEmpty())	cout << "Queue Underflow" << endl;
	else{
		front ++;
		res = queue[front];
	}
	return res;
}

void bfs(struct graph* G){
	int visited[max_vertices], src;
	struct node* temp;
	cout << "Enter the node for bfs" << endl;
	cin >> src;
	visited[src] = 1;
	int curr = src;
	
	while(true){
		cout << curr << " ";
		temp = G->array[curr].head;

		while(temp!=NULL){

			if(visited[temp->data]!=1){
//				cout <<"\n "<< temp->data<<endl;
				visited[temp->data] = 1;
				enqueue(temp->data);
			}
			temp = temp->link;
		}
		if(isEmpty()){
			cout << "\n" << endl;
			return;
		}
		curr = dequeue();
	}
}

void init(struct graph* G){
	G->array = (struct list*)malloc(max_vertices*sizeof(struct list));
	for (int i=0; i<max_vertices; i++)
	{
		G->array[i].head = NULL;
	}
}

void addEdge(struct graph* G, int first, int second){

	struct node* temp1 = (struct node*)malloc(sizeof(struct node));
	temp1->data = second;
	temp1->link = G->array[first].head;
	G->array[first].head = temp1;

	struct node* temp2 = (struct node*)malloc(sizeof(struct node));
	temp2->data = first;
	temp2->link = G->array[second].head;
	G->array[second].head = temp2;
}

void addEdgeUtility(struct graph* G){
	int x, y;
	cout << "Enter the vertices" << endl;
	cin >> x >> y;
	addEdge(G, x, y);
}

void display(struct graph* G){
	for(int i=0; i<max_vertices; i++){
		struct node* temp = G->array[i].head;
		if(temp)
		{
			cout << "Head: " << i << ": ";	
			while(temp){
			cout << temp->data << " ";
			temp = temp->link;
			}
		cout << endl;
		}	
	}
}

void delete_node_L(struct list* list, int node_data, int del_data){
	struct node* temp = list[node_data].head;
	
	if(temp->data == del_data)
		{
			list[node_data].head = list[node_data].head->link;
			free(temp);
		}
	else{
		while(temp->link->data != del_data && temp->link!=NULL){
			temp = temp->link;
		}
		struct node* temp2 = (struct node*)malloc(sizeof(struct node));
		temp2 = temp->link->link;
		free(temp->link);
		temp->link = temp2;
	}
}

void delete_node_G(struct graph* G){
	int del_data;
	cout << "Enter the node to be deleted" << endl;
	cin >> del_data;
	struct node* temp = G->array[del_data].head;
	while(temp){
		delete_node_L(G->array, temp->data, del_data);
		temp = temp->link;
	}
	G->array[del_data].head = NULL;
}

void dfs(struct graph* G, int visited[], int vertex){
	struct node* temp = G->array[vertex].head;
	visited[vertex] = 1;
	cout << vertex << " ";
	if(temp==NULL){
		return;
	}
	else{
		while(temp!=NULL){
			if(visited[temp->data]!=1)
				dfs(G, visited, temp->data);
			temp = temp->link;
		}
	}
}

void dfs_helper(struct graph* G){
	int visited[max_vertices], src;
	cout << "Enter the node for dfs" << endl;
	cin >> src;
	dfs(G, visited, src);
	cout << "\n" << endl;
}

void search(struct graph* G){
	int data;
	cout << "Enter the node to be searched" << endl;
	cin >> data;
	if(G->array[data].head==NULL)	cout << "Not Found" << endl;
	else cout << "Found" << endl;
}

int menu(){
	int option;
	cout << "Enter:" << endl;
	cout << "1: Search a node" << endl;
	cout << "2: Insert an edge" << endl;
	cout << "3: Delete a node" << endl;
	cout << "4: Show graph" << endl;
	cout << "5: BFS" << endl;
	cout << "6: DFS" << endl;
	cin >> option;
	return option;
}

int main(){
	struct graph* G = (struct graph*)malloc(sizeof(struct graph));
	init(G);
	while(true){
		int option = menu();
		if(option == 1)		search(G);
		else if(option == 2)	addEdgeUtility(G);
		else if(option == 3)	delete_node_G(G);
		else if(option == 4)	display(G);
		else if(option == 5)	bfs(G);
		else if(option == 6) 	dfs_helper(G);
		else break;
	}
	
}
