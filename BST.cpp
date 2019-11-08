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
    // if current node is root
    if(currentNode == nullptr){
        currentNode = new Node(k, i);
    } else {
        if(k < currentNode->key){
            if(currentNode->leftNode == nullptr)
                currentNode->leftNode = new Node(k, i);
            else
                insertRec(k, i, currentNode->leftNode);

        }else if(k > currentNode->key){
            if(currentNode->rightNode == nullptr)
                currentNode->rightNode = new Node(k, i);
            else 
                insertRec(k, i, currentNode->rightNode);
        } 
    }
}

BST::Item* BST::lookup(Key keyWanted){
    return lookupRec(keyWanted, root);
}

BST::Item* BST::lookupRec(Key keyWanted, Node* currentNode){
    
    if(currentNode == nullptr){
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
    } else if(currentNode->key < k){
        return getNodeRec(k, currentNode->rightNode);
    } else if(currentNode->key > k){
        return getNodeRec(k, currentNode->leftNode);
    }
}

BST::Node* BST::getParentNodeRec(Key k, Node* currentNode){
    if(currentNode->leftNode->key == k || currentNode->rightNode->key == k){
        // if any of the child nodes match then return current node
        return currentNode;
    } else if(currentNode->leftNode->key > k){
        // if left node is greater then we have to go left and check smaller nodes`
        getParentNodeRec(k, currentNode->leftNode);
    } else if(currentNode->rightNode->key < k){
        // if right is less then we have to go right and check larger nodes
        getParentNodeRec(k, currentNode->rightNode);
    }

    // check both left and right and if match return current
    // if currentNode->left->key < k then go down the right tree
}

bool BST::isLeaf(Node* node){
    if(node->leftNode == nullptr && node->rightNode == nullptr)
        return true;
    else 
        return false;
}

void BST::remove(Key k){
    removeRec(k, root);
}

void BST::removeRec(Key k, Node* currentNode){
    Node* tempNodePtr;
    // check child nodes
    if(k == currentNode->leftNode->key){
        tempNodePtr = currentNode->leftNode;
        // consider making this a seperate function
        if(isLeaf(tempNodePtr)){
            currentNode->leftNode = nullptr;
            delete tempNodePtr;
        } else {
            if(tempNodePtr->leftNode != nullptr){
                currentNode->leftNode = tempNodePtr->leftNode;
            } else {
                currentNode->rightNode = tempNodePtr->rightNode;
            }
            delete tempNodePtr;
        }
    } else if(k == currentNode->rightNode->key){
        tempNodePtr = currentNode->rightNode;
        if(isLeaf(tempNodePtr)){
            currentNode->rightNode = nullptr;
            delete tempNodePtr;
        } else {
            if(tempNodePtr->leftNode != nullptr){
                currentNode->leftNode = tempNodePtr->leftNode;
            } else {
                currentNode->rightNode = tempNodePtr->rightNode;
            }
            delete tempNodePtr;
        }
    } else {
        if(k < currentNode->key){
            removeRec(k, currentNode->leftNode);
        } else {
            removeRec(k, currentNode->rightNode);
        }
    }
    
}

void BST::rotate(Key k, bool direction){
    Node* rotationNode = getNodeRec(k, root);
    Node* rootPtr = getParentNodeRec(k, root);

    if(direction){  // if right
        Rrotation(rotationNode, rootPtr);
    } else {
        Lrotation(rotationNode, rootPtr);
    }
}

void BST::Rrotation(Node* roationPoint, Node* localRoot){
    Node* Aptr = roationPoint->leftNode;
    Node* Bptr = roationPoint;
    Node* beta = Aptr->rightNode; 

    // redirect local root
    localRoot = Aptr;
    // redirect beta;
    Bptr->leftNode = beta;
    // point a to b
    Aptr->rightNode = Bptr;
}

