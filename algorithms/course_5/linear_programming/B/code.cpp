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

double answer = static_cast<double>(-1e9);
bool has_soln = false;
bool infinity = false;
vector<double> u;

vector<vector<double>> create_subs(vector<vector<double>> &a, vector<bool> subs, int m){
	vector<vector<double>> x;
	int n = subs.size();
	for(int i = 0; i < n; i++){
		if (subs[i]) {
			vector<double> t(a[i]);
			x.push_back(t);
		}
	}
	return x;
}

double calc_answer(vector<double> &x, vector<double> &p){
	double ans = 0.0;
	for(int i = 0; i < x.size(); i++){
		ans += x[i]*p[i];
	}
	return ans;
}

void print(vector<double> &x){
	for(auto it: x){
		cout << it << " ";
	}
	cout << endl;
}

bool verify_soln(vector<double> &x, vector<vector<double>> &a){
	bool val = true;
	int m = x.size();
	int n = a.size();
	for(int i = 0; i < m; i++){
		val = val && (x[i] >= 0);
	}
	if (!val) return val;
	for(int i = 0; i < n-m; i++){
		double t = 0.0;
		for(int j = 0; j < m; j++){
			t += x[j]*a[i][j];
		}
		val = val && (t <= a[i][m] + 1e-4);
	}
	return val;
}

vector<double> gaus_elim(vector<vector<double>> &a, bool &solv){
	int n = a.size();
	vector<int> used(n, -1);
	for(int t = 0; t < n; t++){
		for(int i = 0; i < n; i++){
			if (a[i][t] != 0 && used[i] == -1) {
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
	vector<double> ans(n, static_cast<double>(1e9));
	for(int i = 0; i < n; i++){
		if (used[i] != -1){
			int t = used[i];
			ans[t] = a[i][n]/a[i][t];
		}
	}
	for(int i = 0; i < n; i++){
		double res = 0.0;
		for(int j = 0; j < n; j++){
			res += ans[i]*a[i][j];
		}
		solv = solv && (res - a[i][n] < 1e-4);
	}
	return ans;
}

void gen_subset(vector<vector<double>> &a, 
	vector<double> &p, int left, int from, int m, vector<bool> &subs, vector<double> &u){
	int n = a.size();
	if (left == 0){
		vector<vector<double>> x = create_subs(a, subs, m);
		bool is_solvable = true;
		vector<double> ans = gaus_elim(x, is_solvable);
		if (verify_soln(ans, a) && is_solvable){
			has_soln = true;
			double calc = calc_answer(ans, p);
			if (answer < calc){
				double crazy_check = 0.0;
				for(auto it: ans){
					crazy_check += it;
				}
				if (crazy_check < static_cast<double>(1e9)){
					u = vector<double>(ans);
					answer = calc;
				} else {
					infinity = true;
				}
			}
		}
		return;
	}
	for(int i = from; i < n; i++){
		subs[i] = true;
		gen_subset(a, p, left-1, i + 1, m, subs, u);
		subs[i] = false;
	}
}	


int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	cout << setprecision(15);
	int n, m;
	cin >> n >> m;
	vector<vector<double>> a(n, vector<double>(m+1, 0));
	vector<double> p(m, 0);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> a[i][j];
		}
	}
	for(int i = 0; i < n; i++){
		cin >> a[i][m];
	}
	for(int i = 0; i < m; i++){
		vector<double> t(m+1, 0);
		t[i] = -1;
		a.push_back(t);
	}
	for(int i = 0; i < m; i++){
		cin >> p[i];
	}
	vector<bool> subs(n+m, false);
	vector<double> u;
	gen_subset(a, p, m, 0, m, subs, u);
	if (has_soln){
		if (infinity) {
			cout << "Infinity" << endl;
			return 0;
		}
		cout << "Bounded solution" << endl;
		for(auto it : u){
			cout << setprecision(15) << it << " ";
		}
		cout << endl;
	} else {
		cout << "No solution" << endl;
	}
	return 0;
}