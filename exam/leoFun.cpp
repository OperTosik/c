/*
 *  В этот файл Вы можете вставить определения своих функций
 */
#include "tree.h"

void Balance(Tree& tr) {
	makeBalance(tr.root);
}

void makeBalance(TreeNode* node) {
	if (!node) return;
	else if (!node->right && !node->left) node->balance = 0;
	else if (!node->left) node->balance = 3;
	else if (!node->right) node->balance = -3;
	else if (node->left->value <= node->value) {
		if (node->right->value <= node->value) node->balance = 2;
		else node->balance = 1;
	} else {
		if (node->right->value <= node->value) node->balance = -1;
		else node->balance = -2;
	}
	makeBalance(node->left);
	makeBalance(node->right);
}

	bool find(TreeNode *tr, int val, TreeNode*& res) {
		if (!tr) return false; 
		bool f1 = false, f2 = false;
		if (tr->value == val) {res = tr; return true;}
		f1 = find(tr->left, val, res); f2 = find(tr->right, val, res);
		return f1 || f2;	
	}

bool find(TreeNode* tr, TreeNode* x) {
	if (!tr) return false;
	if (tr == x) return true;
	bool f1 = find(tr->left, x), f2 = find(tr->right, x);
	return f1||f2;	
}

TreeNode* commonParent(TreeNode* a, TreeNode* b, TreeNode* root) {
		bool f1 = find(root->left, a) && find(root->left, b),
		     f2 = find(root->right, a) && find(root->right, b);
		if (f1) return commonParent(a, b, root->left);
		if (f2) return commonParent(a, b, root->right);
		return root;
	}
void Del(TreeNode* root) {
	if (!root) return;
	Del(root->left); Del(root->right);
	delete root;
}

void clear(TreeNode* root, TreeNode* p, TreeNode* a, TreeNode* b) {
	TreeNode* pos = root;
	while (pos != p) {
		if (find(pos->left, p)) {
			Del(pos->right); pos->right = nullptr;
			pos = pos->left;
		} else {
			Del(pos->left); pos->left = nullptr;
			pos = pos->right;
		}
	}
	if (find(p->left, a)) {
		pos = p->left;
		while (pos != a) {
			if (find(pos->left, a)) {
						Del(pos->right); pos->right = nullptr;
						pos = pos->left;
				} else {
						Del(pos->left); pos->left = nullptr;
						pos = pos->right;
				}
		}	
		pos = p->right;
		while (pos != b) {
				if (find(pos->left, b)) {
						Del(pos->right); pos->right = nullptr;
						pos = pos->left;
				} else {
						Del(pos->left); pos->left = nullptr;
						pos = pos->right;
				}
		}
	} else {
		pos = p->right;
		while (pos != a) {
			if (find(pos->left, a)) {
				Del(pos->right); pos->right = nullptr;
				pos = pos->left;
			} else {
				Del(pos->left); pos->left = nullptr;
				pos = pos->right;
			}
		}
				
		pos = p->left;
		while (pos != b) {
			if (find(pos->left, b)) {
				Del(pos->right); pos->right = nullptr;
				pos = pos->left;
			} else {
				Del(pos->left); pos->left = nullptr;
				pos = pos->right;
			}
		}       
	}       

}



