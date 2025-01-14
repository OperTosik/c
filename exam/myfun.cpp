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
    if (tmp1 == nullptr && tmp2 == nullptr) {
        deleteNode(root->left);
        walkWithDelete(root->right, a, b);
    }
    tmp1 = findElem(root->right, a);
    tmp2 = findElem(root->right, b);
    if (tmp1 == nullptr && tmp2 == nullptr) {
        deleteNode(root->right);
        walkWithDelete(root->left, a, b);
    }
}

/** Начиная с родителя, удаляет все ветви не содержащие вершину a или вершину b */
void saveNodesWithParents(TreeNode* root, TreeNode* a, TreeNode* b, TreeNode* parent) {
    if (root == nullptr) return;
    if (parent == root) {
        walkWithDelete(root->left, a, b);
        walkWithDelete(root->right, a, b);
        return;
    }
    findElem(root->left, parent);
    findElem(root->right, parent);
}

/** Оставляет ветви от корня до вершин a и b
 * хз, надо переписать
 */
void saveOnlyNodes(TreeNode* root, TreeNode* a, TreeNode* b) {
    if (root == nullptr) return;
    TreeNode* tmp1 = findElem(root->left, a);
    TreeNode* tmp2 = findElem(root->left, b);
    if (tmp1 == nullptr && tmp2 == nullptr) {
        deleteNode(root->left);
        saveOnlyNodes(root->right, a, b);
    }
    tmp1 = findElem(root->right, a);
    tmp2 = findElem(root->right, b);
    if (tmp1 == nullptr && tmp2 == nullptr) {
        deleteNode(root->right);
        saveOnlyNodes(root->left, a, b);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////

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
    if (root == node && root->left == nullptr && root->right == nullptr) {
        root = nullptr;
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

///////////////////////////////////////////////////////////////////////////////////////////