#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct node{
	char v;
	int label;
	vector<node*> edges;
	node(char v, int label):v(v), label(label){

	}
	node(int label):label(label){

	}
	bool is_leaf(){
		bool find = false;
		for(int i = 0; i < edges.size(); i++){
			find = find || edges[i]->v == '$';
		}
		return find;
	}
};

class Trie
{
public:
	void match(const string &text){
		for(int i = 0; i < text.length(); i++){
			match_prefix(text, i);
		}
		cout << endl;
	}
	void add(const string &x){
		node *cur = root;
		for(int i = 0; i < x.length(); i++){
			char cur_c = x[i];
			bool found = false;
			for(int j = 0; j < cur->edges.size(); j++){
				node* next = cur->edges[j];
				if (next->v == cur_c){
					found = true;
					cur = next;
					break;
				}
			}
			if (!found){
				size++;
				node *next = new node(x[i], size);
				cur->edges.push_back(next);
				cur = next;
			}
		}
		cur->edges.push_back(new node('$', -1));
	}
	Trie(){
		root = new node(0); 
	};
	~Trie(){

	};
	void print(){
		traverse(root);
	}
private:
	node *root;
	int size;
	void traverse(node *cur){
		for(int i = 0; i < cur->edges.size(); i++){
			cout << cur->label << "->" << cur->edges[i]->label << ":" << cur->edges[i]->v << endl;
			traverse(cur->edges[i]);
		}
	}
	void match_prefix(const string &text, int from){
		bool match = false;
		node *cur = root;
		for(int i = from; i < text.length(); i++){
			bool found = false;
			for(int j = 0; j < cur->edges.size(); j++){
				if (cur->edges[j]->v == text[i]){
					cur = cur->edges[j];
					found = true;
					break;
				}
			}
			if (!found) break;
			if (cur->is_leaf()){
				match = true;
				break;
			}
		}
		if (match) cout << from << " ";
	}
};

int main(int argc, char const *argv[])
{
	string text;
	cin >> text;
	int n;
	cin >> n;
	Trie t;
	for(int i = 0; i < n; i++){
		string x;
		cin >> x;
		t.add(x);
	}
	t.match(text);
	return 0;
}
