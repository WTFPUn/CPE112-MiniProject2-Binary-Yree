#include <stdio.h>
#include <stdlib.h>
#include "SearchTree.h"


TREENODE_T* newNodeCreate(int data)
{
  TREENODE_T* tree = (TREENODE_T*) calloc(1, sizeof(TREENODE_T));
    if (tree == NULL)
    {
        return NULL;
    }
    
    tree->data = data;
    tree->balance = 0;
    tree->height = 0;
    tree->left = NULL;
    tree->right = NULL;
    // printf("%d\n", tree->data);
    return tree;
}

void InsertNodeToBinaryTree(TREENODE_T* root, TREENODE_T* newNode)
{
  TREENODE_T *p, *previous;
  
  if(root == NULL)
  {
    root = newNode;
    // printf("root1 = %d\n",root->data);
  }
  else
  {  
    previous = root;
    int end = 0;
    do{
      end = 0; 
      if(newNode->data < previous->data)
      { 
        if(previous->left == NULL){
          previous->left = newNode;
          // printf("newnode.left = %d\n",newNode->data);
        }
        else{
          previous = previous->left;
          end = 1;
        }
      }
      else if(newNode->data > previous->data)
      {
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
  printf("Access data: %d Height: %d Balance Factor: %d\n", node->data, node->height, node->balance );
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

void fillBalanceFactor(TREENODE_T* node)
{
          // 40
       // 32
    //28      35
  //.    30
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




