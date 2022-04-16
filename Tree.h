#ifndef Tree_H
#define Tree_H

typedef struct _treenode
{
  int balance, height;
  char *name, *province, *subProv, *tel;
  struct _treenode* left;
  struct _treenode* right;
} TREENODE_T;

TREENODE_T* newNodeCreate();

void getDataByCol(TREENODE_T* node, char* out, char col[]);

void setDataByCol(TREENODE_T* node, char* out, char col[]);

void InsertNodeToBinaryTree(TREENODE_T* root, TREENODE_T* newNode, int sortType);

void postOrder(TREENODE_T* node);

void fillHeight(TREENODE_T* node);

void fillBalanceFactor(TREENODE_T* node);

#endif