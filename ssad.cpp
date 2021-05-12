#include <iostream>
using namespace std;

int priority = 0, max_size = 100;
int top = 0;

struct node{
	int vertex;
	int min_dist;
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
		stk[0] = stk[top--];
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

void dijkstra(int **graph, int size, int start){
	node stk[max_size];
	int min_distance[size];
	bool visited[size];

	for(int i=0; i<size; i++){
		stk[i].vertex = i;
		stk[i].min_dist = 1e9;
		min_distance[i] = 1e9;
		visited[i] = false;
	}

	min_distance[start] = 0;
	struct node temp, curr;
	temp.min_dist = 0;
	temp.vertex = start;
	push(stk, temp);
	
	while(top){
		curr = pop(stk);
		visited[curr.vertex] = true;
		for(int i=0; i<size; i++){
			int new_dist = curr.min_dist + graph[curr.vertex][i];
			if(graph[curr.vertex][i]!=0 && !visited[i] && new_dist<min_distance[i]){
				
				temp.min_dist = new_dist;
				min_distance[i] = temp.min_dist;
				temp.vertex = i;
				push(stk, temp);
			}
		}
	}
	for(int i=0; i < size; i++){
		cout << i << " " << min_distance[i] << endl;
	}
}

void display(int **graph, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cout << graph[i][j] << " ";
		cout << endl;
	}
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
	dijkstra(graph, size, 0);
}