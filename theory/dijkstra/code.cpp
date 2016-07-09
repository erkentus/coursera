#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;

const ll MAX = (ll) 10e9 + 7;

void dijkstra(int start, const vector<vector<pll>> &graph, vector<ll> &min_dist){
	int n = graph.size();
	auto comp = [](const pll &a, const pll &b) -> bool {
		return a.second > b.second;
	};
	priority_queue<pll, vector<pll>, decltype(comp)> q(comp);
	q.push({start, 0});
	min_dist[start] = 0;
	while(!q.empty()){
		pll cur = q.top();
		q.pop();
		int ver = cur.first;
		int weight = cur.second;
		for(auto it = graph[ver].begin(); it != graph[ver].end(); it++){
			pll next = *it;
			ll next_ver = next.first;
			ll next_weight = next.second;
			if (min_dist[next_ver] > min_dist[ver] + next_weight){
				min_dist[next_ver] = min_dist[ver] + next_weight;
				q.push({next_ver, min_dist[next_ver]});
			}
		}
	}
}

void dijkstra_set(int start, const vector<vector<pll>> &graph, vector<ll> &min_dist){
	int n = graph.size();
	auto comp = [](const pll &a, const pll &b) -> bool {
		return a.second > b.second;
	};
	set<pll, decltype(comp)> q(comp);
	q.insert({start, 0});
	min_dist[start] = 0;
	while(!q.empty()){
		pll cur = *(q.begin());
		q.erase(q.begin());
		int ver = cur.first;
		int weight = cur.second;
		for(auto it = graph[ver].begin(); it != graph[ver].end(); it++){
			pll next = *it;
			ll next_ver = next.first;
			ll next_weight = next.second;
			if (min_dist[next_ver] > min_dist[ver] + next_weight){
				q.erase({next_ver, min_dist[next_ver]});
				min_dist[next_ver] = min_dist[ver] + next_weight;
				q.insert({next_ver, min_dist[next_ver]});
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	vector<vector<pll>> graph(n);
	for(int i = 0; i < m; i++){
		ll x,y,w;
		cin >> x >> y >> w;
		graph[x-1].push_back({y-1, w}); //this is a directed graph
	}
	int start, end;
	cin >> start >> end;
	vector<ll> min_dist(n, MAX);
	dijkstra_set(start-1, graph, min_dist);
	if (min_dist[end-1] != MAX) cout << min_dist[end-1] << endl;
	else cout << -1 << endl;
	return 0;
}
