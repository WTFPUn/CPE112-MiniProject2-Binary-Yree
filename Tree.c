
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
  // 0 = Sort by name, 1 = sort by Province, 2 = sort by subprovince, 3 = sort by Telephone number 
  TREENODE_T *p, *previous;

  char *sortCat = sortType == 0 ?  newNode->name : (sortType == 1 ? newNode->province : sortType == 2 ? newNode->subProv : sortType == 3 ? newNode->tel : NULL);
  if(root == NULL) {
    root = newNode;
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
    }while(end == 1);
  }    
}

void getData(TREENODE_T* node) {
  printf("%s, %s, %s, %s\n", node->name, node->province, node->subProv, node->tel);
}


void postOrder(TREENODE_T* node, int id) {
  char* out = id == 0 ?  node->name : (id == 1 ? node->province : id == 2 ? node->subProv : id == 3 ?node->tel : NULL);
  if(node->left != NULL)
    postOrder(node->left, id);
  if(node->right != NULL)
    postOrder(node->right, id);
  fillHeight(node);
  fillBalanceFactor(node);
  printf("Access data: %s \n", out);
}

void PreOrder (TREENODE_T* node, int id)
{
  char* out = id == 0 ?  node->name : (id == 1 ? node->province : id == 2 ? node->subProv : id == 3 ?node->tel : NULL);
  printf("Access %s\n", out);
  if (node->left != NULL)
  PreOrder(node->left, id);
  if (node->right != NULL)
  PreOrder(node->right, id);

}

void InOrder (TREENODE_T* node, int id) {
  char* out = id == 0 ?  node->name : (id == 1 ? node->province : id == 2 ? node->subProv : id == 3 ?node->tel : NULL);
  if (node->left != NULL)
  InOrder(node->left, id);
  printf("Access %s\n", out);
  if (node->right != NULL)
  InOrder(node->right, id);

}

void fillHeight(TREENODE_T* node)
{
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

int breadthSearch (TREENODE_T* node, int sortType) {
  int count = 0;
  
  if(node == NULL)
    return -1;
  
  QUEUE_T* queue =  queueCreate(10); 
  
  queueEnqueue(queue, node);
  while(queue->count != 0) 
  {
    if(queue->data[queue->headIndex]->left != NULL)
      queueEnqueue(queue, queue->data[queue->headIndex]->left);
    if(queue->data[queue->headIndex]->right != NULL)
      queueEnqueue(queue, queue->data[queue->headIndex]->right);
    char* out = sortType == 0 ?  queue->data[queue->headIndex]->name : (sortType == 1 ? queue->data[queue->headIndex]->province : sortType == 2 ? queue->data[queue->headIndex]->subProv : sortType == 3 ? queue->data[queue->headIndex]->tel : NULL);
    printf("Access %s\n", out);
    queueDequeue(queue);
  }

   queueDestroy(queue);

  return 1;
}


