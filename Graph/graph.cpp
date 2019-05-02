#include <queue>
#include <unordered_set>
#include "graph.hpp"

using namespace std;

void Graph::addNode(string n) {
    Graph::Node* nd = new Graph::Node(n);
    addNode(nd);
}

bool Graph::addNode(Node* nd) {
    if (nd == nullptr) return false;
    nodes.push_back(nd);
    return true;
}

Graph::Node* Graph::getNode(string n) {
    for (auto &it : nodes) {
        if (it->name == n) {
            return it;
        }
    }
    return nullptr;
}

void Graph::addChildren(string n, string c) {
    Graph::Node *parent = nullptr, *child = nullptr;
    for (auto &it : nodes) {
        if (it->name == n) parent = it;
        if (it->name == c) child = it;
    }
    if (parent != nullptr && child != nullptr) {
        addChildren(parent, child);
    }
}

void Graph::addChildren(Node* parent, Node* child) {
    parent->children.push_back(child);
}

bool Graph::search(string a, string b) {
    // Breath-first search from a to b
    Node* A = getNode(a);
    Node* B = getNode(b);

    queue<Node*> toVisit;
    unordered_set<Node*> visited;
    toVisit.push(A);

    while (!toVisit.empty()) {
        Node* curr = toVisit.front();
        toVisit.pop();
        if (curr == B) return true;

        if (visited.count(curr) == 0) {
            visited.insert(curr);
            for (auto &it : curr->children) {
                toVisit.push(it);
            }
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////

void UGraph::Node::addParent(UGraph::Node* p) {
    parents.insert(p);
    nDependencies++;
}

void UGraph::Node::addChild(UGraph::Node* c) {
    children.insert(c);
}

void UGraph::Node::eraseParent(Node* p) {
    parents.erase(p);
    nDependencies--;
}

void UGraph::Node::eraseChild(Node* c) {
    children.erase(c);
}

void UGraph::addNode(string& n) {
    UGraph::Node *nd = new UGraph::Node(n);
    nodes.insert(nd);
    roots.insert(nd);
    nameNodeTable[n] = nd;
}

void UGraph::addEdge(string& parentName, string& childName) {
    UGraph::Node* parentNode = nameNodeTable[parentName];
    UGraph::Node* childNode = nameNodeTable[childName];

    roots.erase(childNode);

    parentNode->addChild(childNode);
    childNode->addParent(parentNode);
}


void UGraph::eraseNode(UGraph::Node *nd) {
    if (nd->nDependencies == 0) {
        roots.erase(nd);
    } else {
        unordered_set<Node*> toErase(nd->parents);
        for (auto &p : toErase) {
            eraseEdge(p, nd);
        }
    }

    unordered_set<Node*> toErase(nd->children);
    for (auto &c : toErase) {
        eraseEdge(nd, c);
    }
    nodes.erase(nd);
    nameNodeTable.erase(nd->name);
}

void UGraph::eraseEdge(UGraph::Node *parentNode, UGraph::Node *childNode) {
    parentNode->eraseChild(childNode);
    childNode->eraseParent(parentNode);
    if (childNode->nDependencies == 0) roots.insert(childNode);
}

void UGraph::eraseRoots() {
    unordered_set<Node*> toErase;
    for (auto &it : roots) toErase.insert(it);
    for (auto &it : toErase) {
        eraseNode(it);
    }
}





