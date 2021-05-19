#include <iostream>
using namespace std;

int const large_num = 1e3;
int priority = 0, max_size = 100;
int top = 0;

struct node{
	int vertex;
	int min_dist;
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


void addEdge(struct graph* G, int v1, int v2, int weight){ // Adding the edges

	struct node_graph* temp = (struct node_graph*)malloc(sizeof(struct node_graph));
	temp->vertex = v2;
	temp->weight = weight;
	temp->link = G->array[v1].head;
	G->array[v1].head = temp;
	
}

void init(struct graph *G, int size, bool add){
	int **graph_raw;
	// cin >> size;
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

void display(int **graph, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cout << graph[i][j] << " ";
		cout << endl;
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
void prims(struct graph* G, int size){
	struct graph* new_G = (struct graph*)malloc(sizeof(struct graph));
	init(new_G, size, false);
	struct node stk[max_size];
	struct node unit;
	int weight[size]; bool visited[size];
	for(int i=0; i<size; i++)	weight[i] = large_num;
	for(int i=0; i<size; i++)	visited[i] = false;
		weight[0] = 0;
	int count=0, min_dist, curr;
	unit.vertex = 0;
	unit.min_dist = 0;
	push(stk, unit);

	while(count<size-1){
		min_dist = large_num;
		curr = pop(stk).vertex;
		struct node_graph* temp = G->array[curr].head;

		if (visited[curr]) continue; 
		visited[curr] = true;
		while(temp){

			if(!visited[temp->vertex] && weight[temp->vertex]>temp->weight){
				weight[temp->vertex] = temp->weight;
				addEdge(new_G, curr, temp->vertex, temp->weight);
				addEdge(new_G, temp->vertex, curr, temp->weight);
				struct node unit;
				unit.vertex = temp->vertex;
				unit.min_dist = temp->weight;
				push(stk, unit);
			}
			temp = temp->link;
			count++;
		}
	}
	display_graph(new_G);
}

int main(){
	int size;
	cin >> size;
	struct graph *G = (struct graph*)malloc(sizeof(struct graph));
	init(G, size, true);
	// display_graph(G);

	prims(G, G->V);
}
// Sample Test Case
// 5
// 0 2 0 6 0
// 2 0 3 8 5
// 0 3 0 0 7
// 6 8 0 0 9
// 0 5 7 9 0