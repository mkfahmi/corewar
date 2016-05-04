#include "corewar.h"

int initChampions(t_vm *vm)
{
  t_champ *tmp;

  vm->LiveCount = 0;
  tmp = vm->champs;
  while (tmp != NULL)
    {
      tmp->LastLive = 0;
      tmp->CurrentCycle = 0;
      tmp = tmp->next;
    }
  return (1);
}
