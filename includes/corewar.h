#ifndef __COREWAR_H__
#define __COREWAR_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "op.h"

typedef struct s_champ
{
  char *name;
  char *comment;
  int champ_index;
  int champ_nbr;
  int live;
  boolean carry;
} t_champ;

typedef struct s_vm
{
  t_champ *champions;
  int cycleToDie;
  int cycleMax;
  int cycleForTurn;
  int liveCount;
  int instanceCount;
  int index;
  char **memoryReg;
  char *memoryMap;
} t_vm;

//Game
void startVM(t_vm *vm);

// initChamp
int initChampions(t_vm *vm);

// initVM.c
t_vm *init_VM(char **argv);


#endif
