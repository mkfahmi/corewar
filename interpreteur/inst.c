#include <stdio.h>
#include "vm.h"
#include <stdlib.h>
int *make(char *c);

int *lest(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
};
int *live(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *sti(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *aff(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *lfork(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *lld(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *ldi(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *ffork(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
  }
int *and(char c){
  char *cc = inttobin(c);
  int *k = make(cc);
  return k;
}            
int *sub(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *ld(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *st(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *zjmp(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *xor(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}  
int *add(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
}
int *or(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
} 
int *lldi(char c){
  char *cc = inttobin(c);
  int *k  = make(cc);
  return k;
  }

int *make(char *c){
  int i;
  int *b;
  b = malloc(sizeof(int)*4);
  b[0] = c[0]*10+c[1];
  b[1] = c[2]*10+c[3];
  b[2] = c[4]*10+c[5];
  b[3] = c[6]*10+c[7];
  i = 0;
  while(i<4){
    if(b[i]==0)
      while(i<4){
	b[i]=0x00;
	i++;
      }
      else if(b[i]==11)
	b[i]=2;
      else if(b[i]==10)
	b[i]=4;
    i++;
  }
  return b;
}
