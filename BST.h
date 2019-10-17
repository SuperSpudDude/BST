#include <string>
#include <iostream>


class BST{
    public:
        using Key = int;
        using Item = std::string;

        void insert(Key, Item);
        Item* lookup(Key);
        void replaceNodeItem(Key, Item);
        BST() = default;
        void displayNodes();

    private:
        struct Node;
        Node* root = nullptr;
        void insertRec(Key, Item, Node* &);
        Item* lookupRec(Key, Node*);
        Node* getNodeRec(Key, Node*);
        static bool isLeaf(Node*);
        void displayNodesRec(Node* currentNode);
};