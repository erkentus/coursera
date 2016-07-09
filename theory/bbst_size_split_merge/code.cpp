#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

struct node{
	int key;
	int height = 0; //c++11
	int size = 0;
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
	int get_size(node *n){
		if (n == NULL) return 0;
		return n->size;
	}
	void adjust_size(node *n){
		if (n != NULL) n->size = 1 + get_size(n->left) + get_size(n->right);
	}
	node* find(node* n, int key){
		if (n == NULL) return NULL;
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
		adjust_size(x);
		adjust_height(a);
		adjust_size(a);
		adjust_height(p);
		adjust_size(p);

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
		adjust_size(x);
		adjust_height(b);
		adjust_size(b);
		adjust_height(p);
		adjust_size(p);
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
		adjust_size(n);
		if (p != NULL){
			rebalance(p);
		}
	}
public:
	AVL();
	AVL(node *root);
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
		if (n == NULL || n->key != key) return;
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
		cout << cur->key << " " << cur->size << endl;
		if (cur->left != NULL) PREORDER(cur->left);
		if (cur->right != NULL) PREORDER(cur->right);
	}
	node* get_root(){
		return root;
	}
	node* largest(){
		if (root == NULL) return NULL;
		node *cur = root;
		while(cur->right != NULL){
			cur = cur->right;
		}
		return cur;
	}
	node* find(int key){
		if (root == NULL) return NULL;
		node *cand = find(root, key);
		if (cand != NULL && cand->key == key) return cand;
		return NULL;
	}
	pair<node*, node*> split(node *cur, int key){
		if (cur == NULL) return {NULL, NULL};
		if (key < cur->key){
			pair<node*, node*> spl = split(cur->left, key);
			node *r1 = spl.first;
			node *r2=  spl.second;
			node *r3 = AVL::merge_with_root(r2, cur->right, cur);
			return {r1, r3};
		}
		else if (key > cur->key) {
			pair<node*, node*> spl = split(cur->right, key);
			node *r1 = spl.first;
			node *r2=  spl.second;
			node *r3 = AVL::merge_with_root(cur->left, r1, cur);
			return {r3, r2};
		}
		else {
			node *cr = cur->right;
			if (cr != NULL) cr->parent = NULL;
			node *r1 = AVL::merge_with_root(cur->left, NULL, cur);
			return {r1, cr};
		}
	}
	static int node_height(node *n){
		if (n == NULL) return 0;
		else return n->height;		
	}
	static int node_size(node *n){
		if (n == NULL) return 0;
		return n->size;
	}
	static node* merge_with_root(node *t1, node *t2, node *new_root){
		if (node_height(t1) - node_height(t2) >= -1 && node_height(t1) - node_height(t2) <= 1){
			new_root->left = t1;
			new_root->right = t2;
			if (t1 != NULL) t1->parent = new_root;
			if (t2 != NULL) t2->parent = new_root;
			int h = max({node_height(t1), node_height(t2)});
			new_root->height = 1 + h;
			new_root->size = 1 + node_size(t1) + node_size(t2);
			new_root->parent = NULL;
			return new_root;
		}
		else if (node_height(t1) - node_height(t2) < -1) {
			node *r = merge_with_root(t1, t2->left, new_root);
			t2->left = r;
			r->parent = t2;
			AVL tree(t2);
			t2->parent = NULL;
			tree.rebalance(t2);
			return t2;
		}
		else {
			node *r = merge_with_root(t1->right, t2, new_root);
			t1->right = r;
			r->parent = t1;
			AVL tree(t1);
			t1->parent = NULL;
			tree.rebalance(t1);
			return t1;
		}
	}
	static node* merge(node *t1, node *t2){
		if (t1 == NULL || t2 == NULL) return NULL;
		if (t1->key > t2->key) swap(t1, t2);
		AVL T1(t1);
		AVL T2(t2);
		node *m1 = T1.largest();
		T1.del(m1->key);
		return merge_with_root(t1, t2, m1);
	}
};


AVL::AVL(){

}

AVL::AVL(node *root){
	this->root = root;
}

AVL::~AVL(){

}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	AVL tree1;
	tree1.insert(6);
	tree1.insert(5);
	tree1.insert(7);
	tree1.insert(16);
	tree1.insert(15);
	tree1.insert(17);
	tree1.insert(26);
	tree1.insert(25);
	tree1.insert(27);

	AVL tree2;
	tree2.insert(2);
	tree2.insert(4);
	tree2.insert(1);
	node *r1 = tree1.get_root();
	node *r2 = tree2.get_root();
	node *new_root = AVL::merge(r2, r1); //modifies both trees
	AVL tree(new_root);
	tree.PREORDER(tree.get_root());
	cout << " ___ " << endl;
	pair<node*, node*> spl = tree.split(tree.get_root(), 14);
	AVL spl1(spl.first);
	AVL spl2(spl.second);
	node *new_new_root = AVL::merge(spl1.get_root(), spl2.get_root());
	AVL new_tree(new_new_root);
	new_tree.PREORDER(new_tree.get_root());
	// spl1.PREORDER(spl1.get_root());
	// spl2.PREORDER(spl2.get_root());
	// vector<node*> q = tree1.find(20, 28);
	// for(auto i = q.begin(); i != q.end(); i++){
	// 	cout << (*i)->key << endl;
	// }
	return 0;
}
