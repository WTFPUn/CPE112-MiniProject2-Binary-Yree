
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"


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
  // 0 = Sort by name, 1 = sort by Province, 2 = sort by subprovince, 3 = sort by Telephone number 
  TREENODE_T *p, *previous;

  char *sortCat = sortType == 0 ?  newNode->name : (sortType == 1 ? newNode->province : sortType == 2 ? newNode->subProv : sortType == 3 ? newNode->tel : NULL);
  if(root == NULL)
  {
    root = newNode;
    // printf("root1 = %d\n",root->data);
  }
  else
  {  
    previous = root;
    char *prevCat = sortType == 0 ?  previous->name : (sortType == 1 ? previous->province : sortType == 2 ? previous->subProv : sortType == 3 ? previous->tel : NULL);
    int end = 0;
    do{
      end = 0; 
      if(strcmp(sortCat, prevCat) < 0) { 
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
    }while(end == 1);
  }    
}




void postOrder(TREENODE_T* node)
{
          // 40
       // 32
    //28    35
  if(node->left != NULL)
    postOrder(node->left);
  if(node->right != NULL)
    postOrder(node->right);
  fillHeight(node);
  fillBalanceFactor(node);
  // printf("Access data: %d Height: %d Balance Factor: %d\n", node->data, node->height, node->balance );
}

void fillHeight(TREENODE_T* node)
{

          // 40
       // 32
    //28    35
  int height = 0;
  if(node->left != NULL)
    fillHeight(node->left);
  if(node->right != NULL)
    fillHeight(node->right);
  if(node->left == NULL && node->right == NULL)
    height = 0;
  else if(node->left == NULL)
    height = node->right->height+1;
  else if(node->right == NULL)
    height = node->left->height+1;
  else if(node->right->height > node->left->height)
    height = node->right->height+1;
  else
    height = node->left->height+1;
  
  node->height = height;
}

void getDataByCol(TREENODE_T* node, char* out, char col[]) {
}

void setDataByCol(TREENODE_T* node, char* out, char col[]) {
  
}
void fillBalanceFactor(TREENODE_T* node) {

  int leftHeight = 0, rightHeight = 0;
  if(node->left != NULL)
    fillBalanceFactor(node->left);
  if(node->right != NULL)
    fillBalanceFactor(node->right);

  //Get the height of the left sub-tree
  if(node->left == NULL)
    leftHeight = 0 ;
  else
    leftHeight = node->left->height+1;
  //Get the height of the right sub-tree
  if(node->right == NULL)
    rightHeight = 0;
  else
    rightHeight = node->right->height+1;
  
  node->balance = leftHeight - rightHeight;
}




