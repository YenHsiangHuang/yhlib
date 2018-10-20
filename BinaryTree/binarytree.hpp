#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdlib.h>
#include <time.h>
#include <vector>
using std::vector;


class BinarySearchTree
{
public:
    class TreeNode
    {
    public:
        int data;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;

        TreeNode(int d) : data(d) {};
    };

    int nTreeNodes = 0;

    BinarySearchTree() {
        srand(time(nullptr));
    }

    TreeNode* insert(int d);
    bool erase(int d);
    TreeNode* find(int d);
    TreeNode* getRandomNode();
    void createMinimalBST(vector<int>& sortedValue);

private:
    TreeNode* root = nullptr;
    TreeNode* find(TreeNode* node, int d);
    TreeNode* findNext(TreeNode* nd);
    TreeNode* leftMost(TreeNode* nd);
    TreeNode* createMinimalBST(vector<int>& sortedValue, int start, int end);
};


#endif
