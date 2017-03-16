#include<iostream>
#include<sstream>
#include<string>
#include<cstdlib>

template <typename T>
class treeNode {
    public:
        T data;
        treeNode* left;
        treeNode* right;
        
        treeNode() {
            data = NULL;
            left = right = NULL;
        }

        treeNode(T data, treeNode* left, treeNode* right) {
            this->data = data;
            this->left = left;
            this->right = right;
        }

        treeNode(T data) {
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
};

template <class T>
class tree {
    private:
    public:
        T* root;
        tree() { root = NULL; }
        ~tree() { }
        bool isEmpty() { return (root == NULL); }
        bool getRoot(T& x) const;
        tree<T>* makeTree(const T& element, tree<T>& left, tree<T>& right);
        tree<T>* breakTree(const T& element, tree<T>& left, tree<T>& right);
    protected:
};


int main(){

}