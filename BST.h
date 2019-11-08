#include <string>
#include <iostream>
#include "libs/TerminalGraphs/TerminalGraphs.h"


#define RIGHT true;
#define LEFT false;

class BST{
    public:
        using Key = int;
        using Item = std::string;
        struct Node;
        void insert(Key, Item);
        Item* lookup(Key);
        void replaceNodeItem(Key, Item);
        BST() = default;
        void displayNodes();
        void remove(Key);
        void rotate(Key, bool);
        int size();
        int getLevels();

        void displayTree();

    private:
        Node* root = nullptr;
        void insertRec(Key, Item, Node* &);
        Item* lookupRec(Key, Node*);
        Node* getNodeRec(Key, Node*);
        Node* getParentNodeRec(Key, Node*);
        static bool isLeaf(Node*);
        void removeRec(Key k, Node* currentNode);
        void Rrotation(Node*, Node*);
        void Lrotation(Node*, Node*);
        void displayNodesRec(Node*);

        // these functions are concerned with display
        int countNodesRec(Node*);
        int getMaxLevel(Node*);

        void AddNodesToPanel(Node*, Point* ,Panel*, int, int);
};