#include <iostream>
using namespace std;

int const large_num = 1e3;

void display(int **graph, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cout << graph[i][j] << " ";
		cout << endl;
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

void prims(int **graph, int size){
	int **new_graph = graph_gen(size);
	int weight[size]; bool visited[size];
	for(int i=0; i<size; i++)	weight[i] = large_num;
	for(int i=0; i<size; i++)	visited[i] = false;
		weight[0] = 0;
	int count = 0, min_dist = large_num, curr;
	while(count<size-1){
		min_dist = large_num;

		for(int i=0; i<size; i++){
			if (!visited[i] && min_dist>weight[i])
				curr = i, min_dist = weight[i];
		}

		visited[curr] = true;

		for(int i=0; i<size; i++){

			if(graph[curr][i] && !visited[i] && weight[i]>graph[curr][i]){

				new_graph[curr][i] = graph[curr][i];
				new_graph[i][curr] = graph[curr][i];
				weight[i] = graph[curr][i];
			}
		}

		count++;
	}
	display(new_graph, size);
}

int main(){
	int size;
	cin >> size;
	int **graph = graph_gen(size);

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cin >> graph[i][j];
	}

	// display(graph, size);
	prims(graph, size);
}
