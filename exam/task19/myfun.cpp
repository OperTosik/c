/*
 *  В этот файл Вы можете вставить определения своих функций
 */
#include "tree.h"
#include <map>

/** Нахождение вершины по значению value */
TreeNode* findElem(TreeNode* root, int value) {
    if (root == nullptr) return nullptr;
    if (value == root->value) return root;
    findElem(root->left, value);
    findElem(root->right, value);
}

/** Нахождение  вершины по заданной вершине */
TreeNode* findElem(TreeNode* root, TreeNode* node) {
    if (root == nullptr) return nullptr;
    if (node == root) return root;
    findElem(root->left, node);
    findElem(root->right, node);
}

/** Нахождение общего родителя вершин со значениями a и b (родитель ближайший к вершинам) */
TreeNode* findCommonParent(TreeNode* root, TreeNode* a, TreeNode* b) {
    TreeNode* tmp1 = findElem(root->left, a);
    TreeNode* tmp2 = findElem(root->left, b);
    if (tmp1 != nullptr && tmp2 != nullptr) {
        return findCommonParent(root->left, a, b);
    }
    tmp1 = findElem(root->right, a);
    tmp2 = findElem(root->right, b);
    if (tmp1 != nullptr && tmp2 != nullptr) {
        return findCommonParent(root->right, a, b);
    }
    return root;
}

/** Удаление поддерева, начиная с заданной вершины */
void deleteNode(TreeNode* root) {
    if (root == nullptr) return;
    deleteNode(root->left);
    deleteNode(root->right);
    root = nullptr; 
}

/** Оставлялет ветвь от корня до родителя, остальные удаляет*/
void saveParent(TreeNode* root, TreeNode* parent) {
    if (root == nullptr) return;
    if (root == parent) return;
    if (findElem(root->left, parent) == nullptr) {
        deleteNode(root->left);
        saveParent(root->right, parent);
    }
    if (findElem(root->right, parent) == nullptr) {
        deleteNode(root->right);
        saveParent(root->left, parent);
    }
}

void walkWithDelete(TreeNode* root, TreeNode* a, TreeNode* b) {
    if (root == nullptr) return;
    TreeNode* tmp1 = findElem(root->left, a);
    TreeNode* tmp2 = findElem(root->left, b);
    if (tmp1 != nullptr)
    tmp1 = findElem(root->right, a);
    tmp2 = findElem(root->right, b);
    if (tmp1 == nullptr && tmp2 == nullptr) {
        deleteNode(root->right);
        walkWithDelete(root->left, a, b);
    }
}

/** Начиная с родителя, удаляет все ветви не содержащие вершину a или вершину b 
 *  Оставляет поддревья a и b
*/
void saveNodesWithParents(TreeNode* root, TreeNode* a, TreeNode* b, TreeNode* parent) {
    if (root == nullptr) return;
    if (parent == root) {
        walkWithDelete(root->left, a, b);
        walkWithDelete(root->right, a, b);
        return;
    }
    saveNodesWithParents(root->left, a, b, parent);
    saveNodesWithParents(root->right, a, b, parent);
}