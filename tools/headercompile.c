#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include "include/setup.h"

// prepare data
// recursive get .lul files
// gettextfrom let file
// split \n from lultext
// double backslashe in lultext

// write headers
// open header file
// if exist make backup
// wrate new lultext in #defines
// colse new header file

int main(){
  char headDirPath[PATH_MAX + 1] = PROJ_PATH;
  strcat(headDirPath, "/resources/head");

  // Get open head DIR /head
  DIR *head;
  head = opendir(headDirPath);
  if ( head == NULL) {
    printf("Cannot open dir\n");
    return -1;
  }

  // ls dir
  struct dirent *headent;
  /*printf("headent[0]: %s", headent->d_name);*/
  while ((headent = readdir(head)) != NULL) {
    if (!strcmp(headent->d_name, ".")|| !strcmp(headent->d_name, "..") || (int)headent->d_type == 8){
      //no op
    } else {
      printf ("name: [%s]\n", headent->d_name);
      printf ("type: [%d]\n", headent->d_type);

      char innerDirPath[PATH_MAX + 1];
      strcpy(innerDirPath, headDirPath);
      strcat(innerDirPath, "/");
      strcat(innerDirPath, headent->d_name);

      printf("innerDirPath: %s\n", innerDirPath);

      DIR *innerDir;
      innerDir = opendir(innerDirPath);
      if ( innerDir == NULL ){
        printf("Cannot open dir innerDir\n");
        return -1;
      }
      
      struct dirent *innerDent;
      while((innerDent = readdir(innerDir)) != NULL){
        if (!strcmp(innerDent->d_name, ".")|| !strcmp(innerDent->d_name, "..") || (int)innerDent->d_type == 4){
          // no op
        } else {
          
          // constreact part filepath
          printf("    file: %s\n", innerDent->d_name);
          char headPartPath[PATH_MAX + 1];
          /*char headPartFileName[PATH_MAX + 1];*/
          strcpy(headPartPath, innerDirPath);
          strcat(headPartPath, "/");
          strcat(headPartPath, innerDent->d_name);
          printf("    filePath: %s\n", headPartPath);

          // open part file
          FILE *headPartFile = fopen(headPartPath, "r");
          fseek(headPartFile, 0L, SEEK_END);
          int headPartSize = ftell(headPartFile);
          printf("    fileSize: %d\n", headPartSize);
          rewind(headPartFile);

          // read part conents
          char headPartContents[headPartSize +1];
          fread(headPartContents, headPartSize, 1, headPartFile);
          headPartContents[++headPartSize] = '\0';
          printf("    fileConents:\n%s\n", headPartContents);

          // split part contents by \n
          char headPartLines[10][250]; 
          int linecount = 0;
          int lineIndex = 0;
          for (int i=0; headPartContents[i] != '\0'; i++){
            /*printf("headpartcontents[i] %c\n", headPartContents[i]);*/
            /*printf("               int: %d\n", headPartContents[i]);*/
            if (headPartContents[i] != '\n'|| headPartContents[i] != '\0'){
              if (headPartContents[i] == '\\'){
                headPartLines[linecount][lineIndex] = '\\';
                headPartLines[linecount][++lineIndex] = '\\';
              } else {
                headPartLines[linecount][lineIndex] = headPartContents[i] ;
              /*printf("hpl[%d][%d]: %c\n", linecount, lineIndex, headPartContents[i]);*/
                lineIndex++;
              }
            } else {
              headPartLines[linecount][++lineIndex] = '\0';
              printf("    ine num[%d]: %s\n", linecount, headPartLines[linecount]);
              linecount++;
              lineIndex = 0;
            }
          }
          fclose(headPartFile);

          // open par header
          /*char *partHeaderPath[PATH_MAX + 1] = PROJ_PATH;*/
          /*strcat(partHeaderPath, "/tools/include/");*/

          char *headPartFileName = innerDent->d_name;
          int headPartFNLen = strlen(headPartFileName);

          char partname[headPartFNLen - 3];
          strncpy(partname, headPartFileName, headPartFNLen -4);
          partname[headPartFNLen -4] = '\0';
          /*strcpy(headPartFileName, innerDirPath); */
          printf("headPartFileName: %s\n", headPartFileName);
          printf("headPartFNLen: %d\n", headPartFNLen);
          printf("partname: %s\n", partname);
          /*int lulpathLen = strlen(headPartPath);*/
          /*FILE *partHeaderFile = fopen(partHeaderPath, "w+");*/
          // write part header
          // close part header
        }
      }
      closedir(innerDir); 
    }

  }

  /*printf("dir serail numer: %s", headent->d_name[0]);*/
  closedir(head);

  return 0;
}
