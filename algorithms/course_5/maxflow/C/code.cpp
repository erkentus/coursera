#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

struct edge{
	int f = 0;
	int c = 0;
	edge(int f, int c):f(f),c(c){}
};

bool find_update_path(vector<vector<edge>> &graph){
	int n = graph.size();
	bool path_found = false;
	/** bfs */
	queue<int> q;
	vector<int> prev(n, -1);
	vector<bool> visited(n, false);
	q.push(0);
	visited[0] = true;
	while(!q.empty()){
		int cur = q.front();
		if (cur == n-1){
			path_found = true;
			while(prev[cur] != -1){
				int par = prev[cur];
				graph[par][cur].f += 1;
				graph[cur][par].f -= 1;
				cur = par;
			}
			break;
		}
		q.pop();
		for(int i = 0; i < n; i++){
			if (i != cur && graph[cur][i].f < graph[cur][i].c && !visited[i]){
				prev[i] = cur;
				visited[i] = true;
				q.push(i);
			}
		}
	}
	return path_found;
}

int compare(const vector<vector<int>> &s, int i, int j){
	if (i == j) return 0;
	i--;j--;
	vector<int> a = s[i];
	vector<int> b = s[j];
	int n = a.size();
	bool ss = true;
	for(int i = 0; i < n; i++){
		ss = ss && ((a[i]-b[i]) < 0);
	}
	if (ss) return 1;
	return 0;
}

int main(int argc, char const *argv[])
{	
	ios::sync_with_stdio(false);
	int n,m;
	cin >> n >> m;
	vector<vector<int>> s(n, vector<int>(m, 0));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> s[i][j];
		}
	}
	auto comp = [](const vector<int> &a, const vector<int> &b) -> bool {
		return a[0] < b[0];
	};
	sort(s.begin(), s.end(), comp);
	vector<vector<edge>> graph(2*n+2, vector<edge>(2*n+2, edge(0,0)));
	for(int i = 1; i < n+1; i++){
		graph[0][i].c = 1;
		graph[i][0].c = 1;
		graph[i][0].f = 1;
	}
	for(int i = n+1; i < 2*n+1; i++){
		graph[i][2*n+1].c = 1;
		graph[2*n+1][i].c = 1;
		graph[2*n+1][i].f = 1;
	}
	for(int i = 1; i < n+1; i++){
		for(int j = 1; j < n+1; j++){
			int x = compare(s, i, j);
			graph[i][j+n].c = x;
			graph[j+n][i].c = x;
			graph[j+n][i].f = x;
		}
	}
	while(find_update_path(graph)){

	}
	vector<bool> visited(n, false);
	int total = 0;
	for(int i = 0; i < n; i++){
		if (!visited[i]){
			total++;
			//visit
			int cur = i+1;
			while(true){
				bool fin = true;
				for(int j = n+1; j < 2*n+1; j++){
					if (graph[cur][j].f == 1){
						visited[j-n-1] = true;
						fin = false;
						cur = j-n;
						break;
					}
				}
				if (fin) break;
			}
		}
	}
	cout << total << endl;
	return 0;
}
