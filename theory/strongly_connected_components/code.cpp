#include <algorithm>
#include <vector>
#include <iostream>
#include <deque>

using namespace std;
typedef pair<int, int> pii;

int c = 0;

void explore(
		int cur,
		vector<int> &visited,
		const vector<vector<int>> &graph,
		deque<int> &res
	){	
	visited[cur] = 1;
	for(auto it = graph[cur].begin(); it != graph[cur].end(); it++){
		if (visited[*it] == 0)
			explore(*it, visited, graph, res);
	}
	res.push_front(cur);
}

void mark(
		int cur,
		int cur_comp,
		vector<int> &component,
		const vector<vector<int>> &graph
	){	
	component[cur] = cur_comp;
	for(auto it = graph[cur].begin(); it != graph[cur].end(); it++){
		if (component[*it] == -1)
			mark(*it, cur_comp, component, graph);
	}
}

int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	vector<vector<int>> rgraph(n);
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		graph[x-1].push_back(y-1);
		rgraph[y-1].push_back(x-1);
	}

	vector<int> visited(n, 0);
	deque<int> res;
	for(int i = 0; i < n; i++){
		if (visited[i] == 0){
			explore(i, visited, rgraph, res);
		}
	}
	vector<int> component(n, -1);
	int num_comp = 0;
	for(int i = 0; i < n; i++){
		int ver = res[i];
		if (component[ver] == -1){
			num_comp++;
			mark(ver, num_comp, component, graph);
		}
	}
	cout << num_comp << endl;
	return 0;
}
