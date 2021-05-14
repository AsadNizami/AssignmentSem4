#include <iostream>
using namespace std;
int const large_num = 1e2;
int const max_size = 100;
int stack[max_size];
int top = -1;
struct node{
	int data;
	struct node* link;
};
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
void dfs(int **graph, int vertex, int *visited, int size){
	visited[vertex] = 1;
	bool flag = true;
	// cout << vertex << endl;
	
	for(int i=0; i<size; i++){
		if(visited[i]==0 && graph[vertex][i]!=0){
			dfs(graph, i, visited, size);
		}
	}
	push(vertex);
}

void dfs_helper(int **graph, int size){
	int *visited = new int[size], src;
	for(int i=0; i<size; i++)	visited[i] = 0;
	for(int i=0; i<size; i++){
		if(visited[i]==0){
			dfs(graph, i, visited, size);
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
void dag(int **graph, int size, int src){
	int min_dist[size];
	for(int i=0; i<size; i++)	min_dist[i] = large_num;
	min_dist[src] = 0;

	for(int j=0; j<size; j++){
		int curr = pop();
		if (min_dist[curr]==large_num) continue;
		for(int i=0; i<size; i++){
			
			int new_dist = min_dist[curr] + graph[curr][i];
			if(new_dist<min_dist[i] && graph[curr][i]!=0){
				min_dist[i] = new_dist;
			}
		}
	}
	for(int i=0; i < size; i++){
		cout << i << " " << min_dist[i] << endl;
	}
}

int main(){
	int size, src;
	int **graph;
	cin >> size;
	graph = new int *[size];
	for(int i=0; i <size; i++)
   		graph[i] = new int[size];

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cin >> graph[i][j];
	}
	cin >> src;
	// display(graph, size);
	dfs_helper(graph, size);
	dag(graph, size, src);

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