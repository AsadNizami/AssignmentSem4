#include<iostream>
#include<cstdlib>
using namespace std;

int max_vertices = 99;
struct graph{ 			//Structure for graph
	int V;
	int E;
	struct list* array;	//Points to the structure which stores the head of all vertices
};

struct list{
	struct node* head;
};

struct node{
	int data;
	struct node* link;
};

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

int main(){
	struct graph* G = (struct graph*)malloc(sizeof(struct graph));
	init(G);
	addEdge(G,1, 2);
	addEdge(G,2, 3);
	addEdge(G, 1, 3);
	display(G);
	
	
}