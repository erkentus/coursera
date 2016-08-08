#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

struct node{
	int start;
	int len;
	vector<node*> edges;
	bool tag;
	node(){};
	node(int start, int len, bool tag=false): start(start), len(len), tag(tag){
	};
	~node(){

	};
};	

class SuffixTree
{
private:
	int size;
	node *root;
	void add_prefix(const string &x, const int from, node *cur){
		int match = -1;
		for(int i = 0; i < cur->edges.size(); i++){
			int start = cur->edges[i]->start;
			if (x[start] == x[from]){
				match = i;
			}
		}
		if (match == -1){
			node *n = new node(from, size-from);
			cur->edges.push_back(n);
		}
		else {
			int i = match;
			int len = cur->edges[i]->len;
			int start = cur->edges[i]->start;
			int bp = 1;
			while(bp < len){
				if (x[start + bp] != x[from+bp]) break;
				bp++;
			}
			if (bp == len){
				add_prefix(x, from+bp, cur->edges[i]);
			}
			else {
				node *n = new node(from+bp, size-from-bp);
				node *np = new node(start, bp);
				node *nc = new node(start+bp, len-bp);
				nc->edges = cur->edges[i]->edges;
				np->edges.push_back(nc);
				np->edges.push_back(n);
				cur->edges[i] = np;
			}
		}
	}
	int calc_match(const string &x, const string &y, const int from, node *cur, bool &pmatch){
		int match = -1;
		for(int i = 0; i < cur->edges.size(); i++){
			int start = cur->edges[i]->start;
			if (x[start] == y[from]){
				match = i;
			}
		}
		if (match == -1){
			return 1;
		}
		else {
			int i = match;
			int len = cur->edges[i]->len;
			int start = cur->edges[i]->start;
			int bp = 1;
			while(bp < min({len, static_cast<int>(y.length()) - from})){
				if (x[start + bp] != y[from+bp]) break;
				bp++;
			}
			if (bp == len && bp < static_cast<int>(y.length()) - from){
				return bp + calc_match(x, y, from+bp, cur->edges[i], pmatch);
			}
			else {
				if (bp == static_cast<int>(y.length()) - from) pmatch = true;
				return bp + 1;
			}
		}
	}

	void traverse(const string &x, node *cur){
		if (cur != root){
			cout << x.substr(cur->start, cur->len) << endl;
		}
		for(int i = 0; i < cur->edges.size(); i++){
			traverse(x, cur->edges[i]);
		}
	}
public:
	SuffixTree(const string &x){
		root = new node();
		size = x.length();
		for(int i = 0; i < size; i++){
			add_prefix(x, i, root);
		}
	}
	~SuffixTree(){}
	void print(const string &x){
		traverse(x, root);
	}
	int max_match(const string &x, const string &y, int from, bool &pmatch){
		return calc_match(x,y,from, root,pmatch);
	}
};

int main(int argc, char const *argv[])
{
	string x,y;
	cin >> x >> y;
	y += '$';
	SuffixTree t(y); 
	int m = 1e9;
	int from = -1;
	for(int i = 0; i < x.length(); i++){
		bool pmatch = false;
		int match = t.max_match(y,x,i,pmatch);
		if (!pmatch && match < m) {
			m = match;
			from = i;
		}
	}
	cout << x.substr(from, m) << endl;
	return 0;
}
