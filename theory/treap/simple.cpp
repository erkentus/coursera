#include <algorithm>
#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;

const int MAX = 1e9+7;

struct node{
	int key = 0;
	int p = 0; //priority
	node *left = NULL;
	node *right = NULL;
	node *parent = NULL;
	node(): left(NULL), right(NULL), parent(NULL){
		p = rand() % (int)MAX;
	}	
	node(int key): key(key), left(NULL), right(NULL), parent(NULL){
		p = rand() % (int)MAX;
	}
	static void set_right_parent(node *child, node *parent){
		if (parent == NULL) return;
		parent->right = child;
		if (child != NULL) child->parent = parent;
	}	
	static void set_left_parent(node *child, node *parent){
		if (parent == NULL) return;
		parent->left = child;
		if (child != NULL) child->parent = parent;
	}
};

class Treap{
public:
	Treap():root(NULL) {
	}
	Treap(node *root): root(root) {
	}
	~Treap() { }
	void insert(int x){
		node *l;
		node *r;
		Treap::split(root, x, l, r);
		node *n = new node(x);
		root = Treap::merge(l, n);
		root = Treap::merge(root, r);
	}
	void traverse(){
		inorder(root);
	}
private:
	node *root = NULL;
	static void split(node *cur, int key, node* &l, node* &r){
		if (cur == NULL) {
			l = NULL;
			r = NULL;
			return;
		}
		if (cur->key > key){
			node *newr = NULL;
			if (cur->left == NULL){
				l = NULL;
			}
			else {
				Treap::split(cur->left, key, l, newr);
			}	
			node::set_left_parent(newr, cur);
			r = cur;
		}
		else {
			node *newl = NULL;
			if (cur->right == NULL){
				r = NULL;
			}
			else Treap::split(cur->right, key, newl, r);
			node::set_right_parent(newl, cur);
			l = cur;
		}
	}
	static node* merge(node *l, node *r){
		if (l == NULL) return r;
		if (r == NULL) return l;
		if (l->key > r->key) swap(l, r);
		if (l->p > r->p){
			node *right = Treap::merge(l->right, r);
			node::set_right_parent(right, l);
			return l;
		}
		else {
			node *left = Treap::merge(l, r->left);
			node::set_left_parent(left, r);
			return r;
		}
		return NULL;
	}
	void inorder(node *cur){
		if (cur == NULL) return;
		inorder(cur->left);
		cout << cur->key << endl;
		inorder(cur->right);
	}
};

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	Treap t;
	t.insert(10);
	t.insert(20);
	t.insert(30);
	t.insert(40);
	t.insert(50);
	t.traverse();
	/* code */
	return 0;
}
