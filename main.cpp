#include "BST.h"

int main(){
    
    BST bst = BST();
    
    bst.insert(5,"Key: 5");
    bst.insert(12, "Key: 12");
    bst.insert(2, "Key: 2");
    bst.insert(1,"Key: 1");
    // bst.remove(1);
    bst.insert(4, "Key: 4");
    bst.insert(10, "Key: 10");
    //bst.replaceNodeItem(10, "this node has been replaced");
    // bst.displayNodes();
    bst.displayTree();
    std::cout << "size: " << bst.size() << std::endl
    << "levels: " << bst.getLevels() << std::endl;
    return 0;
}