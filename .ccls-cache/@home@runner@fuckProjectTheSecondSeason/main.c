#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXCHAR 1000

int main(int argc, char **argv) {
  FILE *fp;
   int c;

   fp = fopen(argv[1],"w+");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) {
         break;
      }
      printf("%c", c);
   }
   fclose(fp);
   return(0);
}