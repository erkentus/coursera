#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <set>
#include <assert.h>

using namespace std;

typedef long long ll;
  
struct node {
  int key;
  ll sum = 0;

  node *left = NULL;
  node *right = NULL;
  node *parent = NULL;
  node(int key, ll sum, node *left, node *right, node *parent): 
    key(key), sum(sum), left(left), right(right), parent(parent) {}
};
class ST{
private:
  /**
   *  Node related methods
   */

  ll get_sum(node *n){
    if (n == NULL) return 0ll;
    return n->sum;
  }
  void set_parent(node *n, node *p){
    if (n != NULL) n->parent = p;
  }
  void update(node *n){
    if (n == NULL) return;
    n->sum = n->key + get_sum(n->left) + get_sum(n->right);
    set_parent(n->left, n);
    set_parent(n->right, n);
  }
  bool has_parent(node *n){
    if (n == NULL) return false;
    if (n->parent == NULL) return false;
    return true;
  }
  bool has_grand_parent(node *n){
    if (n == NULL) return false;
    if (n->parent == NULL) return false;
    if (n->parent->parent == NULL) return false;
    return true;
  }
  bool is_left_child(node *n){
    if (!has_parent(n)) return false;
    node *p = n->parent;
    return p->left == n;
  }
  bool is_right_child(node *n){
    if (!has_parent(n)) return false;
    node *p = n->parent;
    return p->right == n;
  }
  /* end of Node related methods */
  /* Splay Tree related methods*/

  node *root = NULL;
  void small_rotation(node *n){
    /* just pushes node one level up */
    if (!has_parent(n)) return;
    node *parent = n->parent;
    node *grand_parent = parent->parent;
    if (is_left_child(n)){
      node *nr = n->right;
      n->right = parent;
      parent->left = nr;
    } else {
      node *nl = n->left;
      n->left = parent;
      parent->right = nl;
    }
    update(parent);
    update(n);
    n->parent = grand_parent;
    if (grand_parent != NULL){
      if (grand_parent->left == parent) grand_parent->left = n;
      else grand_parent->right = n;
    }
  }
  void big_rotation(node *n){
    if (!has_grand_parent(n)) return;
    if (is_left_child(n) && is_left_child(n->parent)){
      small_rotation(n->parent);
      small_rotation(n);
    }
    else if (is_right_child(n) && is_right_child(n->parent)){
      small_rotation(n->parent);
      small_rotation(n);
    }
    else {
      small_rotation(n);
      small_rotation(n);
    }
  }
  void splay(node *n){
    if (n == NULL) return;
    while(has_parent(n)){
      if (has_grand_parent(n)){
        big_rotation(n);
      }
      else {
        small_rotation(n);
        break;
      }
    }
    root = n;
  }
  /* end of splay tree related methods */
public:
  /** public splay tree methods */
  ST(){}
  ST(node *root): root(root) {}
  ~ST(){}
  /** returns the smallest node bigger or equal to a given key
      and splays deepest node reached
      returns NULL if key is bigger than all elements
   */
  node* find(int key){
    node *v = root;
    node *last = root;
    node *next = NULL;
    while(v != NULL){
      if (v->key >= key && (next == NULL || v->key < next->key)){
        next = v;
      }
      last = v;
      if (v->key == key) break;
      else if (v->key > key) v = v->left;
      else v=v->right;
    }
    splay(last);
    return next;
  }
  /** check if key exists */
  bool exists(int key){
    node *c = find(key);
    return (c != NULL && c->key == key);
  }
  /* splits the tree based on given key, right side will have the key if it exists */
  void split(int key, node* &left, node* &right){
    if (root == NULL){
      left = NULL;
      right = NULL;
      return;
    }
    right = find(key);
    splay(right); //make right the root of the tree
    if (right == NULL){
      /* if biggest element is passed  */
      left = root;
      return;
    }
    left = right->left;
    right->left = NULL;
    set_parent(left, NULL);
    update(left);
    update(right);
  }
  /**
   * merge two trees
   */
  static node* merge(node* left, node* right){
    if (left == NULL) return right;
    if (right == NULL) return left;

    ST rtree(right);
    node *minr = right;
    while(minr->left != NULL){
      minr = minr->left;
    }
    rtree.splay(minr);
    minr->left = left;
    rtree.update(minr);
    return minr;
  }
  /** insert a new key */
  void insert(int key){
    node *left, *right;
    split(key, left, right);
    node *nn = NULL;
    if (right == NULL || right->key != key){
      nn = new node(key, (ll)key, NULL, NULL, NULL);
    }
    root = ST::merge(ST::merge(left, nn), right);
  }
  /** erase the key from the tree */
  void erase(int key){
    node *n = find(key);
    if (n != NULL && n->key == key){
      node *next = find(key+1);
      if (next != NULL){
        splay(next);
        splay(n);
        node *nl = n->left;
        next->left = nl;
        set_parent(next, NULL);
        set_parent(nl, next);
        root = next;
        update(root);
      }
      else {
        splay(n);
        node *nl = n->left;
        root = nl;
        set_parent(nl, NULL);
        splay(root);
      }
    }
  }
  /** sum of elements in range [l, r] */
  ll sum(int l, int r){
    if (l > r) return 0;
    node *left, *middle, *right;
    split(l, left, middle);
    ST mt(middle);
    mt.split(r+1, middle, right);
    ll ans = 0;
    if (middle != NULL) ans += (ll)middle->sum;
    node *nmiddle = ST::merge(left, middle);
    root = ST::merge(nmiddle, right);
    return ans;
  }
  void print(){
    inorder(root);
  }
  void inorder(node *cur){
    if (cur == NULL) return;
    inorder(cur->left);
    inorder(cur->right);
  }
};

