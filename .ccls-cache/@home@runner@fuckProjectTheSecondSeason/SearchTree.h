#ifndef SearchTree_H
#define SearchTree_H

typedef struct _treenode
{
  int data, balance, height;
  struct _treenode* left;
  struct _treenode* right;
} TREENODE_T;


TREENODE_T* newNodeCreate(int data);

void InsertNodeToBinaryTree(TREENODE_T* root, TREENODE_T* newNode);

void postOrder(TREENODE_T* node);

void fillHeight(TREENODE_T* node);

void fillBalanceFactor(TREENODE_T* node);

#endif