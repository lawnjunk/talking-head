#include <stdio.h>
#include <string.h>

int main(){
  FILE *lulwat;
  char *mode = "r";
  lulwat = fopen("lulwat", mode);
  fseek(lulwat, 0L, SEEK_END);
  int size = ftell(lulwat);
  char buff[size + 1];
  rewind(lulwat);
  char c;
  if (lulwat){
    size_t newLen = fread(buff, sizeof(char), size, lulwat);
    if (newLen == 0){
      printf("srry err\n");
    } else {
      buff[++newLen] = '\0';
    }
  }
  printf("buff length %d\n", sizeof(buff)/sizeof(char));
  printf("%s", buff);
  fclose(lulwat);
  return 0;
}
