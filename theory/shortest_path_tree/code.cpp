#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> pii;
typedef long long ll;
typedef std::pair<ll, ll> pll;

ll bfs(int start, std::vector<int> &prev, const std::vector<std::vector<int>> &graph){
	ll answer = -1;
	std::queue<int> to_visit;
	std::vector<int> visited(graph.size(), 0);
	std::vector<int> dist(graph.size(), 0);
	to_visit.push(start);
	visited[start] = 1;
	while(!to_visit.empty()){
		int cur = to_visit.front();
		to_visit.pop();
		for(auto it = graph[cur].begin(); it != graph[cur].end(); it++){
			int neigh = *it;
			if (visited[neigh] == 0){
				dist[neigh] = dist[cur] + 1;
				to_visit.push(neigh);
				visited[neigh] = 1;
				prev[neigh] = cur;
			}
		}
	}
	return answer;
}

/** prints reversed shortest path from start to end (end can vary) */

void solution(const std::vector<std::vector<int>> &graph, int start){
	std::vector<int> prev(graph.size(), -1);
	bfs(start, prev, graph);
	for(int i = 0; i < graph.size(); i++){
		std::cout << "shortest path from: " << start << " to: " << i << std::endl;
		int cur = i;
		while(prev[cur] != -1){
			std::cout << cur << " ";
			cur = prev[cur];
		}
		std::cout << std::endl;
	}
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
	int start;
	std::cin >> start;
	solution(graph, start-1);
	/* code */
	return 0;
}