#include "BST.h"


struct BST::Node{
    // private structs are better defined in the .cpp file because the user
    // doesn't need to know anything about this struct  
    Key key;
    Item item;
    Node* leftNode = nullptr;
    Node* rightNode = nullptr;
    public:
        Node(Key k, Item i){
            key = k;
            item = i;
        }
};

void BST::insert(Key k, Item i){
    // first lookup if node is present in tree
    if(lookup(k) == nullptr){
        // not present
        insertRec(k, i, root);
    } else {
        // present --> replace
        replaceNodeItem(k,i);
    }

}

void BST::insertRec(Key k, Item i, Node* & currentNode){
    // // this version tests the current node
    // if(isLeaf(currentNode)){
    //     currentNode = new Node(k, i);
    // } else if(currentNode->key > k){
    //     insertRec(k, i, currentNode->leftNode);
    // } else if(currentNode->key < k){
    //     insertRec(k, i, currentNode->rightNode);
    // }

    // this version tests the child nodes
    if(isLeaf(currentNode)){
        currentNode = new Node(k, i);
    } else{
        if(currentNode->key > k && isLeaf(currentNode->leftNode)){
            // given key is less than current node key AND left child empty
            currentNode->leftNode = new Node(k, i);
        }else if(currentNode->key > k && !isLeaf(currentNode->leftNode)){
            // given key is less than current node key AND left child is a node
            insertRec(k, i, currentNode->leftNode);
        } else if(currentNode->key < k && isLeaf(currentNode->rightNode)){
            // given key is less than current node key AND right child empty
            currentNode->rightNode = new Node(k, i);
        }else if(currentNode->key < k && !isLeaf(currentNode->rightNode)){
            // given key is less than current node key AND right child is a node
            insertRec(k, i, currentNode->rightNode);
        }
    }
}

BST::Item* BST::lookup(Key keyWanted){
    return lookupRec(keyWanted, root);
}

BST::Item* BST::lookupRec(Key keyWanted, Node* currentNode){
    
    if(isLeaf(currentNode)){
        // test for root nood or end node reached
        return nullptr;
    }
    
    if(currentNode->key == keyWanted){
        return &currentNode->item;
    } else if(currentNode->key > keyWanted){
        return lookupRec(keyWanted, currentNode->rightNode);
    } else if(currentNode->key < keyWanted){
        return lookupRec(keyWanted, currentNode->leftNode);
    }
}

void BST::replaceNodeItem(Key k, Item i){
    getNodeRec(k, root)->item = i;
}

BST::Node* BST::getNodeRec(Key k, Node* currentNode){
    if(currentNode->key == k){
        return currentNode;
    } else if(currentNode->key > k){
        return getNodeRec(k, currentNode->rightNode);
    } else if(currentNode->key < k){
        return getNodeRec(k, currentNode->leftNode);
    }
}

bool BST::isLeaf(Node* node){
    return (node == nullptr) ? true : false;
}

void BST::displayNodes(){
    displayNodesRec(root);
}

void BST::displayNodesRec(Node* currentNode){
    // traverse left tree
    // visit (sub) tree root
    // traverse right tree

    if(!isLeaf(currentNode->leftNode)){
        // if left child present, go to
        displayNodesRec(currentNode->leftNode);
    } else {
        // if left child not present, display current node
        std::cout << currentNode->key << ":" << currentNode->item << std::endl;
        if(!isLeaf(currentNode->rightNode)){
            displayNodesRec(currentNode->rightNode);
        }
    }

}