#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){

  printf("char: %c\n", 'z');
  printf(" int: %d\n", 'z');
  printf("char: %c\n", '\n');
  printf(" int: %d\n", '\n');

  char *ohslup = "slug\nlife";

  for(int i=0; ohslup[i] != '\0'; i++){
    printf("ohslup[%d]: int, %d : char, %c\n", i, ohslup[i], ohslup[i]);
  }

  char *lulpath = "heywahtsup.lul";
  int lulpathLen = strlen(lulpath);
  
  char lulname[lulpathLen - 3];
  strncpy(lulname, lulpath, lulpathLen - 4);
  lulname[lulpathLen - 4] = '\0';
  printf("lulname: %s\n", lulname);

   
  char *uperme = "this better print upper";
  char upr[100];
  for (int i=0; uperme[i] != '\0'; i++){
    printf("%d %c\n", i, uperme[i]);
    upr[i] = toupper(uperme[i]);
  }

  printf("up: %s\n", upr);
}

      /*headerPartFilePath = headent-*/

          /*char partHeaderPath[PATH_MAX +1] = PROJ_PATH;*/
          /*strcat(partHeaderPath, "/tool/include/");  */
          /*strcat(partHeaderPath, partname);*/
            
          /*FILE *partHeaderFile = fopen(partHeaderPath, "w+");*/
