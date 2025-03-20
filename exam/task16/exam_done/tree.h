/*
 *          Некоторые функции для работы с бинарным
 *      неупорядоченным деревом для элементов типа  int
 */
#ifndef _TREE_H_
#define _TREE_H_
#include <stdio.h>


// описание вершины дерева
// этот класс менять нельзя !
class TreeNode
{
    public:
        int  value;
        int  balance;
        TreeNode *left,*right;
        TreeNode() { value = balance = 0; left = right = NULL; }
};

// класс бинарное дерево
// этот класс тоже не рекомендуется менять
class  Tree
{
    public:
        TreeNode *root;   // указатель на корень дерева

        // Конструктор пустого дерева
        Tree () { root = NULL; }

        // Деструктор
        ~Tree ();

        // Конструктор заполнения дерева числами из открытого файла.
        //     f   -  указатель на файл,
        Tree (FILE *f);

};

    
        //  Распечатка поддерева в файл.
        //     f   -  указатель на файл,
        //    pos  -  указатель на корень поддерева.

        void  T_Print (FILE *f, TreeNode *pos);

       /*  Примечание:
        *     Дерево распечатывается "лежа на левом боку", т.е.
        *  корень стоит слева, правая ветвь идет направо-вверх,
        *  левая ветвь идет направо-вниз.
        */
TreeNode* findNode(TreeNode* t, int value);
void removeLeftSubtree(TreeNode* t);
void removeRightSubtree(TreeNode* t);
bool isLeaf(const TreeNode* t);
void makeSubtreesEqual(TreeNode* t1, TreeNode* t2);

       
#endif
