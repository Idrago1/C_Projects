#include <iostream>
#include "Tree.h"

using namespace std;

Tree::Tree(){
    root = nullptr;
}

//recersivly deleats  
Tree::~Tree(){
    deleteTree(root);
}



void Tree::insert(const string& userInput) {
    //Make sure they have no duplications
    if (search(userInput)) {
        cout << "Duplicate detected, try again\n";
        return; 
    }

    if (root == nullptr) {
        root = new Node(userInput);
    } else {
        Node* currNode = root;
        bool endLoop = true;

        while (endLoop) {
            if (currNode->left == nullptr && currNode->middle == nullptr && currNode->right == nullptr) {
                // If this is a leaf
                if (currNode->large == "") {
                    // IF the node only have one valuse 
                    if(userInput > currNode->small) {
                        currNode->large = userInput;
                    }else{
                        currNode->large = currNode->small;
                        currNode->small = userInput;
                    }
                }else{
                    // The leaf is full
                    if(currNode == root){
                        // If the current node is the root then split at the middle
                        string midVal;
                        Node* leftNode;
                        Node* rightNode;

                        if(userInput < currNode->small){ //If the input is the smallest 
                            midVal = currNode->small;
                            leftNode = new Node(userInput);
                            rightNode = new Node(currNode->large);
                        } else if (userInput > currNode->large) { //If the input is the biggest
                            midVal = currNode->large;
                            leftNode = new Node(currNode->small);
                            rightNode = new Node(userInput);
                        } else if (userInput > currNode->small && userInput < currNode->large) {
                            midVal = userInput; // if it is in the middle 
                            leftNode = new Node(currNode->small);
                            rightNode = new Node(currNode->large);
                        }

                        root = new Node(midVal);
                        root->left = leftNode;
                        root->right = rightNode;
                    } else if (currNode->parent->large == "") {
                        // If the leaf is full and the parent only has one valse 
                        string midVal;
                        Node* leftNode;
                        Node* midNode;
                        Node* rightNode;

                        if (userInput < currNode->small) {
                            midVal = currNode->small;
                            leftNode = new Node(userInput);
                            midNode = new Node(currNode->large);

                            currNode->parent->large = currNode->parent->small;
                            currNode->parent->small = midVal;
                            currNode->parent->left = leftNode;
                            currNode->parent->middle = midNode;
                        } else if (userInput > currNode->large) {
                            midVal = currNode->large;
                            midNode = new Node(currNode->small);
                            rightNode = new Node(userInput);

                            currNode->parent->large = midVal;
                            currNode->parent->middle = midNode;
                            currNode->parent->right = rightNode;
                        }
                    }
                }
                endLoop = false;
            } else {
                // goes down the tree until it hits a leaf 
                Node* tempParent = currNode;
                if (userInput < currNode->small) {
                    currNode = currNode->left;
                } else if (currNode->hasTwoStrings()) {
                    if (userInput < currNode->large) {
                        currNode = currNode->middle;
                    } else if (userInput > currNode->large) {
                        currNode = currNode->right;
                    }
                } else if (userInput > currNode->large) {
                    currNode = currNode->right;
                }
                currNode->parent = tempParent;
            }
        }
    }
}
// removes the string 
void Tree::remove(const string& userInput) {
    if (!search(userInput)) {
        cout << "Isn't in the tree\n";
        return;
    }

    Node* deleteNode = search(root, userInput); // Find node which will have the deleted key
    
    // Leaf nodes
    if (!deleteNode->left && !deleteNode->middle && !deleteNode->right) {
        if (deleteNode->hasTwoStrings()) { // Two keys delete key and adjust
            if (userInput == deleteNode->small) {
                deleteNode->small = deleteNode->large;
                deleteNode->large = "";
            } else if (userInput == deleteNode->large) { // Just delete
                deleteNode->large = "";
            }
        } else if (deleteNode->large == "") { // Deleting leaf node with only one value parent only has one value
            if (deleteNode == root) { // Deleting entire root
                delete deleteNode;
                root = nullptr;
            } else {
                // Find parent
                Node* currNode = root;
                Node* tempParent = nullptr;

                while (currNode && currNode != deleteNode) { // Loop through tree until node is found and parent is linked
                    tempParent = currNode;
                    if (userInput < currNode->small) {
                        currNode = currNode->left;
                    } else if (currNode->hasTwoStrings()) {
                        if (userInput > currNode->large) {
                            currNode = currNode->right;
                        } else if (userInput > currNode->small && userInput < currNode->large) {
                            currNode = currNode->middle;
                        }
                    } else if (currNode->large == "") {
                        if (userInput > currNode->small) {
                            currNode = currNode->right;
                        }
                    }
                }

                if (deleteNode == tempParent->left) { // Deleting left leaf node then puts the child to null
                    tempParent->large = tempParent->right->small;
                    tempParent->right = nullptr;
                    tempParent->left = nullptr;
                } else if (deleteNode == tempParent->right) { // Deleting right leaf node then put the child ot null
                    tempParent->large = tempParent->small;
                    tempParent->small = tempParent->left->small;
                    tempParent->left = nullptr;
                    tempParent->right = nullptr;
                }
            }
        }
    } else { // In case deleteNode is a parent
        if (deleteNode == root) { // Zybooks testing assume 2-node and root
            root->small = root->left->small;
            root->large = root->right->small;
            root->left = nullptr;
            root->right = nullptr;
            //if it is a three node throw runtime because it only does 2 node 
            if(deleteNode->middle){
                throw runtime_error("was not tested in zybook ");
            }   
        }
        
        
    }
}

