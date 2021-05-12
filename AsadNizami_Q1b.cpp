#include <iostream>
using namespace std;

void display(int **dp, int x, int y){
	for(int i=0; i<=x; i++){
		for(int j=0; j<=y; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}
}

void print_LCS(int **dp, string st1, string st2){
	int x = st1.size();
	int y = st2.size();
	string lcs = "";
	while(true){
		cout << x << " " << y << endl;

		if(x==0 || y==0)	break;

		else if(dp[x-1][y]!=dp[x][y]  && dp[x][y-1]!=dp[x][y]){ 
		// if current cell differs from upper and left cell
		// then the upper cell has matched
			lcs = st1[x-1] + lcs;
			x -= 1;
			y -= 1;
		} 

		else{
			if (dp[x-1][y] > dp[x][y-1]) x -=1;
			else y -= 1;
		}

	}
	cout << lcs << endl;
}

int LCS(int **dp, string st1, string st2){
	int s1 = st1.size()+1;
	int s2 = st2.size()+1;
	for (int i=0; i<s1; i++){
		for (int j=0; j<s2; j++){
			if (i==0 || j==0)	dp[i][j] = 0;

			else if(st1[i-1]==st2[j-1])
				dp[i][j] = 1 + dp[i-1][j-1];

			else
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	print_LCS(dp, st1, st2);
	return dp[st1.size()][st2.size()];
}

int main(){
	string st1 = "ACBCF";
	string st2 = "ABCDAF";
	int size = st1.size();  
	int **dp = new int *[size+1];
	for (int i=0; i<size+1; i++){
		dp[i] = new int[st2.size()+1];
	}
	int ans = LCS(dp, st1, st2);
	cout << ans << endl;
}
