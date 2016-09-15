#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

struct edge{
	int f;
	int c;
	edge(int f, int c): c(c), f(f){};
	void print(){
		cout << "total capacity: " << c << endl;
		cout << "flow: " << f << endl;
	}
};	

bool find_update_path(vector<vector<edge>> &graph, int &answer){
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
			int ccur = cur;
			int mmin = 1e9;
			while(prev[ccur] != -1){
				int par = prev[ccur];
				mmin = min({graph[par][ccur].c - graph[par][ccur].f ,mmin});
				ccur = par;
			}
			answer += mmin;
			while(prev[cur] != -1){
				int par = prev[cur];
				graph[par][cur].f += mmin;
				graph[cur][par].f -= mmin;
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
	vector<vector<edge>> graph(n, vector<edge>(n, edge(0,0)));
	for(int i = 0; i < m; i++){
		int u,v,c;
		cin >> u >> v >> c;
		u--;v--;
		if (u != v) {
			graph[u][v].c += c;
			graph[v][u].c += c;
			graph[v][u].f += c;
		}
	}
	int answer = 0;
	while(find_update_path(graph, answer)){
		// cout << "here" << endl;
	}
	cout << answer << endl;
	return 0;
}
