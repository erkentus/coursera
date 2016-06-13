#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <queue>

using namespace std;

int find_parent(int i, vector<int> &p){
	while(p[i] != i){
		int j = p[i];
		p[i] = p[j];
		i = p[j];
	}
	return i;
}

void merge(int i, int j, vector<int> &h, priority_queue<long long> &max, vector<int> &p){
	int pi = find_parent(i, p);
	int pj = find_parent(j, p);
	if (pi != pj){
		h[pi] += h[pj];
		p[pj] = pi;
		h[pj] = 0;
		max.push(h[pi]);
	}
	cout << max.top() << endl;
}

int main(int argc, char const *argv[])
{
	int n,m;
	cin >> n >> m;
	vector<int> r(n, 0);
	vector<int> p(n, 0);
	priority_queue<long long> max;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		r[i] = x;
		max.push(x);
		p[i] = i;
	}
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		merge(x-1, y-1, r, max, p);
	}
	return 0;
}