void BST::Lrotation(Node* roationPoint, Node* localRoot){
    Node* Aptr = roationPoint;
    Node* Bptr = roationPoint->rightNode;
    Node* beta = Bptr->leftNode; 

    // redirect local root
    localRoot = Bptr;
    // redirect beta;
    Aptr->rightNode = beta;
    // point a to b
    Bptr->leftNode = Aptr;
}

void BST::displayNodes(){
    displayNodesRec(root);
}

void BST::displayNodesRec(Node* currentNode){  
    // traverse left tree
    // visit (sub) tree root
    // traverse right tree

    if(isLeaf(currentNode)){
        // do nothing and display
        std::cout << currentNode->key << ":" << currentNode->item << std::endl;
    } else {
        displayNodesRec(currentNode->leftNode);
        std::cout << currentNode->key << ":" << currentNode->item << std::endl;
        if(currentNode->rightNode == nullptr){
            displayNodesRec(currentNode->rightNode);
        }   
    }
}

int BST::size(){
    return countNodesRec(root);
}

int BST::countNodesRec(Node* currentNode){
    int num = 0;
    if(isLeaf(currentNode)){
        return 1;
    } else {
        if(currentNode->leftNode != nullptr){
            num += countNodesRec(currentNode->leftNode);
        }
        num ++;
        if(currentNode->rightNode != nullptr){
            num += countNodesRec(currentNode->rightNode);
        }
    }    
    return num;
}

int BST::getLevels(){
    return getMaxLevel(root);
}

int BST::getMaxLevel(Node* currentNode){
    /*
        algorithm got from https://www.geeksforgeeks.org/sum-of-all-the-levels-in-a-binary-search-tree/
        (slightly changed by me)
    */
    int leftLevelMax = 0;
    int rightLevelMax = 0;
    if(isLeaf(currentNode)){
        return 1;
    }
    if(currentNode->leftNode != nullptr){
        leftLevelMax = getMaxLevel(currentNode->leftNode);
    }
    if(currentNode->rightNode != nullptr){
        rightLevelMax = getMaxLevel(currentNode->rightNode);
    }
    return ((leftLevelMax > rightLevelMax)? leftLevelMax : rightLevelMax) + 1;

}

// my overly complicated implementation of a displaying the tree
void BST::displayTree(){
    int panelSizeMultiplier = 5;
    int levels = BST::getLevels();
    int panelHieght = levels * panelSizeMultiplier;
    int panelWidth = (levels * levels) * panelSizeMultiplier;
    Panel p = Panel(panelWidth, panelHieght);

    int Xinc = (int)panelWidth/4; // /4 because first used for level 2
    int Yinc = 2;
    Point rootPoint = Point((int)panelWidth/2, 2,root->item);
    p.add(rootPoint);
    AddNodesToPanel(root, &rootPoint, &p, Xinc, Yinc);

    p.Display();
}

void BST::AddNodesToPanel(Node* parentNode, Point* parentPoint, Panel* panel, int Xinc, int Yinc){
    // root point need to be created first and passed into this
    
    // TODO: fix vector creation

    int newX = 0;
    int newY = 0;
    if(parentNode->leftNode != nullptr){
        newX = parentPoint->getX() - Xinc;
        newY = parentPoint->getY() + Yinc;
        Point leftChildPoint = Point(newX, newY, parentNode->leftNode->item);
        panel->add(leftChildPoint);
        // panel->connectPoints(leftChildPoint, *parentPoint);
        if(parentNode->leftNode != nullptr){
            AddNodesToPanel(parentNode->leftNode, &leftChildPoint, panel, Xinc/2, Yinc+2);
        }
    }
    if(parentNode->rightNode != nullptr){
        newX = parentPoint->getX() + Xinc;  
        newY = parentPoint->getY() + Yinc;
        Point rightChildPoint = Point(newX, newY, parentNode->rightNode->item);
        panel->add(rightChildPoint);
        // panel->connectPoints(rightChildPoint, *parentPoint);
        if(parentNode->rightNode != nullptr){
            AddNodesToPanel(parentNode->rightNode, &rightChildPoint, panel, Xinc/2, Yinc+2);
        }
    }
}