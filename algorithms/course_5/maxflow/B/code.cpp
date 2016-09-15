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

int main(int argc, char const *argv[])
{	
	ios::sync_with_stdio(false);
	int n,m;
	cin >> n >> m;
	vector<vector<edge>> graph(n+m+2, vector<edge>(n+m+2, edge(0,0)));
	for(int i = 1; i < n+1; i++){
		graph[0][i].c = 1;
		graph[i][0].c = 1;
		graph[i][0].f = 1;
	}
	for(int i = n+1; i < n+m+1; i++){
		graph[i][n+m+1].c = 1;
		graph[n+m+1][i].c = 1;
		graph[n+m+1][i].f = 1;
	}
	for(int i = 1; i < n+1; i++){
		for(int j = 1; j < m+1; j++){
			int x;
			cin >> x;
			graph[i][j+n].c = x;
			graph[j+n][i].c = x;
			graph[j+n][i].f = x;
		}
	}
	while(find_update_path(graph)){

	}
	for(int i = 1; i < n+1; i++){
		bool f = false;
		for(int j = n+1; j < n+m+1; j++){
			if (graph[i][j].f == 1){
				f = true;
				cout << (j-n) << " ";
				break;
			}
		}
		if (!f) cout << -1 << " ";
	}
	cout << endl;
	return 0;
}
