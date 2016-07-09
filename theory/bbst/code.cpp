#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

struct node{
	int key;
	int height = 0; //c++11
	node *parent = NULL;
	node *left = NULL;
	node *right = NULL;
};

class AVL //balanced binary search tree with no duplicated key
{
private:
	node *root = NULL;
	int height(node *n){
		if (n == NULL) return 0;
		else return n->height;
	}
	node* find(node* n, int key){
		if (n->key == key) return n;
		else if (n->key > key){
			if (n->left == NULL){
				return n;
			}
			return find(n->left, key);
		}
		else{
			if (n->right == NULL){
				return n;
			}
			return find(n->right, key);
		}
	}
	node* right_ancestor(node *n){
		node *p = n->parent;
		if (p == NULL) return NULL;
		if (p->key > n->key) return p;
		else return right_ancestor(p);
	}
	node* next(node *n){
		if (n->right != NULL){
			node *r = n->right;
			while(r->left != NULL){
				r = r->left;
			}
			return r;
		}
		else {
			return right_ancestor(n);
		}
	}
	void rotate_right(node *x){
		if (x == NULL) return;
		node *p = x->parent;
		node *a = x->left;
		node *ar = a->right;
		if (p != NULL){
			if (p->key < x->key){
				p->right = a;
			} else p->left = a;
		}
		else {
			root = a;
		}
		a->parent = p;
		a->right = x;
		x->parent = a;
		x->left = ar;
		adjust_height(x); 
		adjust_height(a); 
		adjust_height(p); 
		if (ar != NULL) ar->parent = x;
	}
	void rotate_left(node *x){
		if (x == NULL) return;
		node *p = x->parent;
		node *b = x->right;
		node *bl = b->left;
		if (p != NULL){
			if (p->key < x->key){
				p->right = b;
			} else p->left = b;
		}
		else {
			root = b;
		}
		b->parent = p;
		b->left = x;
		x->parent = b;
		x->right = bl;
		adjust_height(x);
		adjust_height(b);
		adjust_height(p);
		if (bl != NULL) bl->parent = x;		
	}
	void adjust_height(node *x){
		if (x == NULL) return;
		int h = max({height(x->left), height(x->right)});
		x->height = 1 + h;
	}
	void rebalance_right(node *n){
		node *m = n->left;
		if (height(m->right) > height(m->left)){
			rotate_left(m);
		}
		rotate_right(n);
	}
	void rebalance_left(node *n){
		node *m = n->right;
		if (height(m->left) > height(m->right)){
			rotate_right(m);
		}
		rotate_left(n);
	}
	void rebalance(node *n){
		if (n == NULL) return;
		node *p = n->parent;
		if (height(n->left) > height(n->right)+1){
			rebalance_right(n);
		}
		else if (height(n->right) > height(n->left)+1){
			rebalance_left(n);
		}
		adjust_height(n);
		if (p != NULL){
			rebalance(p);
		}
	}
public:
	AVL();
	~AVL();
	void insert(int key){
		node *n = new node;
		n->key = key;
		if (root == NULL){
			root = n;
			root->height = 1;
			return;
		}
		node *parent = find(root, n->key);
		if (parent->key == n->key){
			return;
		}
		else if (parent->key > n->key){
			parent->left = n;
			n->parent = parent;
		}
		else if (parent->key < n->key){
			parent->right = n;
			n->parent = parent;
		}
		n->height = 1;
		rebalance(n);
	}
	void del(int key){
		node *n = find(root, key);
		if (n->key != key) return;
		node *parent = n->parent;
		if (n->right == NULL){
			if (n->left != NULL) n->left->parent = parent;
			if (parent == NULL){
				root = n->left;
			}
			else if (n->key > parent->key){
				parent->right = n->left;
			}
			else parent->left = n->left;
			if (parent != NULL) {
				adjust_height(parent);
				rebalance(parent);
			}
		}
		else {
			node *x = next(n); // not NULL because n->right is not NULL
			n->key = x->key;
			node *px = x->parent;
			if (px->key > x->key){
				px->left = x->right;
			}
			else {
				px->right = x->right;
			}
			if (x->right != NULL) x->right->parent = px;
			adjust_height(px);
			rebalance(px);
		}
	}
	vector<node*> find(int l, int r){
		vector<node*> res;
		if (root == NULL) return res;
		node *n = find(root, l);
		while(n != NULL && n->key <= r){
			if (n->key >= l){
				res.push_back(n);
			}
			n = next(n);
		}
		return res;
	}
	void PREORDER(node *cur){
		if (cur == NULL) cur = root;
		cout << cur->key << endl;
		if (cur->left != NULL) PREORDER(cur->left);
		if (cur->right != NULL) PREORDER(cur->right);
	}
};

AVL::AVL(){

}

AVL::~AVL(){

}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	AVL tree;
	tree.insert(6);
	tree.insert(5);
	tree.insert(7);
	tree.insert(16);
	tree.insert(15);
	tree.insert(17);
	tree.insert(26);
	tree.insert(25);
	tree.insert(27);
	tree.PREORDER(NULL);
	// vector<node*> q = tree.find(20, 28);
	// for(auto i = q.begin(); i != q.end(); i++){
	// 	cout << (*i)->key << endl;
	// }
	return 0;
}
