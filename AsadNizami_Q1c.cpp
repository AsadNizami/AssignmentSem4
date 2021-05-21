#include<stdio.h>
const int MAX = 100;
int dp[MAX][MAX], value[MAX], weight[MAX], m, n;

void store(){	
	printf("Enter the values:\n");
	for(int i=0; i<n; i++)
		scanf("%d", &value[i]);
	printf("Enter the weights:\n");
	for(int i=0; i<n; i++)
		scanf("%d", &weight[i]);
	for(int i=0; i<MAX; i++)
		for(int j=0; j<MAX; j++)
			dp[i][j] = -1;
}

int knapsack(int rem_weight, int i){
	if(dp[rem_weight][i] != -1)
		return dp[rem_weight][i];
		
	if(rem_weight==0 || i==n)
		return 0;
		
	if(weight[i]>rem_weight){
		dp[rem_weight][i] = knapsack(rem_weight, i+1);
		return dp[rem_weight][i];	
	}
		
	else{
		int left = knapsack(rem_weight, i+1);
		int right = value[i] + knapsack(rem_weight-weight[i], i+1);
		dp[rem_weight][i] = left>right?left:right;
		return dp[rem_weight][i];	
	}
}
int main(){
	printf("Enter the number of elements");
	scanf("%d", &n);
	printf("Enter the max capacity");
	scanf("%d", &m);
	store();
	int res = knapsack(m, 0);
	printf("%d", res);
}