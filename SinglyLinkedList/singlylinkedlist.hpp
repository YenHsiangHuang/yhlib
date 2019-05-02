#ifndef LIST_H
#define LIST_H

class SList {
public:
    class Node {
    private:
        int data;
        Node* next;

    public:
        Node() : data(0), next(nullptr){};
        Node(int d) : data(d), next(nullptr){};
        Node(int d, Node* nextNode) : data(d), next(nextNode){};
        Node(Node* node) : data(node->data), next(node->next){};
        ~Node() {
            data = 0;
            next = nullptr;
        };


        // Copy / Move
        void copy_from(const Node* incoming);

        // Delete
        void delete_next_node();
        void remove_dup(Node* head);
        void remove_dup_in_place(Node* head);

        // Edit
        Node* partition(Node* head, int d);

        bool is_end_of_list() const ;
        Node* get_next_node() const ;
        void set_next_node(Node* node);
        void set_data(int d);
        int get_data() const ;
    };

private:
    Node* head = nullptr;

    // Add
    void append(int d);
    Node* remove(int d);

    Node* get_end_of_list() const ;
    Node* create_new_list_node(int d);

    void delete_node(Node* node);
};

#endif  // LIST_H
