/*
 *  В этот файл Вы можете вставить определения своих функций
 */
#include "tree.h"
#include <map>
#include <cassert>

TreeNode* findNode(
    TreeNode* t,
    int value
) {
    if(t == nullptr)
        return nullptr;
    if(t -> value == value)
        return t;
    TreeNode* res = nullptr;
    if(t -> left != nullptr) {
        res = findNode(t -> left, value);
        if(res != nullptr)
            return res;
    }
    if(t -> right != nullptr) {
        res = findNode(t -> right, value);
        if(res != nullptr)
            return res;
    }
    return res;
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

bool isLeaf(const TreeNode* t) {
    return (t->left == nullptr && t->right == nullptr);
}

void makeSubtreesEqual(
    TreeNode* t1,
    TreeNode* t2
) {
    assert(t1 != nullptr && t2 != nullptr);
    if(isLeaf(t1)) {
        removeLeftSubtree(t2);
        removeRightSubtree(t2);
        return;
    }
    if(isLeaf(t2)) {
        removeLeftSubtree(t1);
        removeRightSubtree(t1);
        return;
    }
    if(t1 -> left == nullptr) {
        removeLeftSubtree(t2);
    } else if(t2 -> left == nullptr) {
        removeLeftSubtree(t1);
    } else makeSubtreesEqual(t1 -> left, t2 -> left);
    
    if(t1 -> right == nullptr) {
        removeRightSubtree(t2);
    } else if(t2 -> right == nullptr) {
        removeRightSubtree(t1);
    } else makeSubtreesEqual(t1 -> right, t2 -> right);
}

/////////////////////////////////////////////////////////////////////////////////////////////

/** Нахождение  вершины по заданной вершине */
TreeNode* findElem(TreeNode* root, TreeNode* node) {
    if (root == nullptr) return nullptr;
    if (node == root) return root;
    TreeNode* res = nullptr;
    res = findElem(root->left, node);
    if (res != nullptr) return res;
    res = findElem(root->right, node);
    if (res != nullptr) return res;
    return res;
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

/////////////////////////////////////////////////////////////////////////////////////////////

/** Вставить в tmain.cpp
 *  std::map<TreeNode*, int> array;
 */

/** Нахождение минимальной концевой вершины, начиная с заданной вершины
 *  Искомая вершина сохраняется в min
*/
void findMinimumElem(TreeNode* root, TreeNode* min) {
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        if (min == nullptr) min = root;
        if (min->value > root->value) min = root;
    }
    findMinimumElem(root->left, min);
    findMinimumElem(root->right, min);
}

/** Создает список пар (TreeNode*, int), состоящий из вершин поддеревьев,
 * таких что минимальная концевая вершина кратна N
 */
void generatePairs(TreeNode* root, TreeNode* min, std::map<TreeNode*, int> array, int N) {
    if (root == nullptr) return;
    findMinimumElem(root, min);
    if (min->value % N == 0){
        array[root] = min->value;
    }
    generatePairs(root->left, min, array, N);
    generatePairs(root->right, min, array, N);
}

/** Короче 14 задача */
std::map<TreeNode*, int> maximumPairs(std::map<TreeNode*, int> array) {
    std::map<TreeNode*, int> res;
    int max;
    bool flag = false;
    for (const auto& pair : array) {
        if (flag) {
            max = pair.second;
            flag = false;
        }
        if (max < pair.second) max = pair.second;
    }
    for (const auto& pair : array) {
        if (pair.second == max) res.insert(pair);
    }
    return res;
}

/////////////////////////////////////////////////////////////////////////////////////////////

/** Задача 4 */
/** Возвращает концевой узел самой длинной ветки
 *  Также в tmain.cpp надо будет инициализовать node1
*/
void findLongestBranch(TreeNode* root, TreeNode* node) {
    static int max = 0, tmp = 0;
    ++tmp;
    if (root == nullptr) {
        --tmp;
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        if (max < tmp) {
            max = tmp;
            node = root;
        }
        --tmp;
        return;
    }
    findLongestBranch(root->left, node);
    findLongestBranch(root->right, node);
    --tmp;
}

/** Удаляет концевой узел самой длиной ветви */
void deleteTerminalNode(TreeNode* root, TreeNode* node) {
    if (root == nullptr) return;
    if (root->left == node) {
        removeLeftSubtree(root);
    }
    if (root->right == node) {
        removeRightSubtree(root);
    }
    deleteTerminalNode(root->left, node);
    deleteTerminalNode(root->right, node);
}

/** Возвращает концевой узел самой короткой ветки
 *  Также в tmain.cpp надо будет инициализовать node2
*/
void findShortestBranch(TreeNode* root, TreeNode* node) {
    static int min = 0, tmp = 0;
    ++tmp;
    if (root == nullptr) {
        --tmp;
        if (min > tmp) {
            min = tmp;
            node = root;
        }
        return;
    }
    findShortestBranch(root->left, node);
    findShortestBranch(root->right, node);
    --tmp;
}

/** Вставляет узел в конец самой короткой ветви */
void insertTerminalNode(TreeNode* root, TreeNode* node) {
    if (root == nullptr) return;
    if (root == node && root->left == nullptr && root->right == nullptr) {
        root->left = node;
    }
    insertTerminalNode(root->left, node);
    insertTerminalNode(root->right, node);
}