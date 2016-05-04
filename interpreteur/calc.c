#include <stdlib.h>
char  *inttobin(int binaire){
  int i;
  char val[8]={0,0,0,0,0,0,0,0};
  char *final = malloc(sizeof(char)*8);
  int res;
  if (binaire & 1 )
    val[0]=1;
  for (i = 1;i<8;i++){
    res = binaire/2;
    if(res & 1)
      val[i]=1;
    binaire = res;
  }
  int yy = 0;
  for(i=7;i>=0;i--){
    final[yy]=val[i];
    yy++;
  }
  return final;
}
