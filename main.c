#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.h"

#define n 100

void addRow(TREENODE_T *root, TREENODE_T **N, int *currentnode, int id){
  if(*currentnode >= 100){
      printf("Your data has reached the limit (max of rows is 100)");
      *currentnode-=1;
      return;
  }
  printf("Add Information in this format => name,province,subprovince,tel\n");
  char temp[100], *name, *prov, *subprov, *tel;
  fgets(temp, 60, stdin);
  name = strdup(strtok(temp, ","));
  if(!strcmp(name,"\0")) return;
  prov = strdup(strtok(NULL, ","));
  if(!strcmp(prov,"\0")) return;
  subprov = strdup(strtok(NULL, ","));
  if(!strcmp(subprov,"\0"))  return;
  tel = strdup(strtok(NULL, "\n"));
  if(!strcmp(tel,"\0"))  return;
  N[*currentnode] = newNodeCreate();
  N[*currentnode]->name = strdup(name);
  N[*currentnode]->province = strdup(prov);
  N[*currentnode]->subProv = strdup(subprov);
  N[*currentnode]->tel = strdup(tel);
  InsertNodeToBinaryTree(root, N[*currentnode], id);
}

void addFile(TREENODE_T *root, TREENODE_T **N, int *currentnode) {
  FILE *fp; 
  char temp[100], fileName[100];
  printf("Add Filename\n");
  fgets(fileName, 60, stdin);
  int len = strlen(fileName);
  fileName[len-1] = '\0';
  fp = fopen(fileName, "r+");
  while(fgets(temp, 60, fp) != NULL) {
    if(*currentnode >= 100){
      printf("Your data has reached the limit (max of rows is 100)");
      *currentnode-=1;
      return;
    }
    N[*currentnode] = newNodeCreate();
    N[*currentnode]->name = strdup(strtok(temp, ","));
    N[*currentnode]->province = strdup(strtok(NULL, ","));
    N[*currentnode]->subProv = strdup(strtok(NULL, ","));
    N[*currentnode]->tel = strdup(strtok(NULL, "\n"));
    *currentnode+=1; 
  }
  fclose(fp);
  *currentnode-=1;
}

void SearchByCol(TREENODE_T *node, int id, char *key) {
  char* out = id == 0 ?  node->name : (id == 1 ? node->province : id == 2 ? node->subProv : id == 3 ?node->tel : NULL);
   if (strstr(out, key) != NULL)
    getData(node);
  if (node->left != NULL)
    SearchByCol(node->left, id, key);
  if (node->right != NULL)
    SearchByCol(node->right, id, key);
}

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
//nan
int getint(char min, char max){
  char ch, num;
  while(scanf("%c%c", &num, &ch) == 0 || (ch != ' ' && ch != '\n') || num < min || num > max){
    rewind(stdin);
    printf("!INVALID NUMBER!\n");
    printf("Please Select (%c - %c) Again : \n", min, max);
  }
  return num;
}
//nan
int get_menu(){
  char select;
  printf("============================================\n");
  printf(">                  THE MENU                <\n");
  printf("============================================\n");
  printf(">         1. ADD DATA                      <\n");
  printf(">         2. SORT & SHOW DATA              <\n");
  printf(">         3. SEARCH DATA                   <\n");
  printf(">         0. EXIT                          <\n");
  printf("============================================\n");
  printf("SELECT THE MENU : ");
  //เรียกใช้ฟังก์ชัน getint() เพื่อรับค่าตัวเลขที่อยู่ระหว่าง
  select = getint('0', '3'); 
  return select;
}

int main(int argc, char **argv) {
  FILE *fp;
  char temp[100], *fileName, *token;
  int j = 0, currentnode = 0, id = 0;

  TREENODE_T* root;
  TREENODE_T* N[n];
  
  char select;
  system("clear");
  do{
      char key1[15];
      rewind(stdin); 
        
      select = get_menu(); //เรียกใช้ฟังก์ชัน getmenu() เพื่อเลือกเมนูที่ต้องการทำงาน
      system("clear");
      if(select == '1'){ // เลือกเมนู ADD DATA
        printf("============================================\n");
        printf(">                1.ADD DATA                <\n");
        printf("============================================\n");
        printf(">              a. ADD 1 ROW                <\n");
        printf(">              b. LOAD FILE                <\n");
        printf(">              c. BACK TO MAIN MENU        <\n");
        printf("============================================\n");
        printf("SELECT THE MENU : ");
        char selectAdd = getint('a', 'c');
        system("clear");
        //เรียกใช้ฟังก์ชัน addRow()
        if(selectAdd == 'a') {
          currentnode+=1;
          addRow(root, N, &currentnode, id);
        }
        else if(selectAdd == 'b') {
          addFile(root, N, &currentnode);
        }
        else if(selectAdd == 'c') {
          continue;
        }
      }
      else if(select == '2'){ // เลือกเมนู SORT & SHOW DATA
      
        printf("============================================\n");
        printf(">            2.SORT & SHOW DATA            <\n");
        printf("============================================\n");
        printf(">            a. SORT BY NAME               <\n");
        printf(">            b. SORT BY PROVINCE           <\n");
        printf(">            c. SORT BY SUBPROVINCE        <\n");
        printf(">            d. SORT BY TELEPHONE NUMBER   <\n");
        printf(">            e. BACK TO MAIN MENU.         <\n");
        printf("============================================\n");
        printf("SELECT THE MENU : ");
        char selectSort = getint('a', 'e');
        system("clear");
        if(selectSort == 'a') {
          //SORT BY NAME : id = 0 
          nodeSort(N, id, currentnode);
          for(int i = 0; i < currentnode; i++) {
            getData(N[i]);
          }
          
        }
        else if(selectSort == 'b') {
          //SORT BY PROVINCE : id = 1
          nodeSort(N, id, currentnode);
          for(int i = 0; i < currentnode; i++) {
            getData(N[i]);
          }
        }
        else if(selectSort == 'c') {
          //SORT BY SUBPROVINCE : id = 2
          nodeSort(N, id, currentnode);
          for(int i = 0; i < currentnode; i++) {
            getData(N[i]);
          }
        }
        else if(selectSort == 'd') {
          //SORT BY TELEPHONE NUMBER : id = 3
          nodeSort(N, id, currentnode);
          for(int i = 0; i < currentnode; i++) {
            getData(N[i]);
          }
        }
        else if(selectSort == 'e') {
          continue;
        }
        
      }
      else if(select == '3') { // เลือกเมนู SEARCH BY NAME
        //เปลี่ยน id = 0
        printf("============================================\n");
        printf(">                3.SEARCH DATA             <\n");
        printf("============================================\n");
        printf(">            a. SEARCH BY NAME             <\n");
        printf(">            b. SEARCH BY PROVINCE         <\n");
        printf(">            c. SEARCH BY SUBPROVINCE      <\n");
        printf(">            d. SEARCH BY TELEPHONE NUMBER <\n");
        printf(">            e. BACK TO MAIN MENU.         <\n");
        printf("============================================\n");
        printf("SELECT THE MENU : ");
        char selectSearch = getint('a', 'e');
        system("clear");
        if(selectSearch == 'a') {
           
        }
        else if(selectSearch == 'b') {
          
        }
        else if(selectSearch == 'c') {
          
        }
        else if(selectSearch == 'd') {
          
        }
        else if(selectSearch == 'e') {
          continue;
        }
      
      }
    }while (select != '0');
  printf("================= End program ==============\n"); 
  return 0;
}