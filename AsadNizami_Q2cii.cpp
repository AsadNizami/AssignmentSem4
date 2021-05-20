#include <iostream>
using namespace std;

int priority = 0, max_size = 100;
int top = 0;

struct node{
	int vertex;
	int min_dist;
	int parent;
};

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
void display(int **graph, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cout << graph[i][j] << " ";
		cout << endl;
	}
}
void init(struct graph *G, int size, bool add){
	int **graph_raw;
	G->V = size;

	G->array = (struct list*)malloc(G->V*sizeof(struct list));
	for(int i=0; i< G->V; i++){
		G->array[i].head = NULL;
	}
	graph_raw = new int *[size];

	for(int i=0; i <size; i++)
   		graph_raw[i] = new int[size];
   	if (!add)	return;
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

bool isEmpty(){
	if (top==0)	return true;
	return false;
}
bool isFull(){
	if(top==max_size)	return true;
	return false;
}

void min_heapify_insert(struct node stk[], int index){
	int parent = (index-1)/2;

	if(stk[parent].min_dist > stk[index].min_dist){
		swap(stk[parent], stk[index]);
		min_heapify_insert(stk, parent);
	}
}

void min_heapify_delete(struct node stk[], int index){
	int left = 2*index+1;
	int right = 2*index+2;
	struct node left_child = stk[left];
	struct node right_child = stk[right];
	int min = index;
	
	if(left<=top && left_child.min_dist < stk[min].min_dist)	min = left;
	if(right<=top && right_child.min_dist < stk[min].min_dist)	min = right;
	
	if(stk[min].min_dist != stk[index].min_dist){
		swap(stk[min], stk[index]);
		min_heapify_delete(stk, min);
	}
}

void push(struct node stk[], struct node st){
	if (isFull()){
		cout << "Stack Overflow\n" << endl;
		return;
	}
	stk[top] = st;
	min_heapify_insert(stk, top);
	top++;
}

struct node pop(struct node stk[]){
	struct node ans;
	if (!isEmpty()){
		ans = stk[0];
		stk[0] = stk[--top];
		min_heapify_delete(stk, 0);
		return ans;
	}
	cout << "Stack Underflow\n" << endl;
	return ans;
}

void display_heap(struct node stk[]){
	cout << "Vertex\t" << "MinDist" << endl; 
	for(int i=0; i<top; i++){
		cout << stk[i].vertex << "\t\t " << stk[i].min_dist << endl;
	}
}

int **graph_gen(int size){
	int **graph = new int*[size];
	for (int i=0; i<size; i++) graph[i] = new int[size];
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			graph[i][j] = 0;
	return graph;
}

bool detect_cycle(int **graph, int size, bool* visited, int vertex, int parent){
	visited[vertex] = true;

	for(int i=0; i<size; i++){
		if(!visited[i] && graph[vertex][i]!=0){
			if(detect_cycle(graph, size, visited, i, vertex))
				return true;
		}
		else if (i!=parent && graph[vertex][i]!=0)	return true;
	}
	return false;
}

bool detect_cycle_util(int **graph, int size){
	bool *visited = new bool[size];
	for(int i=0; i<size; i++)	visited[i] = false;
	if(detect_cycle(graph, size, visited, 0, -1))
		return true;
	return false;
}

void kruskal(struct graph* G, int size){
	struct node unit;
	struct node stk[size*size];
	int **new_graph = graph_gen(size);

	for(int i=0; i<size; i++){
		struct node_graph* temp = G->array[i].head;
		while(temp){
			unit.vertex = temp->vertex;
			unit.parent = i;
			unit.min_dist = temp->weight;
			push(stk, unit);
			temp = temp->link;
		}
	}
	struct node_graph* temp;

	while(top){
		unit = pop(stk);
		int prev = unit.parent;
		int ver = unit.vertex;
		temp = G->array[prev].head;
		while(temp->vertex!=ver){
			temp = temp->link;
		}

		new_graph[prev][ver] = temp->weight;
		new_graph[ver][prev] = temp->weight;
		if(detect_cycle_util(new_graph, size)){
			new_graph[prev][ver] = 0;
			new_graph[ver][prev] = 0;
		}

	}

	display(new_graph, size);
}

int main(){
	int size;
	cin >> size;
	struct graph* G = (struct graph*)malloc(sizeof(struct graph));

	init(G, size, true);

	kruskal(G, G->V);
}
