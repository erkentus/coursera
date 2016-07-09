#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

int diameter(const vector<vector<pii>> &graph, vector<pii> &diam){
	int n = graph.size();
	assert(diam.size() == n);
	int u, v; //starting and ending vertices in the diameter
	int start = 0; //start can be from anywhere
	//find the vertex most distant from start
	//using normal bfs
	//
	vector<ll> dist(n, -1);
	vector<bool> visited(n, false);
	queue<int> to_visit;
	to_visit.push(start);
	visited[start] = true;
	dist[start]  = 0;
	ll local_max = -1;
	while(!to_visit.empty()){
		int cur = to_visit.front();
		to_visit.pop();
		for(auto it = graph[cur].begin(); it != graph[cur].end(); it++){
			pii neigh = *it;
			int next_ver = neigh.first;
			int weight = neigh.second;
			if (!visited[next_ver]){
				to_visit.push(next_ver);
				visited[next_ver] = true;
				dist[next_ver] = dist[cur] + weight;
				if (dist[next_ver] > local_max) { 
					u = next_ver; 
					local_max = dist[next_ver];
				}
			}
		}
	}
	//after bfs we tracked down node 'u', which most distant from 'start', now 
	//run another bfs from 'u', but this time track down the path using diam array 
	for(int i = 0; i < n; i++){
		visited[i] = false;
		dist[i] = -1;
	}
	to_visit.push(u);
	diam[u] = {-1, 0};
	visited[u] = true;
	dist[u] = 0;
	local_max = -1;
	while(!to_visit.empty()){
		int cur = to_visit.front();
		to_visit.pop();
		for(auto it = graph[cur].begin(); it != graph[cur].end(); it++){
			pii neigh = *it;
			int next_ver = neigh.first;
			int weight = neigh.second;
			if (!visited[next_ver]){
				to_visit.push(next_ver);
				visited[next_ver] = true;
				dist[next_ver] = dist[cur] + weight;
				diam[next_ver] = { cur, weight };
				if (dist[next_ver] > local_max) { 
					v = next_ver; 
					local_max = dist[next_ver];
				}
			}
		}		
	}
	return v;
}

int main(int argc, char const *argv[])
{
	int tests;
	cin >> tests;
	for(int i = 0; i < tests; i++){
		int n;
		cin >> n;
		vector<vector<pii>> graph(n); //it is a connected tree to num_edges = n-1
		for(int i = 0; i < n-1; i++){
			int x,y,w;
			cin >> x >> y >> w;
			graph[x-1].push_back({y-1,w});
			graph[y-1].push_back({x-1,w});
		}
		vector<pii> diam(n);
		int cur = diameter(graph, diam);
		ll total = 0;
		while(cur != -1){
			pii pcur = diam[cur];
			cur = pcur.first;
			total += pcur.second;
		}
		ll total_cost = 0;
		if (total > 100)  total_cost = 100;
		if (total > 1000) total_cost = 1000;
		if (total > 10000) total_cost = 10000;
		cout << total_cost << " " << total << endl;
	}
	return 0;
}
