#include <iostream>
using namespace std;
int const large_num = 1e2;
int const max_size = 100;
int stack[max_size];
int top = -1;

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

void push(int data){
	stack[++top] = data;
}
int pop(){
	return stack[top--];
}
void display_stack(){
	for(int i=0; i<=top; i++)
		cout << stack[i] << " ";
	cout << endl;
}
void dfs(struct graph* G, int vertex, int *visited, int size){
	visited[vertex] = 1;
	bool flag = true;
	// cout << vertex << endl;
	
	struct node_graph* temp = G->array[vertex].head;
	while(temp){
		if(visited[temp->vertex]==0){
			dfs(G, temp->vertex, visited, size);
		}
		temp = temp->link;
	}

	push(vertex);
}

void dfs_helper(struct graph* G, int size){
	int *visited = new int[size];
	for(int i=0; i<size; i++)	visited[i] = 0;
	for(int i=0; i<size; i++){
		if(visited[i]==0){
			dfs(G, i, visited, size);
		}
	}
	
	// cout << "\n" << endl;
	// display_stack();
}

void display(int **graph, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cout << graph[i][j] << " ";
		cout << endl;
	}
}
void dag(struct graph* G, int size, int src){
	int min_dist[size];
	for(int i=0; i<size; i++)	min_dist[i] = large_num;
	min_dist[src] = 0;

	for(int j=0; j<size; j++){
		int curr = pop();
		struct node_graph* temp = G->array[curr].head;
		while(temp){
			int new_dist = min_dist[curr] + temp->weight;
			if(min_dist[temp->vertex]>new_dist && min_dist[curr]!=large_num){
				min_dist[temp->vertex] = new_dist;
			}
			temp = temp->link;
		}

	}
	for(int i=0; i < size; i++){
		cout << i << " " << min_dist[i] << endl;
	}
}

int main(){
	int size, src;
	struct graph *G = (struct graph*)malloc(sizeof(struct graph));
	init(G);
	cin >> src;
	// display_graph(G);
	dfs_helper(G, G->V);
	dag(G, G->V, src);
}

// Sample test case
// 6
// 0 0 7 4 0 0
// 3 0 0 0 -1 0
// 0 0 0 5 0 1
// 0 0 0 0 0 -2
// 2 0 6 0 0 0
// 0 0 0 0 0 0
// 1