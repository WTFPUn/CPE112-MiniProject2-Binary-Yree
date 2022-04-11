#include <stdio.h>
#include <string.h>
#include "Tree.h"

#define n 51
#define defaultFile "test.csv"

int main(int argc, char **argv) {
  FILE *fp;
  char temp[30];
  int j = 0, currentnode = 0;
  TREENODE_T* root;
  TREENODE_T* N[n];
  
  fp = fopen("test.csv","r+");
  // printf("%d", feof(fp));
  while(fgets(temp, 60, fp) != NULL) {
    printf("%s", temp);
  }
  fclose(fp);
  return(0);
}