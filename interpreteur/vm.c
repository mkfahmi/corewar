#include <stdlib.h>
#include "vm.h"
#include "op.h"
#include <stdio.h>
t_psf pf[]={{live,0x01},{ld,0x02},{st,0X03},{add,0x04},{sub,0x05},{and,0x06},{or,0x07},{xor,0x08},{zjmp,0x09},{ldi,0x0a},{sti,0x0b},{ffork,0x0c},{lld,0x0d},{lldi,0x0e},{lfork,0x0f},{aff,0x10},{NULL,'d'}};
int main(int argc, char **argv){
  int i = 0;
  c[0].fp = fopen(argv[1], "r");
  for(;i<2;i++)
    get_par(argv[1],0);
  fclose(c[0].fp);
  return (0);
}
void get_par(char *arg,int ii){
  char t[4][4];
  int y;
  int i;
  int *b;
  int cc = 0;
  int reg = 0;
  if(c[ii].fp!=NULL){
    do{
      b=0;
      for(y = 0;pf[y].psf!=NULL;y++){
	if(pf[y].i==c[ii].curser){
	  reg = 1;
	  c[ii].curser=fgetc(c[ii].fp);
	  b = pf[y].psf(c[ii].curser);
	  if(pf[y].i== 0x06 || pf[y].i==)
	    c[ii].curser=fgetc(c[ii].fp);
	  for(i=0;i<4;i++)
	    for(cc=0;cc<b[i];cc++){
	      c[ii].parameters[i][cc]= c[ii].curser;
	      c[ii].curser= fgetc(c[ii].fp); 
	    }
	  break;
	}
      }
      c[ii].curser = fgetc(c[ii].fp);
    }while(c[ii].curser != EOF && reg < 1); 
  }
}
