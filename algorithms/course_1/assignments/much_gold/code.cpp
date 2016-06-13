#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	int total, n;
	cin >> total >> n;
	vector<int> caps;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		if (x > 0) caps.push_back(x);
	}
	sort(caps.begin(), caps.end());
	n = caps.size();
	vector<vector<int> > dp(total+1, vector<int>(n, 0));
	for(int i = 1; i < total+1; i++){
		for(int j = 0; j < n; j++){
			if ( i == 1 ){
				if (caps[0] <= 1){
					dp[1][j] = 1;
				}
			}
			else {
				if (j == 0){
					if (i >= caps[0]){
						dp[i][0] = caps[0];
					}
				}
				else{
					if (i >= caps[j]) dp[i][j] = max({dp[i-caps[j]][j-1]+caps[j], dp[i][j-1]});
					else{
						dp[i][j] = dp[i][j-1];
					}
				}
			}
		}
	}
	cout << dp[total][n-1] << endl;
	return 0;
}