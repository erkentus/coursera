#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

struct node{
	int start;
	int len;
	vector<node*> edges;
	node(){};
	node(int start, int len): start(start), len(len){

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
};

int main(int argc, char const *argv[])
{
	string x;
	cin >> x;
	SuffixTree t(x);
	t.print(x);
	return 0;
}
