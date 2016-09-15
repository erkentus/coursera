/**
 * gaussian elimination
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long ll;

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	cout << setprecision(5);
	int n;
	cin >> n;
	if (n == 0) return 0;
	vector<vector<double>> a(n, vector<double>(n+1, 0));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> a[i][j];
		}
	}

	vector<int> used(n, -1);
	for(int t = 0; t < n; t++){
		//let's find one equation with a non-zero in first coefficient
		for(int i = 0; i < n; i++){
			if (a[i][t] != 0 && used[i] == -1) {
				// cout << "found: " << i << endl;
				used[i] = t;
				for(int j = 0; j < n; j++){
					if (j == i || a[j][t] == 0) continue;
					double coef = a[j][t]/a[i][t];
					for(int k = 0; k < n+1; k++){
						a[j][k] -= coef*a[i][k];
					}
				}
				break;
			}
		}
	}
	vector<double> ans(n, 0.0);
	for(int i = 0; i < n; i++){
		if (used[i] != -1){
			int t = used[i];
			ans[t] = a[i][n]/a[i][t];
		}
	}
	for(int i = 0; i < n; i++){
		cout << setprecision(10) << ans[i] << endl;
	}
	return 0;
}