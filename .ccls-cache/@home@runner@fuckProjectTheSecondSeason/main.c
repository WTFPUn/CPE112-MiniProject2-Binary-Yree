
#include <stdio.h>
#include <string.h>
#include "Tree.h"

#define n 100
void nodeSort(TREENODE_T *NodeArray[], int id, int cnt) {
  
for (int step = 0; step < cnt - 1; ++step) {
    for (int i = 0; i < cnt - step - 1; ++i) {
      TREENODE_T *a = NodeArray[i];
      char *outA = id == 0 ?  NodeArray[i]->name : (id == 1 ? NodeArray[i]->province : id == 2 ? NodeArray[i]->subProv : id == 3 ? NodeArray[i]->tel : NULL);
      char *outB = id == 0 ?  NodeArray[i+1]->name : (id == 1 ? NodeArray[i+1]->province : id == 2 ? NodeArray[i+1]->subProv : id == 3 ? NodeArray[i+1]->tel : NULL);

      if (strcmp(outA, outB) > 0) {
        TREENODE_T *temp = NodeArray[i];
        NodeArray[i] = NodeArray[i+1];
        NodeArray[i+1] = temp;
      }
    }
  }
}



int main(int argc, char **argv) {
  FILE *fp;
  char temp[100], *fileName, *token;
  int j = 0, currentnode = 0, id = 1;
  TREENODE_T* root;
  TREENODE_T* N[n];

  fileName = argc > 1 ? argv[1] : "test.csv";
  fp = fopen(fileName, "r+");
  while(fgets(temp, 60, fp) != NULL) {
    
    N[currentnode] = newNodeCreate();
    N[currentnode]->name = strdup(strtok(temp, ","));
    N[currentnode]->province = strdup(strtok(NULL, ","));
    N[currentnode]->subProv = strdup(strtok(NULL, ","));
    N[currentnode]->tel = strdup(strtok(NULL, "\n"));
    // getData(N[currentnode]);
    currentnode++;
    
  }
  currentnode--;
  fclose(fp);
  // printf("%s\n%s\n%s\n%s\n", N[currentnode]->name, N[currentnode]->province, N[currentnode]->subProv, N[currentnode]->tel);
// getData(N[12]);
  printf("---------BEFORE SORT ------------\n");
  for(int j = 0; j <= currentnode; j++) {
    getData(N[j]);
  }
  printf("--------------------------------\n");
  
  nodeSort(N, id, currentnode+1);
// getData(N[12]);
  
  int half = currentnode/2;

  printf("---------AFTER SORT ------------\n");
  for(int j = 0; j <= currentnode; j++) {
    getData(N[j]);
  }
  printf("--------------------------------\n");
  
  root = N[half];
  // getData(root);
  for(int i = 0; i <= currentnode; i++) {
    i != half ? InsertNodeToBinaryTree(root, N[i], id) : printf("");
    // InsertNodeToBinaryTree(root, N[i], 3);
  }
  
  // breadthSearch(root, id);
  // postOrder(root, 3);
  
  return 0;
}