#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct s_exec t_exec;
struct s_exec{
  char **param;
};

typedef struct s_psf t_psf;
struct s_psf{
  int *(*psf)(char);
  char i;
};

typedef struct s_champion
{
  char          *name;
  char          *comment;
  int           champ_index;
  int           champ_nbr;
  int           live;
  int           carry;
  char          current_instruction;
  char          coding_byte;
  char          parameters[4][4];
  int           curser;
  FILE          *fp;
  int           is_executed;
  int           index;
} t_champion;

typedef struct s_args t_args;
struct s_args{
  char *binary;
  char i;
};

t_champion  c[4];

char *inttobin(int binaire);
void get_par(char *arg,int c);
int *live(char c);
int *sti(char c);
int *aff(char c);
int *lfork(char c);
int *lld(char c);
int *ldi(char c);
int *ffork(char c);
int *and(char c);
int *sub(char c);
int *ld(char c);
int *st(char c);
int *zjmp(char c);
int *xor(char c);
int *add(char c);
int *or(char c);  
int *lldi(char c);
