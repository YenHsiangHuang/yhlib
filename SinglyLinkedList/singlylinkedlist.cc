#include "singlylinkedlist.h"
#include <unordered_set>

/*
 * Add
 */
void Node::append(int d) {
    Node* end = this;
    while (end->next != nullptr) {
        end = end->next;
    }
    end->next = new Node(d);
}

/*
 * Copy / Move
 */
void Node::copyFrom(const Node* incoming) {
    this->data = incoming->data;
    this->next = incoming->next;
}

/*
 * Delete
 */
void Node::deleteNodeAfter(Node* prevNode) {
    prevNode->next = this->next;
    delete this;
}

// Given only access to the middle node
bool Node::deleteNode(Node* node) {
    if ((node == nullptr) || (node->next == nullptr)) return false;
    Node* toDelete = node->next;
    node->copyFrom(toDelete);
    delete toDelete;
    return true;
}

// If the head could change, we need a dummy head
Node* Node::remove(Node* head, int d) {
    if (head == nullptr) return head;

    Node dummy;
    Node* dummyHead = &dummy;  // Do not need to use "new"
    dummyHead->next = head;

    Node* prevNode = dummyHead;
    Node* node = head;
    while (node != nullptr) {
        if (node->data == d) {
            node->deleteNodeAfter(prevNode);
        } else {
            prevNode = node;
        }
        node = prevNode->next;
    }
    return dummyHead->next;
}

// Head can never change, do not need a dummy head
void Node::removeDup(Node* head) {
    Node dummy;
    Node* prevNode = &dummy;
    Node* node = head;
    std::unordered_set<int> dups;
    while (node != nullptr) {
        if (dups.count(node->data)) {
            node->deleteNodeAfter(prevNode);
        } else {
            dups.insert(node->data);
            prevNode = node;
        }
        node = prevNode->next;
    }
}

void Node::removeDupInPlace(Node* head) {
    if (head == nullptr) return;
    Node* node = head;
    while (node != nullptr) {
        node->next = node->remove(node->next, node->data);
        node = node->next;
    }
}

/*
 * Edit
 */
Node* Node::partition(Node* head, int d) {
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
    //if (head == nullptr || head->next == nullptr) return head;

    //Node dummyRight, dummyLeft;
    //Node* dummyRightHead = &dummyRight;
    //Node* dummyLeftHead = &dummyLeft;
    //Node* rightNode = dummyRightHead;
    //Node* leftNode = dummyLeftHead;

    //Node* node = head;
    //while (node != nullptr) {
        //if (node->data >= d) {
            //rightNode->next = node;
            //rightNode = rightNode->next;
        //} else {
            //leftNode->next = node;
            //leftNode = leftNode->next;
        //}
        //node = node->next;
    //}

    //leftNode->next = dummyRightHead->next;
    //rightNode->next = nullptr;


    //return dummyLeftHead->next;
}
