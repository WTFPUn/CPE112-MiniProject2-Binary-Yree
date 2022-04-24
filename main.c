#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.h"

#define n 100
int insertcnt = 0;

void addRow(TREENODE_T *root, TREENODE_T **N, int *currentnode, int id){
  if(*currentnode >= 100){
      printf("Your data has reached the limit (max of rows is 100)");
      *currentnode-=1;
      return;
  }
  printf("ADD INFORMATION \n[Ex. Bee,Bangkok,Tungkru,0111111111]\n");
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
  printf("DATA ADDING SUCCESSFUL!\n");
  //*currentnode = *currentnode != 0 ? *currentnode + 1 : *currentnode;
  // if(N[*currentnode] != NULL)    *currentnode+=1;
  N[*currentnode] = newNodeCreate();
  N[*currentnode]->name = strdup(name);
  N[*currentnode]->province = strdup(prov);
  N[*currentnode]->subProv = strdup(subprov);
  N[*currentnode]->tel = strdup(tel);
  getData(N[*currentnode]);
  //*currentnode = *currentnode != 0 ? *currentnode : *currentnode + 1;
}

void addFile(TREENODE_T *root, TREENODE_T **N, int *currentnode, int id) {
  FILE *fp; 
  char temp[100], fileName[100];
  printf("ADD FILENAME\n");
  fgets(fileName, 60, stdin);
  int len = strlen(fileName);
  fileName[len-1] = '\0';
  fp = fopen(fileName, "r+");  
  // *currentnode = *currentnode != 0 ? *currentnode + 1 : *currentnode;
  // if(N[*currentnode]!= NULL)    *currentnode+=1;
  while(fgets(temp, 60, fp) != NULL) {
    if(*currentnode >= 100){
      printf("Your data has reached the limit (max of rows is 100)\n");
      *currentnode-=1;
      return;
    }
    N[*currentnode] = newNodeCreate();
    N[*currentnode]->name = strdup(strtok(temp, ","));
    N[*currentnode]->province = strdup(strtok(NULL, ","));
    N[*currentnode]->subProv = strdup(strtok(NULL, ","));
    N[*currentnode]->tel = strdup(strtok(NULL, "\n"));  
    getData(N[*currentnode]);
    *currentnode+=1;
  }
  fclose(fp);
  *currentnode-=1;
  rewind(stdin);
}



void nodeSort(TREENODE_T *NodeArray[], int id, int cnt) {
  for (int step = 0; step < cnt - 1 ; ++step) {
    for (int i = 0; i < cnt - step - 1 ; ++i) {
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

int getint(char min, char max){
  char ch = '\0', num = '\0';
  while(scanf(" %c%c", &num, &ch) == 0 || (ch != ' ' && ch != '\n') || num < min || num > max){
    rewind(stdin);
    printf("!INVALID NUMBER!\n");
    printf("Please Select (%c - %c) Again : \n", min, max);
  }
  return num;
}

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
  int j = 0, currentnode = 0, id = 0, cnt=0;
  char check;  
  TREENODE_T* N[n];
  TREENODE_T* root = NULL;
  
  char select;
  system("clear");
  do{

      rewind(stdin); 
      select = '\0';
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
        int i = currentnode;
        if(cnt != 0) 
          currentnode+=1;
        if(selectAdd == 'a') {
          addRow(root, N, &currentnode, id);
          //root = N[currentnode/2];
          InsertNodeToBinaryTree(root, N[currentnode], 0);
          cnt++;
        }
        else if(selectAdd == 'b') {
          addFile(root, N, &currentnode, id);
          root = N[currentnode/2];
          for(; i < currentnode;i++) 
            i != currentnode/2 ? InsertNodeToBinaryTree(root, N[i], 0) : printf("");
          cnt++;
        }
        else if(selectAdd == 'c') {
          continue;
        }        
      }
      else if(select == '2') { // เลือกเมนู SORT & SHOW DATA
      
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
        rewind(stdin);
        system("clear");
        
        if(selectSort == 'e') continue;
        selectSort == 'a' ? nodeSort(N, 0, currentnode+1) : selectSort == 'b' ? nodeSort(N, 1, currentnode+1) : selectSort == 'c' ? nodeSort(N, 2, currentnode+1) : selectSort == 'd' ? nodeSort(N, 3, currentnode+1) : printf("");  
        
        for(int i = 0; i <= currentnode; i++)
            getData(N[i]);
        do {
          printf("Please Enter 'y' to MAIN MENU: ");
          check = getchar();
          rewind(stdin);
        } while(check != 'y');
        if(check == 'y') {
          rewind(stdin);
          system("clear");
          continue;
        }
      }
      else if(select == '3') { // เลือกเมนู SEARCH BY NAME
        printf("============================================\n");
        printf(">                3.SEARCH DATA             <\n");
        printf("============================================\n");
        printf(">         a. SEARCH BY NAME                <\n");
        printf(">         b. SEARCH BY PROVINCE            <\n");
        printf(">         c. SEARCH BY SUBPROVINCE         <\n");
        printf(">         d. SEARCH BY TELEPHONE NUMBER    <\n");
        printf(">         e. BACK TO MAIN MENU             <\n");
        printf("============================================\n");
        printf("SELECT THE MENU : ");
        char selectSearch = getint('a', 'e');
        system("clear");
        char key1[15];        
        if(selectSearch == 'e') continue;        
        printf("ENTER THE KEYWORD: ");
        fgets(key1, 20, stdin);
        key1[strlen(key1) - 1] = '\0';
        printf("The data that have key: %s is. \n", key1);
        selectSearch == 'a' ? SearchByCol(root, 0, key1) : selectSearch == 'b' ? SearchByCol(root, 1, key1) :  selectSearch == 'c' ? SearchByCol(root, 2, key1) : selectSearch == 'd' ? SearchByCol(root, 3, key1) : printf("");
        memset(key1, '\0', sizeof(key1));
      }
      if(select != '0'){
        do{
          printf("Please Enter 'y' to MAIN MENU: ");
          check = getchar();
          rewind(stdin);
        } while(check != 'y');
        if(check == 'y') {
          rewind(stdin);
          system("clear");
          continue;
        }
      }
    } while (select != '0');
  printf("================= End program =================\n"); 
  return 0;
}
//AomZak,Rayong,Mueng,0850080085
//ZomYed,Ranong,Mueng,0860080086