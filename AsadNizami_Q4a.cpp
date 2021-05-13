#include <iostream>
using namespace std;
int const large_num = 1e2;

void bellman_ford(int **graph, int size, int src){
	int min_dist[size];
	for(int i=0;i<size; ++i){
		min_dist[i] = large_num;
	}
	min_dist[src] = 0;
	bool flag = true;
	while(flag){
		flag = false;
		for(int i=0; i<size; i++){
			if(min_dist[i]==large_num)	continue;

			for(int j=0; j<size; j++){
				if(!graph[i][j]) continue;

				int new_dist = min_dist[i]+graph[i][j];
				if(min_dist[j]>new_dist){
					min_dist[j] = new_dist;
					flag = true;
				}
			}
		}
	}
	for(int i=0; i < size; i++){
		cout << i << " " << min_dist[i] << endl;
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
	int src;
	// display(graph, size);
	cin >> src;
	bellman_ford(graph, size, src);
}

// Sample test case
// 5
// 0 -1 4 0 0
// 0  0 3 2 2 
// 0  0 0 0 0 
// 0  1 5 0 0
// 0  0 0 -3 0
// 0