const int MODULO = 1000000001;

int main(){
  ios::sync_with_stdio(false);
  // int TEST_CASES = 100;
  // vector<int> types = {'+', '?', '-', 's'};
  // for(int i = 0; i < TEST_CASES; i++){
  //   set<int> vals;
  //   ST t;
  //   const int MAX_LENGTH = 1e5;
  //   const int MAX_INT = 1e2;
  //   int len = rand() % MAX_LENGTH;
  //   ll last_sum_result = 0;
  //   for(int j = 0; j < len; j++){
  //     char type = types[rand() % 4];
  //     switch (type) {
  //       case '+' : {
  //         ll x = rand() % MAX_INT;
  //         vals.insert((x + last_sum_result) % MODULO);
  //         t.insert((x + last_sum_result) % MODULO);
  //       } break;
  //       case '-' : {
  //         ll x = rand() % MAX_INT;
  //         vals.erase((x + last_sum_result) % MODULO);
  //         t.erase((x + last_sum_result) % MODULO);
  //       } break;            
  //       case '?' : {
  //         ll x = rand() % MAX_INT;
  //         bool exist = (vals.find((x + last_sum_result) % MODULO) != vals.end());
  //         bool stexist = t.exists((x + last_sum_result) % MODULO);
  //         if (exist != stexist){
  //           for(auto it = vals.begin(); it != vals.end(); it++){
  //             cout << *it << " ";
  //           }
  //           t.exists(85);
  //           cout << endl;
  //           t.print();
  //         }
  //       } break;
  //       case 's' : {
  //         ll l = rand() % len-1;
  //         ll r = (l == len-1) ? (len-1) : (l + (rand() % (len-l-1)));
  //         long long res = t.sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
  //         long long set_res = 0;
  //         for(auto it = vals.lower_bound((l + last_sum_result) % MODULO); it != vals.upper_bound((r + last_sum_result) % MODULO); it++){
  //           set_res += ll(*it);
  //         }
  //         assert(res==set_res);
  //         last_sum_result = ll(res % MODULO);
  //       }
  //     }      
  //   } 
  // }
  int n;
  scanf("%d", &n);
  int last_sum_result = 0;
  ST t;
  for (int i = 0; i < n; i++) {
    char buffer[10];
    scanf("%s", buffer);
    char type = buffer[0];
    switch (type) {
      case '+' : {
        int x;
        scanf("%d", &x);
        t.insert((x + last_sum_result) % MODULO);
      } break;
      case '-' : {
        int x;
        scanf("%d", &x);
        t.erase((x + last_sum_result) % MODULO);
      } break;            
      case '?' : {
        int x;
        scanf("%d", &x);
        printf(t.exists((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
      } break;
      case 's' : {
        int l, r;
        scanf("%d %d", &l, &r);
        long long res = t.sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
        printf("%lld\n", res);
        last_sum_result = int(res % MODULO);
      }
    }
  }
  return 0;
}