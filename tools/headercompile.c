#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
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

      char headerPartFilePath[PATH_MAX + 1] = PROJ_PATH;
      strcat(headerPartFilePath, "/tools/include/");
      strcat(headerPartFilePath, headent->d_name);
      strcat(headerPartFilePath, ".h");
      printf("headerPartFilePath: %s\n", headerPartFilePath);
      FILE *headerPartFile = fopen(headerPartFilePath, "w");

      fprintf(headerPartFile, "#ifndef _%s_h\n", headent->d_name);
      fprintf(headerPartFile, "#define _%s_h\n\n", headent->d_name);

      
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
          char headPartLines[10][250] = {'\0', '\0', '\0', '\0', '\0',
               '\0', '\0', '\0', '\0', '\0'};
          int linecount = 0;
          int lineIndex = 0;
          for (int i=0; headPartContents[i] != '\0'; i++){
            /*printf("headpartcontents[i] %c\n", headPartContents[i]);*/
            /*printf("               int: %d\n", headPartContents[i]);*/
            if (headPartContents[i] != '\n'){
              if (headPartContents[i] == '\\' && headPartContents[i] != '\0'){
                headPartLines[linecount][lineIndex] = '\\';
                headPartLines[linecount][++lineIndex] = '\\';
                headPartLines[linecount][++lineIndex] = '\\';
              } else if (headPartContents[i] == '\"'){

                headPartLines[linecount][lineIndex] = '\\';
                headPartLines[linecount][++lineIndex] = '\"';
                headPartLines[linecount][++lineIndex] = '\"';
                
              } else {
                headPartLines[linecount][lineIndex] = headPartContents[i] ;
                lineIndex++;
              }
            } else {
              headPartLines[linecount][++lineIndex] = '\0';
              printf("    ine num[%d]: %s\n", linecount, headPartLines[linecount]);
              linecount++;
              lineIndex = 0;
            }
          }

           /*write part header*/
           /*get part name */
          char *headPartFileName = innerDent->d_name;
          int headPartFNLen = strlen(headPartFileName);

          printf("headerpartfilename: %s\n", headPartFileName);
          char partname[headPartFNLen - 3];
          int i=0;
          for (i=0; i < headPartFNLen -4; i++){
            if (headPartFileName[i] == '-'){
              partname[i] = '_';
            } else {
              partname[i] = toupper(headPartFileName[i]);
            }
          }
          partname[headPartFNLen -4] = '\0';
          printf("partname: %s\n", partname);
          char defineVar[400] ="#define ";
          strcat(defineVar, partname);
          printf("definevar: %s\n", defineVar);
          
          for (int i=0; headPartLines[i][0] != '\0'; i++){
            printf("%s_%d \"%s\"\n", defineVar, i, headPartLines[i]);
            fprintf(headerPartFile, "%s_%d \"%s\"\n", defineVar, i, headPartLines[i]);
          }

          /*printf("hpl 0: \"%s\"\n", headPartLines[0]);*/
          /*printf("hpl 1: \"%s\"\n", headPartLines[1]);*/

        }
      }
      fprintf(headerPartFile, "#endif\n");
      fclose(headerPartFile);
      closedir(innerDir); 
      //closeheader
    }

  }

  /*printf("dir serail numer: %s", headent->d_name[0]);*/
  closedir(head);

  return 0;
}
