#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &); 
  bool search (const string &) const;
  void shiftUp(Node*);
  void deleteTree(Node*);
  Tree& operator =(const Tree&)= delete;
  Tree(const Tree&)=delete;
  //Node* findSuccessorNode(Node* node);
private:
  void preOrder(Node* curr) const;
  Node* search (Node* curr, const string &) const;
  void inOrder(Node* curr) const;
  void postOrder(Node* curr) const;
  //Node* delAll(Node*);
  
};
#endif
