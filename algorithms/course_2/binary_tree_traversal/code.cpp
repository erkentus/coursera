#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct node{
	int key = 0;
	node *left = NULL;
	node *right = NULL;
};

void preorder(node *root){
	if (root == NULL) return;
	cout << root->key << " ";
	preorder(root->left);
	preorder(root->right);
}

void inorder(node *root){
	if (root == NULL) return;
	inorder(root->left);
	cout << root->key << " ";
	inorder(root->right);
}

void postorder(node *root){
	if (root == NULL) return;
	postorder(root->left);
	postorder(root->right);
	cout << root->key << " ";
}

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	vector<node*> nodes;
	for(int i = 0; i < n; i++){
		node *n = new node;
		nodes.push_back(n);
	}
	for(int i = 0; i < n; i++){
		node *n = nodes[i];
		int a, b, c;
		cin >> a >> b >> c;
		n->key = a;
		if (b != -1){
			n->left = nodes[b];
		}
		if (c != -1){
			n->right = nodes[c];
		}
	}
	inorder(nodes[0]);
	cout << endl;
	preorder(nodes[0]);
	cout << endl;
	postorder(nodes[0]);
	cout << endl;
	return 0;
}
	