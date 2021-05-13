#include <iostream>
using namespace std;
int const large_num = 1e3;

struct graph{
	int V;
	int E;
	struct list *array; // Pointer to the array which stores the head of every vertex
};
struct list{
	struct node_graph* head; // Pointer to the head of every vertex
};
struct node_graph{ // For creating every node 
	int vertex;
	int weight;
	struct node_graph* link;
};


void addEdge(struct graph* G, int v1, int v2, int weight){ // Adding the edges

	struct node_graph* temp = (struct node_graph*)malloc(sizeof(struct node_graph));
	temp->vertex = v2;
	temp->weight = weight;
	temp->link = G->array[v1].head;
	G->array[v1].head = temp;
	
}

void init(struct graph *G){
	int size;
	int **graph_raw;
	cin >> size;
	G->V = size;
	G->array = (struct list*)malloc(G->V*sizeof(struct list));
	for(int i=0; i< G->V; i++){
		G->array[i].head = NULL;
	}
	graph_raw = new int *[size];

	for(int i=0; i <size; i++)
   		graph_raw[i] = new int[size];

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cin >> graph_raw[i][j];
	}

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			if (graph_raw[i][j]!=0)
				addEdge(G, i, j, graph_raw[i][j]);
		}
	}
}

void display_graph(struct graph* G){
	for(int i=0; i<G->V; i++){
		struct node_graph* temp = G->array[i].head;
		printf("\n%d: ", i);
		while(temp){
			cout << temp->vertex << ":" << temp->weight << "  "; 
			temp = temp->link;
		}
	}cout << endl;
}
void display(int **graph, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cout << graph[i][j] << " ";
		cout << endl;
	}
}


void bellman_ford(struct graph *G, int size, int src){
	int min_dist[size];
	for(int i=0;i<size; ++i){
		min_dist[i] = large_num;
	}
	min_dist[src] = 0;
	bool flag = true;

	while(flag){
		flag = false;
		for(int i=0; i<size; i++){

			// cout << "I: " << i << endl;
			struct node_graph *temp = G->array[i].head;
			// cout << i << " " << temp->vertex << endl;

			while(temp){

				int new_dist = min_dist[i] + temp->weight;
				if (min_dist[i]!=large_num && min_dist[temp->vertex]>new_dist){
					min_dist[temp->vertex] = new_dist;
					flag = true;
				}
				temp = temp->link;
			}
		}
	}
	for(int i=0; i < size; i++){
		cout << i << " " << min_dist[i] << endl;
	}

}

int main(){
	struct graph *G = (struct graph*)malloc(sizeof(struct graph));
	init(G);
	int src;
	cin >> src;
	// display_graph(G);
	bellman_ford(G, G->V, src);
}

// Sample test case
// 5
// 0 -1 4 0 0
// 0  0 3 2 2 
// 0  0 0 0 0 
// 0  1 5 0 0
// 0  0 0 -3 0
// 0