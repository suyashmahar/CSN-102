/*
================================================================
 * Usages:
 *  suyash@suyash:~/Documents/GitHub/CSN-102/bst-tree$ ./bst.elf
 *  Postorder traversal : 0-103477521
 *  Preorder traversal : 102-1053747
 *  InOrder traversal : 01-10235747
 *  
 *  Here's a tree for you
 *  
 *                  47
 *                /
 *              7
 *            /
 *          5
 *            \
 *              3
 *         /
 *      2
 *        \
 *          -10
 *    /
 *  1
 *    \
 *      0
================================================================
*/

#include<iomanip>
#include<iostream>
#include<sstream>

void setw(int indent){
    while (indent--){
        std::cout << " ";
    }
}
class node{
    public:
        node *left;
        node *right;
        int data;
        
        node();

        node(int data, node *left, node *right){
            this->data = data;
            this->left = left;
            this->right = right;
        }
};

class bst{
    private:
        void addToNode(node *ref, int element);
        void constructPostOrderTraversal(node *ref, std::stringstream &ss);
        void constructPreOrderTraversal(node *ref, std::stringstream &ss);
        void constructInOrderTraversal(node *ref, std::stringstream &ss);

    public:
        node *root;
        bst(){
            root = NULL;
        }
        void add(int element);
        void postorderPrint(node* p, int indent=0);
        bool search(node *ref, int element);

        std::string postOrderTraversal() { 
            std::stringstream ss("");
            constructPostOrderTraversal(root, ss);
            return ss.str(); 
        }

        std::string preOrderTraversal(){ 
            std::stringstream ss;
            constructPreOrderTraversal(root, ss); 
            return ss.str(); 
        }

        std::string inOrderTraversal(){ 
            std::stringstream ss;
            constructInOrderTraversal(root, ss); 
            return ss.str(); 
        }
};

void bst::addToNode(node *ref, int element) {
    if (ref->data == element){
        return;
    } else if (ref->data <= element) {
        if (ref->right == NULL){
            node *newNode = new node(element, NULL, NULL);
            ref->right = newNode;
        } else {
            addToNode(ref->right, element);
        }
    } else {
        if (ref->left == NULL){
            node *newNode = new node(element, NULL, NULL);
            ref->left = newNode;
        } else {
            addToNode(ref->right, element);
        }
    }
}

void bst::add(int element){
    if (root == NULL){
        root = new node(element, NULL, NULL);
    } else {
        addToNode(root, element);
    }
}


void bst::constructPostOrderTraversal(node *ref, std::stringstream &ss) {
    if (ref->left!=NULL){
        constructPostOrderTraversal(ref->left, ss);
    }
    
    if (ref->right!=NULL){
        constructPostOrderTraversal(ref->right, ss);
    }

    ss << ref->data;
}


void bst::constructPreOrderTraversal(node *ref, std::stringstream &ss){
    ss << ref->data;

    if (ref->left!=NULL){
        constructPreOrderTraversal(ref->left, ss);
    }
    
    if (ref->right!=NULL){
        constructPreOrderTraversal(ref->right, ss);
    }
}

void bst::constructInOrderTraversal(node *ref, std::stringstream &ss){
    if (ref->left!=NULL){
        constructInOrderTraversal(ref->left, ss);
    }

    ss << ref->data;
    
    if (ref->right!=NULL){
        constructInOrderTraversal(ref->right, ss);
    }
}
void bst::postorderPrint(node* p, int indent) {
    if(p != NULL) {
        if(p->right) {
            postorderPrint(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<< p->data << "\n ";
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            postorderPrint(p->left, indent+4);
        }
    }
}

bool bst::search(node *ref, int element){
    if (ref->data == element) {
        return true;
    } else {
        if (ref->left != NULL && ref->data > element) {
            return search(ref->left, element);
        } else if (ref->right != NULL && ref->data <= element){
            return search(ref->right, element);                
        } else {
            return false;
        }
    }
}


int main() {
    std::cout << "====================================================" << std::endl;
    bst newTree;
    newTree.add(1);
    newTree.add(2);
    newTree.add(5);
    newTree.add(7);
    newTree.add(2);
    newTree.add(0);
    newTree.add(47);
    newTree.add(-10);
    newTree.add(3);

    std::cout << "Postorder traversal : " << newTree.postOrderTraversal() << std::endl;
    std::cout << "Preorder traversal : " << newTree.preOrderTraversal() << std::endl;
    std::cout << "InOrder traversal : " << newTree.inOrderTraversal() << std::endl;
    
    // Prints structure of the tree from left to right (like a fallen tree)
    std::cout << std::endl << "Here\'s a tree for you" << std::endl << std::endl;
    newTree.postorderPrint(newTree.root, 0);
    std::cout << std::endl;

    std::cout << "searching for \'470\'... \nResult: " 
              << newTree.search(newTree.root, 470) 
              << std::endl; 
    
    std::cout << "searching for \'47\'... \nResult: " 
              << newTree.search(newTree.root, 47) 
              << std::endl; 
    
    std::cout << "====================================================" << std::endl;
}