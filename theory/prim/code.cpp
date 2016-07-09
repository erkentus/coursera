#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;

const ll lMAX = 1e18;
const int MAX = 1e9;
const double dMAX = static_cast<double>(lMAX);

/** undirected graph */
void prim(const vector<vector<pil>> &graph, vector<vector<pil>> &mst){
	assert(mst.size() == graph.size());

	int n = graph.size();
	int start = 0;
	auto comp = [](const pii &a, const pii &b) -> bool{
		return a.first > b.first;
	};
	priority_queue<pii, vector<pii>, decltype(comp)> q(comp);

	/** complementary data structures */
	vector<int> cost(n, MAX);
	vector<bool> visited(n, false);
	vector<int> parent(n, -1);

	/** init procedure */
	cost[start] = 0;
	q.push({0, start});
	parent[start] = start; //root of the mst 

	while(!q.empty()){
		pii cur = q.top();
		q.pop();
		int cur_ver = cur.second;
		if (visited[cur_ver]) continue;
		visited[cur_ver] = true;
		int par = parent[cur_ver];
		assert(par != -1);
		mst[cur_ver].push_back({par, cur.first});
		mst[par].push_back({cur_ver, cur.first});
		for(auto it = graph[cur_ver].begin(); it != graph[cur_ver].end(); it++){
			pil neigh = *it;
			int next_ver = neigh.first;
			int weight = neigh.second;
			if (!visited[next_ver] && cost[next_ver] > weight){
				parent[next_ver] = cur_ver;
				cost[next_ver] = weight;
				q.push({cost[next_ver], next_ver});
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	vector<vector<pil>> graph(n);
	for(int i = 0; i < m; i++){
		int x,y,w;
		cin >> x >> y >> w;
		graph[x-1].push_back({y-1,w});
		graph[y-1].push_back({x-1,w});
	}
	vector<vector<pil>> mst(n);
	prim(graph, mst);
	ll total = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < mst[i].size(); j++){
			total += mst[i][j].second;
		}
	}
	total /= 2;
	cout << total;
	return 0;
}
