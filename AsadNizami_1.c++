#include <iostream>
using namespace std;

const int graph_size = 100;
int graph[graph_size][graph_size];
int max_node = -1;

const int queue_size = 100;
int queue[queue_size];
int front = -1;
int rear = -1;

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
void bfs(){
	int visited[max_node], src;
	cout << "Enter the node for bfs"<< endl;
	cin >> src;
	visited[src] = 1;
	int curr = src;

	while(true){
		cout << curr << " ";

		for(int j=0; j<=max_node; j++){
			if(graph[curr][j] == 1 && visited[j] != 1){
				enqueue(j);
				visited[j] = 1;
			}
		}
		if(isEmpty())
		{
			cout << "\n" << endl;
			return;
		} 
		curr = dequeue();
	}

}

void search(){
	int node;
	cout << "Enter the node to search" << endl;
	cin >> node;
	if(0 <= node && node <= max_node){
		cout << "Node found" << endl;
		cout << "Edges:" << endl;
		for(int i=0 ;i<= max_node; i++){
			if(graph[node][i] == 1)cout<< i << " ";
		}
	}
	else cout << "Node not found" << endl;
}

void insert_node(){
	max_node++;
	cout << "Node Inserted:" << max_node << endl;
}

void insert_edge(){
	int first, second;
	cout << "Enter the nodes to insert edge between them" << endl;
	cin >> first >> second;
	if ((0 <= first && first <= max_node) && (0 <= second && second <= max_node)){
		graph[first][second] = 1;
		graph[second][first] = 1;
		cout << "Edge inserted" << endl;
	}
	else cout << "Invalid Input" << endl;
}

void delete_node(){
	int node;
	cout << "Enter the node to delete" << endl;
	cin >> node;
	if (0 <= node && node <= max_node){
		for(int i=0; i<=max_node; i++){
			if(graph[node][i] == 1){
				graph[node][i] = 0;
				graph[i][node] = 0;
			}
		}
		cout << "Node deleted" << endl;
	}
	else cout << "Invalid Input" << endl;
}

void show_graph(){
	for(int i=0; i<=max_node; i++){
		for(int j=0; j<=max_node; j++)
			cout << graph[i][j] << " ";
		cout << "\n" << endl;
	}
}

int menu(){
	int option;
	cout << "Enter:" << endl;
	cout << "1: Search a node" << endl;
	cout << "2: Insert a node" << endl;
	cout << "3: Insert an edge" << endl;
	cout << "4: Delete a node" << endl;
	cout << "5: Show graph" << endl;
	cout << "6: BFS" << endl;
	cout << "7: DFS" << endl;
	cin >> option;
	return option;
}

void dfs(int visited[], int vertex){
	visited[vertex] = 1;
	cout << vertex << " ";
	for(int i=0; i<=max_node; i++){
		if(visited[i]!=1 && graph[vertex][i]==1){
			dfs(visited, i);
		}
	}
}

void dfs_helper(){
	int visited[max_node], src;
	cout << "Enter the node for dfs" << endl;
	cin >> src;
	dfs(visited, src);
	cout << "\n" << endl;
}

int main(){
	while(true){
		int option = menu();
		if(option == 1)		search();
		else if(option == 2)	insert_node();
		else if(option == 3)	insert_edge();
		else if(option == 4)	delete_node();
		else if(option == 5)	show_graph();
		else if(option == 6)	bfs();
		else if(option == 7) 	dfs_helper();
		else break;
	}
}