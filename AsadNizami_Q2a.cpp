#include <iostream>
using namespace std;

int priority = 0, max_size = 10;
int top = 0;

struct node{
	char job;
	int profit;
	int deadline;
};

bool isEmpty(){
	if (top==0)	return true;
	return false;
}

bool isFull(){
	if(top==max_size)	return true;
	return false;
}
void max_heapify_insert(struct node stk[], int index){
	int parent = (index-1)/2;

	if(stk[parent].profit < stk[index].profit){
		swap(stk[parent], stk[index]);
		max_heapify_insert(stk, parent);
	}
}
void max_heapify_delete(struct node stk[], int index){
	int left = 2*index+1;
	int right = 2*index+2;
	struct node left_child = stk[left];
	struct node right_child = stk[right];
	int max = index;
	
	if(left<=top && left_child.profit > stk[max].profit)	max = left;
	if(right<=top && right_child.profit > stk[max].profit)	max = right;
	
	if(stk[max].profit != stk[index].profit){
		swap(stk[max], stk[index]);
		max_heapify_delete(stk, max);
	}
}

void push(struct node stk[], struct node unit){
	if (isFull()){
		cout << "Stack Overflow\n" << endl;
		return;
	}
	stk[top] = unit;
	max_heapify_insert(stk, top);
	top++;
}


struct node pop(struct node stk[]){
	if (isEmpty()){
		cout << "Stack Underflow\n" << endl;
		return stk[100];
	}
	
	struct node ans = stk[0];
	stk[0] = stk[--top];
	max_heapify_delete(stk, 0);
	return ans;
}


void display(struct node job_arr[], int size){
	cout << "Job " << "Profit " << " Deadline\n";
	for (int i=0; i<size; i++)
		if (job_arr[i].profit != 0)
		cout << job_arr[i].job << " \t" << job_arr[i].profit << " \t\t" << job_arr[i].deadline << endl; 
}


int main(){
	int size;
	cin >> size;
	struct node job_seq[size];
	struct node heap[max_size];
	struct node unit;
	for(int i=0; i<size; i++){
		job_seq[i].profit = 0;
		cin >> unit.job >> unit.deadline >> unit.profit;
		push(heap, unit);	
	}
	// display(heap, size);
	while(top){
		unit = pop(heap);
		int point = unit.deadline-1;

		while(point>-1){
			if (job_seq[point].profit==0){
				job_seq[point] = unit;
				break;
			}
			else point--;
		}
	}
	display(job_seq, size);
}