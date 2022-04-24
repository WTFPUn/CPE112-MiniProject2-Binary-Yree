#ifndef Tree_H
#define Tree_H

typedef struct _treenode
{
  char *name, *province, *subProv, *tel;
  struct _treenode* left;
  struct _treenode* right;
} TREENODE_T;

TREENODE_T* newNodeCreate();

void getData(TREENODE_T* node);

void InsertNodeToBinaryTree(TREENODE_T* root, TREENODE_T* newNode, int sortType);

void SearchByCol(TREENODE_T *node, int id, char *key);

#endif