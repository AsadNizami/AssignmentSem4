#include <iostream>
using namespace std;
int const large_num = 1e2;


void init(int **dp, int **breakpoint, int max_size){
	for(int i=0; i<max_size; i++)
		dp[i] = new int[max_size];

	for(int i=0; i<max_size; i++)
		breakpoint[i] = new int[max_size];

	for (int i=0; i<max_size; i++)
		for (int j=0; j<max_size; j++)
		{
			dp[i][j] = large_num;
			breakpoint[i][j] = large_num;
		}
	for (int i=0; i<max_size; i++)
		dp[i][i] = 0;
}

void display(int **arr, int size){
	for (int i=0; i<size; i++){
		for(int j=0; j<size; j++)
			cout << arr[i][j] << "\t";
		cout << endl;
	}
	cout << "\n\n" << endl;
}

void mcm(int arr[], int size){

	int **dp = new int *[size];
	int **breakpoint = new int *[size];

	init(dp, breakpoint, size);

	for(int len=1; len<size; len++){
		for(int i=0; i<size-len; i++){
			int j = len + i;
			for(int k=i; k<j; k++){
				int temp = dp[i][k] + dp[k+1][j] +
				arr[i]*arr[k+1]*arr[j+1];

				if (temp < dp[i][j]){
					dp[i][j] = temp;
					breakpoint[i][j] = k;
				}
			}//dp[i][j] = 0;
			// display(dp, size);

		}
	}

	display(dp, size);
	display(breakpoint, size);
}

int main(){

	int size;
	cin >> size;
	int arr[size];
	for (int i=0; i<size; i++)	cin >> arr[i]; 
	mcm(arr, size-1);
	// display(arr, size);
}