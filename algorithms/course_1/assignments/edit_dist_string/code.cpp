#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	string a,b;
	cin >> a >> b;
	int n = a.length();
	int m = b.length();
	vector<vector<int> > dp(n+1, vector<int>(m+1, 0));
	for(int i = 0; i < n+1; i++){
		for(int j = 0; j < m+1; j++){
			if (i == 0){
				dp[i][j] = j;
			}
			else if (j == 0){
				dp[i][j] = i;
			}
			else {
				if (a[i-1] == b[j-1]){
					dp[i][j] = dp[i-1][j-1];
				}
				else {
					dp[i][j] = 1 + min({dp[i-1][j], dp[i-1][j-1], dp[i][j-1]});
				}
			}
		}
	}
	cout << dp[n][m] << endl;
	return 0;
}
