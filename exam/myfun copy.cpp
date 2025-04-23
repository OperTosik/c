/*
 *  В этот файл Вы можете вставить определения своих функций
 */
#include "tree.h"
#include <map>
#include <cassert>

TreeNode* balance(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    else {
        if (root->left != nullptr) {
            root->balance += root->left->balance + root->left->value - 1;
        }
        if (root->right != nullptr) {
            root->balance += root->right->balance + root->right->value - 1;
        }
    }
    balance(root->left);
    balance(root->right);
    return nullptr;
}

void removeLeftSubtree(
    TreeNode* t
) {
    assert(t != nullptr);
    if(t -> left == nullptr)
        return;
    if(t -> left -> left == nullptr && t -> left -> right == nullptr) { 
        delete t -> left;
    } else {
        removeLeftSubtree(t -> left);
        removeRightSubtree(t -> left);
        delete t -> left;
    } 
    t -> left = nullptr;
}

void removeRightSubtree(
    TreeNode* t
) {
    assert(t != nullptr);
    if(t -> right == nullptr)
        return;
    if(t -> right -> left == nullptr && t -> right -> right == nullptr) { 
        delete t -> right;
    } else {
        removeLeftSubtree(t -> right);
        removeRightSubtree(t -> right);
        delete t -> right;
    } 
    t -> right = nullptr;
}

TreeNode* walkWithDelete(TreeNode* root, int x) {
    if (root == nullptr) return nullptr;
    if (root->value == x) {
        removeLeftSubtree(root);
        return root;
    }
    if (root->value < x) {
        removeLeftSubtree(root);
        removeRightSubtree(root);
        return root;
    }
    walkWithDelete(root->left, x);
    walkWithDelete(root->right, x);
    return nullptr;
   
}