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
        TreeNode(int d) : data(d) {};
        TreeNode* BinarySearchTree::TreeNode::go_down(TreeNode* new_node) const ;  // any idea of a better name?

        // getter
        int get_value() const { return data; }
        TreeNode* get_right_child() const { return this->right; }
        TreeNode* get_left_child() const { return this->left; }

        // setter
        void set_right_child(TreeNode* node) { this->right = node; }
        void set_left_child(TreeNode* node) { this->left = node; }

        // modifier
        void append_child(TreeNode* new_node);
        void append_right_child(TreeNode* new_node);
        void append_left_child(TreeNode* new_node);

        // iser
        bool is_appendable_to(TreeNode* node);
        bool is_appendable_to_the_right_of(TreeNode* node);
        bool is_appendable_to_the_reft_of(TreeNode* node);
        bool is_right_empty() { this->right == nullptr; }
        bool is_left_empty() { this->left == nullptr; }

    private:
        int data;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
    };

    BinarySearchTree() {
        srand(time(nullptr));
    }

    TreeNode* insert(int d);
    bool erase(int d);
    TreeNode* find(int d);
    TreeNode* get_random_node();
    void create_minimal_BST(vector<int>& sortedValue);

private:
    TreeNode* root = nullptr;
    int n_tree_nodes = 0;
    TreeNode* find(TreeNode* node, int target_value);
    TreeNode* find_next(TreeNode* nd);
    TreeNode* left_most(TreeNode* nd);
    TreeNode* create_minimal_BST(vector<int>& sortedValue, int start, int end);

    void set_root(TreeNode* new_node) { this->root = new_node; }  // used only when this tree is empty
    void append_child(TreeNode* new_node);
    TreeNode* create_node_of_value(int d);
    bool is_empty() { return n_tree_nodes == 0; }  // is a empty tree
    TreeNode* insert(TreeNode* new_node);
};


#endif
