#include "binarytree.h"
#include <stdio.h>

using TreeNode = BinarySearchTree::TreeNode;

TreeNode* BinarySearchTree::insert(int d) {
    TreeNode* newNode = new TreeNode(d);
    if (nTreeNodes == 0) {
        root = newNode;
    } else {
        TreeNode* currNode = root;
        while (currNode) {
            if (d > currNode->data) {
                if (currNode->right != nullptr) {
                    currNode = currNode->right;
                } else {
                    currNode->right = newNode;
                    break;
                }
            } else {
                if (currNode->left != nullptr) {
                    currNode = currNode->left;
                } else {
                    currNode->left = newNode;
                    break;
                }
            }
        }
    }

    nTreeNodes++;
    return newNode;
}

bool BinarySearchTree::erase(int d) {
    // Don't want to spend time on this
    nTreeNodes--;
    return true;
}

TreeNode* BinarySearchTree::find(int d) {
    return find(root, d);
}

/*
 * This method takes O(n) in the worst case
 *
 * Another way to implement this is to modify TreeNode so that
 * each node contains the number of nodes below
 * which lead to a O(log n) solution but takes more space to store information
 *     class TreeNode
 *     {
 *     public:
 *         int data;
 *         int size;  // number of sub-nodes + 1
 *         TreeNode* left = nullptr;
 *         TreeNode* right = nullptr;
 *
 *         TreeNode(int d) : data(d) {};
 *     };
 */
TreeNode* BinarySearchTree::getRandomNode() {
    if (nTreeNodes == 0) return nullptr;

    TreeNode* node = leftMost(root);
    int lottery = rand()%nTreeNodes;
    for (int i = 0; i < lottery; i++) {
        node = findNext(node);
    }
    return node;
}

void BinarySearchTree::createMinimalBST(vector<int>& sortedValue) {
    if (root != nullptr) return;
    root = createMinimalBST(sortedValue, 0, sortedValue.size()-1);
    nTreeNodes = sortedValue.size();
}

TreeNode* BinarySearchTree::find(TreeNode* node, int d) {
    if (!node) return nullptr;
    if (d == node->data) return node;
    if (d >  node->data && node->right != nullptr) return find(node->right, d);
    if (d <= node->data && node->left  != nullptr) return find(node->left , d);
    return nullptr;
}

TreeNode* BinarySearchTree::findNext(TreeNode* nd) {
    if (!root || !nd) return nullptr;
    if (nd->right) return leftMost(nd->right);  // trivial part

    TreeNode* currNode = root;
    TreeNode* res = nullptr;
    while (currNode) {
        if (currNode->data > nd->data) {
            res = currNode;
            currNode = currNode->left;
        } else {  // currNode->data < nd->data
            currNode = currNode->right;
        }
    }
    return res;
}

TreeNode* BinarySearchTree::leftMost(TreeNode* node) {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

TreeNode* BinarySearchTree::createMinimalBST(vector<int>& sortedValue, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end-start)/2;
    TreeNode* node = new TreeNode(sortedValue[mid]);
    node->left = createMinimalBST(sortedValue, start, mid-1);
    node->right = createMinimalBST(sortedValue, mid+1, end);
    return node;
}