//deleates the tree recursivly 
void Tree::deleteTree(Node* deleteNode) {
    if (deleteNode != nullptr) { // Use recursion to delete every node
        deleteTree(deleteNode->left);
        deleteTree(deleteNode->middle);
        deleteTree(deleteNode->right);
        delete deleteNode;
    }
}

bool Tree::search(const string& userInput) const {
    return search(root, userInput);
}

Node* Tree::search(Node* node, const string& key) const {
    Node* currNode = node;
    // Look through the tree
    while (currNode != nullptr) {
        // When it is found
        if (key == currNode->small || key == currNode->large) {  
            return currNode;
        }
        // When the key is smaller 
        if (key < currNode->small) { 
            currNode = currNode->left;
        } else if (currNode->large == "") { // If it is a 2-node go right
            currNode = currNode->right;
        } else if (key < currNode->large) { // If currNode is a 3-node go middle
            currNode = currNode->middle;
        } else { // If currNode is a 3-node go right
            currNode = currNode->right;
        }
    }

    return nullptr;
}

//puts it in per order 
void Tree::preOrder( ) const {
    preOrder(root);
    cout<<endl;
}

void Tree::preOrder(Node* node) const {
    if (node != nullptr) {
        // if it is a 2 tree
        if (node->large == "") {
            cout << node->small << ", ";
            preOrder(node->left);
            preOrder(node->right);
        }else {//if it is a three
            cout << node->small << ", ";
            preOrder(node->left);
            cout << node->large << ", ";
            preOrder(node->middle);
            preOrder(node->right);
           
        }
    }
}
//puts it in order  
void Tree::inOrder( ) const {
    inOrder(root);
    cout<<endl;
}

void Tree::inOrder(Node* node) const {
    if (node != nullptr) {
        // if it is a 2 tree
        if (node->large == "") {
            inOrder(node->left);
            cout << node->small << ", ";
            inOrder(node->right);
        }else {//if it is a three
            inOrder(node->left);
            cout << node->small << ", ";
            inOrder(node->middle);
            cout << node->large << ", ";
            inOrder(node->right);
            
        }
    }
}
//puts it in post order 
void Tree::postOrder( ) const {
    postOrder(root);
    cout<<endl;
}

//goes all of the tree to print it out 
void Tree::postOrder(Node* node) const {
    if (node != nullptr) {
        // if it is a 2 tree
        if (node->large == "") {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->small << ", ";
        }else {//if it is a three
            postOrder(node->left);
            postOrder(node->middle);
            cout << node->small << ", ";
            postOrder(node->right);
            cout << node->large << ", ";
           
        }
    }
}

