#include "BST.h"

int main(){
    
    BST bst = BST();
    
    bst.insert(5,"node 1");
    bst.insert(12, "node 2");
    bst.insert(2, "node 3");
    bst.insert(1,"node 3");
    bst.insert(4, "node 4");
    bst.insert(10, "node 5");
    //bst.replaceNodeItem(12, "this node has been replaced");
    bst.displayNodes();
    return 0;
}