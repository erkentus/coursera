#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <deque>

typedef std::pair<int, int> pii;

bool has_cycle(int cur,
	std::vector<int> &visited, 
	std::vector<int> &marked, 
	const std::vector<std::vector<int>> &edges){
	
	bool ans = false;
	if (visited[cur] == 1) return false;
	if (marked[cur] == 1) return true;
	marked[cur] = 1;
	for(auto it = edges[cur].begin(); it != edges[cur].end(); it ++){
		ans = ans || has_cycle(*it, visited, marked, edges);
	}
	visited[cur] = 1;
	marked[cur] = 0;
	return ans;
}

void solution(const std::vector<std::vector<int>> &edges){
	bool answer = false;
	int num_vert = edges.size();
	std::vector<int> visited(num_vert, 0);
	std::vector<int> marked(num_vert, 0);
	for(int i = 0; i < num_vert; i++){
		if (has_cycle(i, visited, marked, edges)){
			answer = true;
			break;
		}
	}
	std::cout << answer << std::endl;
}

int main(int argc, char const *argv[])
{
	std::ios::sync_with_stdio(false);
	int n,m;
	std::cin >> n >> m;	
	std::vector<std::vector<int>> edges(n);
	for(int i = 0; i < m; i++){
		int s,e;
		std::cin >> s >> e;
		edges[s-1].push_back(e-1);
	}
	solution(edges);
	return 0;
}
