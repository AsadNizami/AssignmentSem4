#include <iostream>
using namespace std;

int priority = 0, max_size = 100;
int top = 0;

struct node{
	int vertex;
	int min_dist;
	int parent;
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

void display(int **graph, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cout << graph[i][j] << " ";
		cout << endl;
	}
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

int **graph_gen(int size){
	int **graph = new int*[size];
	for (int i=0; i<size; i++) graph[i] = new int[size];
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			graph[i][j] = 0;
	return graph;
}

void kruskal(int **graph, int size){
	struct node unit;
	struct node stk[size*size];
	int **new_graph = graph_gen(size);
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			if(graph[i][j]!=0){
				unit.vertex = j;
				unit.parent = i;
				unit.min_dist = graph[i][j];
				push(stk, unit);
			}
	while(top){
		unit = pop(stk);
		int prev = unit.parent;
		int ver = unit.vertex;
		new_graph[prev][ver] = graph[prev][ver];
		new_graph[ver][prev] = graph[prev][ver];
		if(detect_cycle_util(new_graph, size)){
			new_graph[prev][ver] = 0;
			new_graph[ver][prev] = 0;
		}
	}
	display(new_graph, size);
}

int main(){
	int size;
	int **graph;
	cin >> size;
	graph = new int *[size];

	for(int i=0; i <size; i++)
   		graph[i] = new int[size];

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cin >> graph[i][j];
	}
	kruskal(graph, size);
}
