#include "corewar.h"

static int getChampionCount(t_champ *instances)
{
  int out;
  t_champ *tmp;

  out = 0;
  tmp = instances;
  while (tmp != NULL)
    {
      if (tmp->Parent == -1)
	out++;
      tmp = tmp->next;
    }
  return (out);
}

void StartVM(t_vm *vm)
{
  int cycle;
  void(*functionPtr[16])(t_vm *vm, t_champ *champ, char type[4],
			 int argv[4]);

  setInstructionTab(functionPtr, vm);
  while (GetChampionCount(vm->champs) > 1)
    {
      cycle = initChampions(vm);
      while (cycle < vm->CycleToDie && vm->LiveCount < NBR_LIVE)
	{
	  cycle++;
	  vm->cycleForTurn++;
	}
      if (vm->liveCount)
	vm->cycleToDie -= CYCLE_DELTA;
      getChampionCount(vm->champs);
    }
}
