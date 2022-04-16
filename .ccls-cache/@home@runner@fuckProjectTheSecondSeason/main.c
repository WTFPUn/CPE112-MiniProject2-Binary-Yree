#include <stdio.h>
#include <string.h>
#include "Tree.h"

#define n 51

int main(int argc, char **argv) {
  FILE *fp;
  char temp[100], *fileName, *token;
  int j = 0, currentnode = 0;
  TREENODE_T* root;
  TREENODE_T* N[n];

  for(int i = 0; i<n;i++) {
    N[i] = newNodeCreate();
  }
  
  fileName = argc > 1 ? argv[1] : "test.csv";
  fp = fopen(fileName, "r+");
  while(fgets(temp, 60, fp) != NULL) {
    // printf("%s", temp);
    //Adam,Bangkok,Tungkru,0123456789
    token = strtok(temp, ",");
    N[currentnode]->name = strdup(token);
    token = strtok(NULL, ",");
    N[currentnode]->province = strdup(token);
    token = strtok(NULL, ",");
    N[currentnode]->subProv = strdup(token);
    token = strtok(NULL, "\n");
    N[currentnode]->tel = strdup(token);
    // fuck this \n
    // printf("Node[%d]: %s %s  %s  %s\n",currentnode , N[currentnode]->name, N[currentnode]->province, N[currentnode]->subProv, N[currentnode]->tel);
    // currentnode++;
  }
  fclose(fp);
  currentnode = 5;
  
  return(0);
}