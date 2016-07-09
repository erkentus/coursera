#include <algorithm>
#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;

const int MAX = 1e9+7;
const int MIN = -1e9+7;

//https://habrahabr.ru/post/102364/
struct node{
  char key = 0;
  int p = 0; //priority
  int size = 1; //number of nodes in subtree
  node *left = NULL;
  node *right = NULL;
  node *parent = NULL;
  node(): left(NULL), right(NULL), parent(NULL){
    p = rand() % (int)MAX;
  } 
  node(char key): key(key), left(NULL), right(NULL), parent(NULL){
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
  static void recalc(node *n){
    if (n == NULL) return;
    int total = 1;
    if (n->left != NULL){ 
      total += n->left->size;
    }
    if (n->right != NULL){ 
      total += n->right->size;
    }
    n->size = total;
  }
  static int sizeOf(node *n){
    if (n == NULL) return 0;
    else return n->size;
  }
};

class Treap{
public:
  Treap():root(NULL) {
  }
  Treap(node *root): root(root) {
  }
  ~Treap() { }
  void insert(int x, char key){
    node *l;
    node *r;
    Treap::split(root, x, l, r);
    node *n = new node(key);
    root = Treap::merge(l, n);
    root = Treap::merge(root, r);
  }
  void remove(int x){
    node *l;
    node *r;
    Treap::split(root, x, l, r);
    node *ml;
    node *mr;
    Treap::split(r, 1, ml, mr);
    root = Treap::merge(l, mr);
  }
  node* find_kth(int k){
    node *cur = root;
    while(cur != NULL){
      int size = node::sizeOf(cur->left);
      if (size == k){
        break;
      }
      else if (size > k){
        cur = cur->left;
      } else {
        cur = cur->right;
        k -= size + 1;
      }
    }
    return cur;
  }
  void process(int l, int r){ //same as below with k = 0
    node *ll;
    node *rr;
    Treap::split(root, l, ll, rr);
    // if (root == rr) cout << "is null" << endl;
    node *nll;
    node *nrr;
    Treap::split(rr, r-l+1, nll, nrr);
    root = Treap::merge(nll, ll);
    root = Treap::merge(root, nrr);
  } 
  void process(int l, int r, int k){
    node *ll;
    node *rr;
    Treap::split(root, l, ll, rr);
    node *nll;
    node *nrr;
    Treap::split(rr, r-l+1, nll, nrr);
    if (node::sizeOf(ll) >= k){
      node *nnll;
      node *nnrr;
      Treap::split(ll, k, nnll, nnrr);
      root = Treap::merge(nnll, nll);
      root = Treap::merge(root, nnrr);
      root = Treap::merge(root, nrr);
    }
    else {
      node *nnll;
      node *nnrr;
      Treap::split(nrr, k-node::sizeOf(ll), nnll, nnrr);
      root = Treap::merge(ll, nnll);
      root = Treap::merge(root, nll);
      root = Treap::merge(root, nnrr);
    }
  }
  void traverse(){
    inorder(root);
    cout << endl;
  }
private:
  node *root = NULL;
  static void split(node *cur, int pos, node* &l, node* &r){
    if (cur == NULL) {
      l = NULL;
      r = NULL;
      return;
    }
    int size_left = node::sizeOf(cur->left) + 1;
    if (size_left > pos){
      node *newr = NULL;
      if (cur->left == NULL){
        l = NULL;
      }
      else {
        Treap::split(cur->left, pos, l, newr);
      } 
      node::set_left_parent(newr, cur);
      r = cur;
      node::recalc(r);
    }
    else {
      node *newl = NULL;
      if (cur->right == NULL){
        r = NULL;
      }
      else Treap::split(cur->right, pos-size_left, newl, r);
      node::set_right_parent(newl, cur);
      l = cur;
      node::recalc(l);
    }
  }
  static node* merge(node *l, node *r){
    if (l == NULL) return r;
    if (r == NULL) return l;
    if (l->p > r->p){
      node *right = Treap::merge(l->right, r);
      node::set_right_parent(right, l);
      node::recalc(l);
      return l;
    }
    else {
      node *left = Treap::merge(l, r->left);
      node::set_left_parent(left, r);
      node::recalc(r);
      return r;
    }
    return NULL;
  }
  void inorder(node *cur){
    if (cur == NULL) return;
    inorder(cur->left);
    cout << cur->key << " ";
    inorder(cur->right);
  }
};

int main(int argc, char const *argv[])
{
  ios::sync_with_stdio(false);
  string x;
  cin >> x;
  Treap t;
  for(int i = 0; i < x.length(); i++){
    t.insert(i, x[i]);
  }
  int m;
  cin >> m;
  for(int i = 0; i < m; i++){
    int l,r,k;
    cin >> l >> r >> k;
    t.process(l,r,k);
  }
  t.traverse();
  /* code */
  return 0;
}
