#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
using namespace std;

struct list{
	struct node* head;
};

struct node{
	char word[20];
	int repeat;
	struct node* link;
};

void init(struct list* lst, int size){
	for(int i=0; i<size; i++)
		lst[i].head = NULL; 
}


void display_list(struct list* lst, int size){
	for(int i=0; i<size; i++){
		struct node* temp = lst[i].head;
		printf("\n%d: ", i);
		while(temp){
			cout << temp->word << ": " << temp->repeat << " "; 
			temp = temp->link;
		}
	}
	cout << "\n" << endl;
}

int get_key(int size, string word){
	long long count = 0;
	for(int i=0; i<word.length(); i++){
		count += pow(31, i)*word[i];
	}
	count = count % size;
	return count;
}

struct node* get_point(struct list* lst, string word, int key){
	struct node* temp = lst[key].head;

	while(temp){
		if(temp->word == word){
			return temp;
		}
		temp = temp->link;
	}

	return temp;
}

void insert(struct list* lst, int size, string word){
	int key = get_key(size, word);
	struct node* point = get_point(lst, word, key);
	if(point == NULL){
		struct node* temp = (struct node*)malloc(sizeof(struct node));
		strcpy(temp->word, word.c_str());
		temp->repeat = 1;
		point = lst[key].head;
		lst[key].head = temp;
		temp->link = point;
	}

	else{
		point->repeat += 1;
	}
}

void display_occ(struct list* lst, int size, string word){
	int key = get_key(size, word);
	struct node* point = get_point(lst, word, key);
	if(point)	cout << point->repeat << endl;
	else cout << 0 << endl;
}

int main(){
	string line, word;
	int size = 30;
	struct list* lst = (struct list*)malloc(size*sizeof(struct list));
	init(lst, size);

	ifstream file("Question2.txt");
	while(getline(file, line)){

		stringstream iss(line);
		while(iss >> word){
			insert(lst, size, word);
		}
	}
	// display_list(lst, size);
	cin >> word;
	display_occ(lst, size, word);
}