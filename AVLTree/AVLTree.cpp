#include "AVLTree.h" 

using namespace std;
//initilize the root and the tree
AVLTree::AVLTree() {
    root = nullptr;
}

//calls the helper function insert to make a new node from the strig into the tree
void AVLTree::insert(const string &data){
    Node* realData = new Node(data);
    insert(root,realData);
}

// adds a node to the tree in order 
void AVLTree:: insert(Node* cur,Node* node) {
    //checks if its null to set the node to root
    if(root == nullptr) {
        root = node;
        node->parent = nullptr;
        return;
    }

    //cycals through everthing inf the tree to place the node in the trree
    while (cur != nullptr) {
        //if its the same or equal to root than just add to the count 
        if (node->data == cur->data) {
          cur->count++; 
          cur = nullptr;
        }else if (node->data < cur->data ){
            // checks if its on the left side and moves to the left
            if (cur->left == nullptr){
                cur->left = node;
                node->parent = cur;
                cur = nullptr;
            }else {
            cur = cur->left;
            }
        }else{
            //checks the right side and see if its on the right 
            if(cur->right == nullptr) {
                cur->right = node;
                node->parent = cur;
                cur = nullptr;
            }else{
                cur = cur->right;
            }
            
        }
    }

    //calls rotate to mate sure its still a AVL tree thats balents 
    node = node->parent;
    while (node != nullptr) {
        rotate(node);
        node = node->parent;
    }
}

//gives the balence factor 
int AVLTree::balanceFactor(Node *curr) const {
    return height(curr->left) - height(curr->right);
}

//prints it out 
void AVLTree::printBalanceFactors() const {
    printBalanceFactors(root); 
    cout << endl;
} 

//prints out the balense factor all pritty like 
void AVLTree::printBalanceFactors(Node *curr) const {
    if(curr!=nullptr) {
        printBalanceFactors(curr->left); 
        cout << curr->data << "(" << balanceFactor(curr) << "), "; 
        printBalanceFactors(curr->right); 
    }
}

//gives the hight of the tree
int AVLTree::height(Node *curr) const { 
    if (curr==nullptr){
       return -1;
    }
    
    int tHight = 0;
    height(0,tHight,curr); 

    return tHight - 1;
} 

//the recsersive hight function 
void AVLTree::height(int hightCount, int &tHight, Node *curr) const {
    if(curr==nullptr) {
        return;
    }

    hightCount++; 
    if(hightCount > tHight){
        tHight = hightCount;
    }
    //recursively traverse tree
    height(hightCount,tHight,curr->left);
    height(hightCount,tHight,curr->right); 
}


//rotates things to fix the ballence factor 
void AVLTree::rotate(Node *curr) { 
    
    if(balanceFactor(curr) == 2) {
        if(balanceFactor(curr->left) == -1) {
            rotateLeft(curr->left);
        } 
        rotateRight(curr);
    }
    else if(balanceFactor(curr) == -2) {
        if(balanceFactor(curr->right) == 1) { 
            rotateRight(curr->right); 
        } 
        rotateLeft(curr);
    }
}

//rotaies it to the right
void AVLTree::rotateRight(Node *curr) {
    Node *temp = curr->left->right;
    if(curr->parent) {
        replaceChild(curr->parent,curr,curr->left);
    } 
    else {
        root = curr->left; 
        root->parent = 0;
    }
    setChild(curr->left,"right",curr); 
    setChild(curr,"left",temp);
}  

//rotes it left 
void AVLTree::rotateLeft(Node *curr) {
    Node *temp = curr->right->left;
    if(curr->parent) { 
        replaceChild(curr->parent,curr,curr->right);
    } 
    else {
        root = curr->right; 
        root->parent = 0;
    }
    setChild(curr->right,"left",curr); 
    setChild(curr,"right",temp);
} 

//set the child stuff 
void AVLTree::setChild(Node *parent, string whichChild, Node *child) {
    if(whichChild == "left") {
        parent->left = child;
    } 
    else {
        parent->right = child;
    } 
    if(child) {
        child->parent = parent;
    }
}

//repaces the child stuff
void AVLTree::replaceChild(Node *parent, Node *curr,Node *newChild) {
    if(parent->left == curr) {
        setChild(parent,"left",newChild);
    } 
    else if(parent->right == curr) {
        setChild(parent,"right",newChild);
    }
}

//prints the tree
void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
//prints the tree
void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}