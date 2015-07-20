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
          printf("    file: %s\n", innerDent->d_name);
        }
      }
    }
  }

  /*printf("dir serail numer: %s", headent->d_name[0]);*/
  closedir(head);

  return 0;
}




  /*lulwat = fopen("lulwat", mode);*/
  /*fseek(lulwat, 0L, SEEK_END);*/
  /*int size = ftell(lulwat);*/
  /*char buff[size + 1];*/
  /*rewind(lulwat);*/
  /*char c;*/
  /*if (lulwat){*/
    /*size_t newLen = fread(buff, sizeof(char), size, lulwat);*/
    /*if (newLen == 0){*/
      /*printf("srry err\n");*/
    /*} else {*/
      /*buff[++newLen] = '\0';*/
    /*}*/
  /*}*/
  /*printf("buff length %d\n", sizeof(buff)/sizeof(char));*/
  /*printf("%s", buff);*/
  /*fclose(lulwat);*/
  /*return 0;*/
