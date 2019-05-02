#include <stdio.h>
#include "binarytree.hpp"

using TreeNode = BinarySearchTree::TreeNode;

TreeNode* BinarySearchTree::insert(int d) {
    TreeNode* new_node = create_node_of_value(d);
    return insert(new_node);
}

TreeNode* BinarySearchTree::insert(TreeNode* new_node) {
    if (this->is_empty()) {
        set_root(new_node);
    } else {
        append_child(new_node);
    }
    return new_node;
}

void BinarySearchTree::append_child(TreeNode* new_node) {
    TreeNode* curr_node = this->root;
    while (curr_node) {
        if (new_node->is_appendable_to(curr_node)) {
            curr_node->append_child(new_node);
            break;
        } else {
            curr_node = curr_node->go_down(new_node);
        }
    }
    ++n_tree_nodes;
}

void BinarySearchTree::TreeNode::append_child(TreeNode* new_node) {
    if (new_node->is_appendable_to_the_right_of(this)) {
        this->append_right_child(new_node);
    } else {
        this->append_left_child(new_node);
    }
}

void BinarySearchTree::TreeNode::append_right_child(TreeNode* new_node) {
    this->set_right_child(new_node);
}
void BinarySearchTree::TreeNode::append_left_child(TreeNode* new_node) {
    this->set_left_child(new_node);
}

bool BinarySearchTree::TreeNode::is_appendable_to(TreeNode* node) {
    return node->is_appendable_to_the_right_of(this) || node->is_appendable_to_the_reft_of(this);
}

bool BinarySearchTree::TreeNode::is_appendable_to_the_right_of(TreeNode* node) {
    return node->right == nullptr && this->get_value() > node->get_value();
}

bool BinarySearchTree::TreeNode::is_appendable_to_the_reft_of(TreeNode* node) {
    return node->left == nullptr && !(this->get_value() > node->get_value());
}

TreeNode* BinarySearchTree::TreeNode::go_down(TreeNode* new_node) const {
    if (new_node->get_value() > this->get_value()) {
        return this->get_right_child();
    } else {
        return this->get_left_child();
    }
}

TreeNode* BinarySearchTree::create_node_of_value(int d) {
    return new TreeNode(d);
}

// TreeNode* BinarySearchTree::insert(int d) {
//     TreeNode* new_node = new TreeNode(d);
//     if (n_tree_nodes == 0) {
//         root = new_node;
//     } else {
//         TreeNode* curr_node = root;
//         while (curr_node) {
//             if (d > curr_node->data) {
//                 if (curr_node->right != nullptr) {
//                     curr_node = curr_node->right;
//                 } else {
//                     curr_node->right = new_node;
//                     break;
//                 }
//             } else {
//                 if (curr_node->left != nullptr) {
//                     curr_node = curr_node->left;
//                 } else {
//                     curr_node->left = new_node;
//                     break;
//                 }
//             }
//         }
//     }
//     n_tree_nodes++;
//     return new_node;
// }

bool BinarySearchTree::erase(int d) {
    // Don't want to spend time on this
    n_tree_nodes--;
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
TreeNode* BinarySearchTree::get_random_node() {
    if (n_tree_nodes == 0) return nullptr;

    TreeNode* node = left_most(root);
    int lottery = rand()%n_tree_nodes;
    for (int i = 0; i < lottery; i++) {
        node = find_next(node);
    }
    return node;
}

void BinarySearchTree::create_minimal_BST(vector<int>& sorted_value) {
    if (root != nullptr) return;
    root = create_minimal_BST(sorted_value, 0, sorted_value.size()-1);
    n_tree_nodes = sorted_value.size();
}

TreeNode* BinarySearchTree::find(TreeNode* node, int target_value) {
    if (!node) return nullptr;
    int node_value = node->get_value();

    if (target_value == node_value) return node;

    if (target_value > node_value)        return find(node->get_right_child(), target_value);
    else /* target_value <= node_value */ return find(node->get_left_child() , target_value);
}

TreeNode* BinarySearchTree::find_next(TreeNode* nd) {
    if (!root || !nd) return nullptr;
    if (nd->get_right_child()) return left_most(nd->get_right_child());  // trivial part

    TreeNode* curr_node = root;
    TreeNode* res = nullptr;
    while (curr_node) {
        if (curr_node->get_value() > nd->get_value()) {
            res = curr_node;
            curr_node = curr_node->get_left_child();
        } else {  // curr_node->data < nd->data
            curr_node = curr_node->get_right_child();
        }
    }
    return res;
}

TreeNode* BinarySearchTree::left_most(TreeNode* node) {
    if (!node) return nullptr;
    while (!node->is_left_empty()) node = node->get_left_child();
    return node;
}

TreeNode* BinarySearchTree::create_minimal_BST(vector<int>& sorted_value, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end-start)/2;
    TreeNode* node = create_node_of_value(sorted_value[mid]);
    node->set_left_child(create_minimal_BST(sorted_value, start, mid-1));
    node->set_right_child(create_minimal_BST(sorted_value, mid+1, end));
    return node;
}
