#include <iostream>
using namespace std;

int priority = 0, size = 100;
int top = 0;

struct stack{
	int priority;
	int value;
};

bool isEmpty(){
	if (top==0)	return true;
	return false;
}

bool isFull(){
	if(top==size)	return true;
	return false;
}
void max_heapify_insert(struct stack stk[], int index){
	int parent = (index-1)/2;

	int largest = index;
	if(stk[parent].priority < stk[index].priority){
		swap(stk[parent], stk[index]);
		max_heapify_insert(stk, parent);
	}
}
void max_heapify_delete(struct stack stk[], int index){
	int left = 2*index+1;
	int right = 2*index+2;
	struct stack left_child = stk[left];
	struct stack right_child = stk[right];
	int largest = index;
	
	if(left<=top && left_child.priority > stk[largest].priority)	largest = left;
	if(right<=top && right_child.priority > stk[largest].priority)	largest = right;
	
	if(stk[largest].priority != stk[index].priority){
		swap(stk[largest], stk[index]);
		max_heapify_delete(stk, largest);
	}
	
}

void push(struct stack stk[]){
	if (isFull()){
		cout << "Stack Overflow\n" << endl;
		return;
	}
	int value;
	cout << "Enter a value" << endl;
	cin >> value;
	cout << "\n\n";
	stk[top].priority = priority++;
	stk[top].value = value;
	max_heapify_insert(stk, top);
	top++;
}


int pop(struct stack stk[]){
	if (isEmpty()){
		cout << "Stack Underflow\n" << endl;
		return -1;
	}
	
	int ans = stk[0].value;
	stk[0] = stk[top--];
	max_heapify_delete(stk, 0);
	return ans;
}

void display(struct stack stk[]){
	for(int i=0; i<top; i++){
		cout << stk[i].priority << " " << stk[i].value << endl;
	}
}

int menu(){
	cout << "Enter:" << endl;
	cout << "1: Push" << endl;
	cout << "2: Pop" << endl;
	cout << "3: IsEmpty" << endl;
	cout << "4: IsFull" << endl;
	int option;
	cin >> option;
	return option;
}

int main(){
	stack stk[size];
	while (true){
		int option = menu();
		if(option==1)	push(stk);
		else if(option==2)	cout << pop(stk) << endl;
		else if(option==3)	cout << isEmpty() << endl;
		else if(option==4) 	cout << isFull() << endl;
		else if(option==5) display(stk);
		else	break;
	}
}
