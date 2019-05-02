#include "singlylinkedlist.hpp"
#include <unordered_set>

typedef SList::Node Node;

/**
   Add
 */
void SList::append(int d) {
    Node* end = get_end_of_list();
    end->set_next_node(create_new_list_node(d));
}

Node* SList::get_end_of_list() const {
    Node* end = head;
    while (!end->is_end_of_list()) {
        end = end->get_next_node();
    }
    return end;
}

bool SList::Node::is_end_of_list() const {
    return this != nullptr && this->get_next_node() == nullptr;
}

Node* SList::Node::get_next_node() const {
    return this->next;
}

void SList::Node::set_next_node(Node* node) {
    this->next = node;
}

Node* SList::create_new_list_node(int d) {
    return new Node(d);
}

void SList::Node::set_data(int d) {
    this->data = d;
}

int SList::Node::get_data() const {
    return this->data;
}

/**
   Copy / Move
 */
void SList::Node::copy_from(const Node* incoming) {
    this->set_next_node(incoming->get_next_node());
    this->set_data(incoming->get_data());
}

/**
   Delete
 */
void SList::Node::delete_next_node() {
    Node* to_delete = this->get_next_node();
    if (to_delete != nullptr) {
        this->set_next_node(to_delete->get_next_node());
        delete to_delete;
    }
}

// Given only access to the middle node
void SList::delete_node(Node* node) {
    Node* to_delete = node->get_next_node();
    if (to_delete != nullptr) {
        node->copy_from(to_delete);
        delete to_delete;
    } else {
        delete node;
    }
}

// If the head could change, we need a dummy head
Node* SList::remove(int d) {
    if (head == nullptr) return head;

    Node dummy;
    Node* dummy_head = &dummy;  // Do not need to use "new"
    dummy_head->set_next_node(head);

    Node* prev_node = dummy_head;
    Node* node = head;
    while (node != nullptr) {
        if (node->get_data() == d) {
            prev_node->delete_next_node();
        } else {
            prev_node = node;
        }
        node = prev_node->get_next_node();
    }
    return dummy_head->get_next_node();
}

// Head can never change, do not need a dummy head
void SList::Node::remove_dup(Node* head) {
    Node dummy;
    Node* prev_node = &dummy;
    Node* node = head;
    std::unordered_set<int> dups;
    while (node != nullptr) {
        if (dups.count(node->data)) {
            node->delete_next_node(prev_node);
        } else {
            dups.insert(node->data);
            prev_node = node;
        }
        node = prev_node->next;
    }
}

void SList::Node::remove_dup_in_place(Node* head) {
    if (head == nullptr) return;
    Node* node = head;
    while (node != nullptr) {
        node->next = node->remove(node->next, node->data);
        node = node->next;
    }
}

/**
   Edit
 */
Node* SList::Node::partition(Node* head, int d) {
    if (head == nullptr || head->next == nullptr) return head;

    Node* tail = head;
    Node* node = head;
    while (node != nullptr) {
        Node* nextNode = node->next;
        if (node->data < d) {
            node->next = head;
            head = node;
        } else {
            tail->next = node;
            tail = node;
        }
        node = nextNode;
    }

    tail->next = nullptr;

    return head;

    /*
     * The following code provides a method with same time complexity
     * But we have to hold four variables to keep tracking of two linked lists
     */
    // if (head == nullptr || head->next == nullptr) return head;

    // Node dummyRight, dummyLeft;
    // Node* dummyRightHead = &dummyRight;
    // Node* dummyLeftHead = &dummyLeft;
    // Node* rightNode = dummyRightHead;
    // Node* leftNode = dummyLeftHead;

    // Node* node = head;
    // while (node != nullptr) {
    // if (node->data >= d) {
    // rightNode->next = node;
    // rightNode = rightNode->next;
    //} else {
    // leftNode->next = node;
    // leftNode = leftNode->next;
    //}
    // node = node->next;
    //}

    // leftNode->next = dummyRightHead->next;
    // rightNode->next = nullptr;

    // return dummyLeftHead->next;
}
