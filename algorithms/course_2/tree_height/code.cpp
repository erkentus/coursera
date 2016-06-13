#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <string>

using namespace std;

typedef pair<int, int> pii;

int tree_height(int root, vector<vector<int>> &edges){
	int res = 1;
	stack<pii> path;
	set<int> visited;
	path.push({1, root});
	visited.insert(root);
	while(!path.empty()){
		pii cur = path.top();
		if (cur.first > res) res = cur.first;
		path.pop();
		for(int i = 0; i < edges[cur.second].size(); i++){
			int nei = edges[cur.second][i];
			bool is_added = visited.find(nei) != visited.end();
			if (!is_added){
				path.push({cur.first+1, nei});
				visited.insert(nei);
			}
		}
	}
	return res;
}

int main(int argc, char const *argv[])
{
	int n;
	int root;
	cin >> n;
	vector<vector<int>> edges(n);
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		if (x != -1){
			edges[i].push_back(x);
			edges[x].push_back(i);
		} else root = i;
	}
	cout << tree_height(root, edges) << endl;
	return 0;
}
