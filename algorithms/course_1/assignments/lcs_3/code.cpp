#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	int a,b,c;
	cin >> a;
	vector<int> A(a);
	for(int i = 0; i < a; i++){
		int x;
		cin >> x;
		A[i] = x;
	}
	cin >> b;
	vector<int> B(b);
	for(int i = 0; i < b; i++){
		int x;
		cin >> x;
		B[i] = x;
	}
	cin >> c;
	vector<int> C(c);
	for(int i = 0; i < c; i++){
		int x;
		cin >> x;
		C[i] = x;
	}
	vector<vector<vector<int> > > dp(a+1, vector<vector<int>>(b+1, vector<int>(c+1, 0)));
	for(int i = 0; i < a+1; i++){
		for(int j = 0; j < b+1; j++){
			for(int k = 0; k < c+1; k++){
				if (i == 0 || j == 0 || k == 0){
					dp[i][j][k] = 0;
				}
				else{
					if (A[i-1] == B[j-1] && B[j-1] == C[k-1]){
						dp[i][j][k] = dp[i-1][j-1][k-1]+1;
					}
					else{
						dp[i][j][k] = max({
							dp[i-1][j][k],
							dp[i][j-1][k],
							dp[i][j][k-1]
						});
					}
				}
			}
		}
	}
	cout << dp[a][b][c] << endl;
	/* code */
	return 0;
}
