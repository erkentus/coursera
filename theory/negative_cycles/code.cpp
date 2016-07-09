#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <limits>


using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll,ll> pll;

struct edge{
	int from;
	int to;
	ll weight;
	edge(int from, int to, ll weight):from(from), to(to), weight(weight) { }
};
/**
 * writes into min_dist minimum distance from node "from"
 * if it equals MAX then unreachable
 * if it is inside in_negative then the distance can be made infinitely small due to 
 * negative cycle
 * @param from        [description]
 * @param edges       [description]
 * @param in_negative [description]
 * @param min_dist    [description]
 */

const ll MAX = numeric_limits<long long>::max()-1e10;

void bellman_ford(int from, const vector<edge*> &edges, set<int> &in_negative, vector<ll> &min_dist){
	min_dist[from] = 0ll;
	int n = min_dist.size();
	for(int i = 0; i < n; i++){
		bool relaxed = false; 
		for(int j = 0; j < edges.size(); j++){
			edge *e = edges[j];
			int from = e->from;
			int to = e->to;
			ll weight = e->weight;
			if (min_dist[from] != MAX && min_dist[to] > min_dist[from] + weight){
				relaxed = true;
				min_dist[to] = min_dist[from] + weight;
				if (i == n-1){
					in_negative.insert(from);
				}
			}
		}
		if (!relaxed) break;
	}
}


int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	vector<edge*> edges;
	vector<vector<pii>> graph(n); //this is to run bfs
	for(int i = 0; i < m; i++){
		int a,b;
		ll c;
		cin >> a >> b >> c;
		edge *e = new edge(a-1,b-1,c);
		edges.push_back(e);
		graph[a-1].push_back({b-1, c});
	}
	int start;
	cin >> start;
	start--; //input uses 1-indexing, we use 0-indexing
	set<int> in_negative;
	vector<ll> min_dist(n, MAX);
	bellman_ford(start, edges, in_negative, min_dist);
	//now in_negative stores the set of nodes in negative cycle
	//now need to find all nodes reachable from the cycle
	vector<bool> visited(n, false);
	queue<int> to_visit;
	for(auto it = in_negative.begin(); it != in_negative.end(); it++){
		to_visit.push(*it);
		visited[*it] = true;
	}
	while(!to_visit.empty()){
		int cur = to_visit.front();
		to_visit.pop();
		for(auto it = graph[cur].begin(); it != graph[cur].end(); it++){
			pii p = *it;
			int neigh = p.first;
			if (!visited[neigh]) {
				to_visit.push(neigh);
				visited[neigh] = true;
			}
		}
	}
	for(int i = 0; i < n; i++){
		if (min_dist[i] == MAX){
			cout << "*" << endl;
		}
		else if (visited[i]){
			cout << "-" << endl;
		}
		else cout << min_dist[i] << endl;
	}
	/* code */
	return 0;
}
