#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>

using namespace std;

void bfs(int vert, int &answer, vector<vector<int>> &edges, vector<int> &visited){
	if (visited[vert] == 1) return;
	answer++;
	stack<int> to_visit;
	to_visit.push(vert);
	visited[vert] = 1;
	while(!to_visit.empty()){
		int cur = to_visit.top();
		to_visit.pop();
		for(auto it = edges[cur].begin(); it != edges[cur].end(); it++){
			if (visited[*it] == 0){
				visited[*it] = 1;
				to_visit.push(*it);
			}
		}
	}
}

int num_components(int num_vert, vector<vector<int>> &edges){
	int answer = 0;
	vector<int> visited(num_vert, 0);
	for(int i = 0; i < num_vert; i++){
		bfs(i, answer, edges, visited);
	}
	return answer;
}

int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> edges(n);
	for(int i = 0; i < m; i++){
		int a,b;
		cin >> a >> b;
		edges[a-1].push_back(b-1);
		edges[b-1].push_back(a-1);
	}
	cout << num_components(n, edges) << endl;
	return 0;
}