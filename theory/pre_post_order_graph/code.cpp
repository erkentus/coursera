#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
typedef pair<int, int> pii;

int c = 0;

void explore(
		int cur,
		vector<int> &visited,
		const vector<vector<int>> &edges,
		vector<pii> &pre,
		vector<pii> &post
	){	
	visited[cur] = 1;
	pre[cur].first = ++c;
	for(auto it = edges[cur].begin(); it != edges[cur].end(); it++){
		if (visited[*it] == 0)
			explore(*it, visited, edges, pre, post);
	}
	post[cur].first = ++c;
}

int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	vector<pii> pre(n);
	vector<pii> post(n);
	vector<vector<int>> edges(n);
	for(int i = 0; i < n; i++){
		pre[i] = {0, i};
		post[i] = {0, i};
	}	
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		edges[x-1].push_back(y-1);
	}

	vector<int> visited(n , 0);
	for(int i = 0; i < n; i++){
		if (visited[i] == 0){
			explore(i, visited, edges, pre, post);
		}
	}
	return 0;
}
