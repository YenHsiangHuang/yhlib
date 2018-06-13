#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using std::vector;
using std::string;

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:

    class Node
    {
    public:
        string name;
        vector<Node*> children;

        Node() : name(), children() {};
        Node(string n) : name(n) {};
        Node(string n, vector<Node*> c) : name(n), children(c) {};
    };


    // data
    vector<Node*> nodes;

    // constructors
    Graph() : nodes() {};
    Graph(vector<Node*> n) : nodes(n) {};

    // methods
    void addNode(string n);
    bool addNode(Node* nd); Node* getNode(string n); void addChildren(string n, string c);
    void addChildren(Node* nd, Node* c);

    bool search(string a, string b);
};

class UGraph
{
public:

    class Node
    {
    public:
        string name;
        unordered_set<Node*> parents;
        unordered_set<Node*> children;
        int nDependencies = 0;
        Node() : name(), parents(), children() {};
        Node(string n) : name(n) {};

        void addParent(Node* p);
        void addChild(Node* c);
        void eraseParent(Node* p);
        void eraseChild(Node* c);
    };

    unordered_set<Node*> roots;
    unordered_set<Node*> nodes;
    unordered_map<string, Node*> nameNodeTable;
    void addNode(string& n);
    void addEdge(string& parentName, string& childName);
    void eraseNode(Node *nd);
    void eraseEdge(Node *parentNode, Node *childNode);
    void eraseRoots();

};

#endif
