#include <iostream>
#include "Tree.h"

using namespace std;

Tree::Tree() : root(0) {}

Tree::~Tree( ) {
    
}



void Tree::insert(Node* current, const string& word) {
    Node* left = nullptr;
    Node* leftMid = nullptr;
    Node* rightMid = nullptr;
    Node* right = nullptr;
    
    if (current == nullptr) { // empty tree, create new root
        root = new Node(word);
        return;
    }

    // Check if word should be inserted in the left subtree
    if (word < current->small) {
        if (current->left == nullptr) { // empty left child
            if (current->large == "") { // there is no large value, insert here
                current->large = current->small;
                current->small = word;
                return;
            }
            else { // split current node
                split(current, left, word, "right");
                return;
            }
        }
        else { // recursively insert in left subtree
            insert(current->left, word);
            return;
        }
    }

    // Check if word should be inserted in the right subtree
    if (word > current->large) {
        if (current->right == nullptr) { // empty right child
            insert(current->right, word);
            return;
        }
        else { // recursively insert in right subtree
            insert(current->right, word);
            return;
        }
    }

    // Word should be inserted in the middle subtree
    if (current->middle == nullptr) { // empty middle child
        split(current, left, word, "right");
        return;
    }
    else { // recursively insert in middle subtree
        insert(current->middle, word);
        return;
    }
}

void Tree::split(Node* n, Node* other, const string& s, string where) {
    bool setRoot = false;
    Node* p = nullptr;
    Node* n1 = nullptr;
    Node* n2 = nullptr;
    Node* n3 = nullptr;
    Node* temp = new Node("");

    if (n->small == root->small) {
        p = new Node("");
        setRoot = true;
    } else {
        p = n->parent;
    }

    if (s < n->small) {
        n1 = new Node(s);
        n2 = new Node(n->small);
        n3 = new Node(n->large);
    } else if (s > n->small && s < n->large) {
        n1 = new Node(n->small);
        n2 = new Node(s);
        n3 = new Node(n->large);
    } else {
        n1 = new Node(n->small);
        n2 = new Node(n->large);
        n3 = new Node(s);
    }

    n->parent = nullptr;
    n1->parent = p;
    n3->parent = p;

    if (n->left != nullptr) {
        if (where == "left") {
            n1->left = other->left;
            other->left->parent = n1;
            n1->right = other->right;
            other->right->parent = n1;
            n3->left = n->middle;
            n->middle->parent = n3;
            n3->right = n->right;
            n->right->parent = n3;
        } else if (where == "middle") {
            n1->left = n->left;
            n->left->parent = n1;
            n1->right = other->left;
            other->left->parent = n1;
            n3->left = other->right;
            other->right->parent = n3;
            n3->right = n->right;
            n->right->parent = n3;
        } else if (where == "right") {
            n1->left = n->left;
            n->left->parent = n1;
            n1->right = n->middle;
            n->middle->parent = n1;
            n3->left = other->left;
            other->left->parent = n3;
            n3->right = other->right;
            other->right->parent = n3;
        } else {
            cout << "Error: Invalid input for 'where' parameter" << endl;
        }
    }

    temp->left = n1;
    temp->right = n3;
    string x = n2->small;

    if (p->hasLarge()) {
        split(p, temp, x, where);
    } else {
        if (p->small.empty()) {
            p->small = x;
        } else if (x < p->small) {
            p->large = p->small;
            p->small = x;
        } else {
            p->large = x;
        }
    }

    if (p->left == nullptr) {
        p->left = temp->left;
        p->right = temp->right;
    } else if (p->left->small == n->small) {
        p->left = temp->left;
        p->middle = temp->right;
    } else if (p->right->small == n->small) {
        p->middle = temp->left;
        p->right = temp;
    }
    
    
    if(setRoot){
        p->left = n1;
        p->right = n3;
        root = p;
    }   
}

void Tree::remove(const string &s) {

}

bool Tree::search(const string &word) const {
    return search(root, word);
}



bool Tree::search(Node* start ,const string &data) const{
    if(start == nullptr){
        return false;
    }

	if(start->small == data || start->large == data){
		
		if(data > start->large){
			return getSearchNode(start->right,data);
		}else if(data > start->small) {
			return getSearchNode(start->left,data);
		}else{
             return search(start->middle, word);
        }
		
	}else{
		return true;
	}
}







void Tree::preOrder(Node* root) const {
    if (root == 0) {
        return;
    }
    cout << root->small << " "; //not sure
    cout << root->large << " "; //not sure
    preOrder(root->left);
    preOrder(root->middle);
    preOrder(root->right);
}
void Tree::preOrder( ) const {
    preOrder(root);
    cout << endl;
}

void Tree::inOrder(Node* root) const {
    if (root == 0) {
        return;
    }
    inOrder(root->left);
    cout << root->small << " ";
    inOrder(root->middle);
    cout << root->large << " ";
    inOrder(root->right);
}  
void Tree::inOrder( ) const {
    inOrder(root);
    cout << endl;    
}

void Tree::postOrder(Node* root) const {
    if (root == 0) {
        return;
    }    
    postOrder(root->left);
    postOrder(root->middle);
    postOrder(root->right);
    cout << root->small << " "; //not sure
    cout << root->large << " "; //not sure
    
}  

void Tree::postOrder( ) const {
    postOrder(root);
    cout << endl;    
}
