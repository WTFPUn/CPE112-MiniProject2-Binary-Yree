#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "queue.h"


TREENODE_T* newNodeCreate() {
  TREENODE_T* tree = (TREENODE_T*) calloc(1, sizeof(TREENODE_T));
    if (tree == NULL) {
        return NULL;
    }
    tree->name = "";
    tree->province = "";
    tree->subProv = "";
    tree->tel = "";
    tree->left = NULL;
    tree->right = NULL;
    // printf("%d\n", tree->data);
    return tree;
}

void InsertNodeToBinaryTree(TREENODE_T* root, TREENODE_T* newNode, int sortType) {
  
  TREENODE_T *p, *previous;

  char *sortCat = sortType == 0 ?  newNode->name : (sortType == 1 ? newNode->province : sortType == 2 ? newNode->subProv : sortType == 3 ? newNode->tel : NULL);
  if(root == NULL) {
    root = newNode;
    // getData(root);
    // printf("root1 = %d\n",root->data);
  }
  else {
    previous = root;
    char *prevCat = sortType == 0 ?  previous->name : (sortType == 1 ? previous->province : sortType == 2 ? previous->subProv : sortType == 3 ? previous->tel : NULL);
    int end = 0;
    do{
      end = 0; 
      if(strcmp(sortCat, prevCat) <= 0) { 
        if(previous->left == NULL){
          previous->left = newNode;
          // printf("newnode.left = %d\n",newNode->data);
        }
        else{
          previous = previous->left;
          end = 1;
        }
      }
      else if(strcmp(sortCat, prevCat) > 0) {
        if(previous->right == NULL)
        {
          previous->right = newNode;
          // printf("newnode.right = %d\n",newNode->data);  
        }
        else
        {
          previous = previous->right;
          end = 1;
        }
      }
      // printf("root = %d\n",root->data);
      // printf("StepBro\n");
    } while(end == 1);
  }
  // getData(newNode);
  // printf("NodeInserted\n");
}

void getData(TREENODE_T* node) {
  printf("%s, %s, %s, %s\n", node->name, node->province, node->subProv, node->tel);
}

void SearchByCol(TREENODE_T *node, int id, char *key) {
  char* out = id == 0 ?  node->name : (id == 1 ? node->province : id == 2 ? node->subProv : id == 3 ? node->tel : NULL);
  if(strstr(out, key) != NULL)
      getData(node);
  if (node->left != NULL)
    SearchByCol(node->left, id, key);
  if (node->right != NULL)
    SearchByCol(node->right, id, key);
}

