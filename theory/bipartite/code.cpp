#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> pii;
typedef long long ll;
typedef std::pair<ll, ll> pll;

bool is_bipartite(int start, const std::vector<std::vector<int>> &graph){
	bool is_bipartite = true;
	std::queue<int> to_visit;
	std::vector<int> visited(graph.size(), 0);
	std::vector<int> color(graph.size(), -1);
	to_visit.push(start);
	visited[start] = 1;
	color[start] = 0;
	while(!to_visit.empty()){
		int cur = to_visit.front();
		to_visit.pop();
		for(auto it = graph[cur].begin(); it != graph[cur].end(); it++){
			int neigh = *it;
			if (visited[neigh] == 0){
				to_visit.push(neigh);
				visited[neigh] = 1;
				if (color[cur] == 0) color[neigh] = 1;
				else color[neigh] = 0;
			}
			else if (color[neigh] == color[cur]) {
				is_bipartite = false;
			}
		}
		if (!is_bipartite) break;
	}
	return is_bipartite;
}

int main(int argc, char const *argv[])
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> graph(n);
	for(int i = 0; i < m; i++){
		int x, y;
		std::cin >> x >> y;
		graph[x-1].push_back(y-1);
		graph[y-1].push_back(x-1);
	}
	int start = 0;
	std::cout << is_bipartite(start, graph) << std::endl;
	/* code */
	return 0;
}