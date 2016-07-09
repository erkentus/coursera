#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> pii;
typedef long long ll;
typedef std::pair<ll, ll> pll;

ll bfs(int start, int end, const std::vector<std::vector<int>> &graph){
	ll answer = -1;

	std::queue<int> to_visit;
	std::vector<int> visited(graph.size(), 0);
	std::vector<int> dist(graph.size(), 0);
	to_visit.push(start);
	visited[start] = 1;
	while(!to_visit.empty()){
		int cur = to_visit.front();
		if (cur == end) {
			answer = dist[cur];
			break;
		}
		to_visit.pop();
		for(auto it = graph[cur].begin(); it != graph[cur].end(); it++){
			int neigh = *it;
			if (visited[neigh] == 0){
				dist[neigh] = dist[cur] + 1;
				to_visit.push(neigh);
				visited[neigh] = 1;
			}
		}
	}
	return answer;
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
	int start, end;
	std::cin >> start >> end;
	std::cout << bfs(start-1, end-1, graph) << std::endl;
	/* code */
	return 0;
}