#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

struct node{
	int key;
	unsigned char height = 0; //c++11
	node *parent = NULL;
	node *left = NULL;
	node *right = NULL;
};

class BST //binary search tree with no duplicated key
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
public:
	BST();
	~BST();
	void insert(int key){
		node *n = new node;
		n->key = key;
		if (root == NULL){
			root = n;
			return;
		}
		node *parent = find(root, n->key);
		if (parent->key > n->key){
			parent->left = n;
			n->parent = parent;
		}
		else if (parent->key < n->key){
			parent->right = n;
			n->parent = parent;
		}
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
};

BST::BST(){

}

BST::~BST(){

}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	BST tree;
	tree.insert(6);
	tree.insert(5);
	tree.insert(7);
	tree.del(6);
	vector<node*> q = tree.find(5, 8);
	for(auto i = q.begin(); i != q.end(); i++){
		cout << (*i)->key << endl;
	}
	return 0;
}
