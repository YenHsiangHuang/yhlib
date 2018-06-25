#ifndef LIST_H
#define LIST_H

class Node
{
public:
    int data;
    Node* next;

    Node() : data(0), next(nullptr) {};
    Node(int d) : data(d), next(nullptr) {};
    Node(int d, Node* nextNode) : data(d), next(nextNode) {};
    Node(Node* node) : data(node->data), next(node->next) {};
    ~Node() {
        data = 0;
        next = nullptr;
    };

    // Add
    void append(int d);

    // Copy / Move
    void copyFrom(const Node* incoming);

    // Delete
    void deleteNodeAfter(Node* prevNode);
    bool deleteNode(Node* node);
    Node* remove(Node* head, int d);
    void removeDup(Node* head);
    void removeDupInPlace(Node* head);

    // Edit
    Node* partition(Node* head, int d);
};

#endif  // LIST_H
