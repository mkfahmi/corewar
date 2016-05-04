#include "../../includes/corewar.h"

// Initialisation de la structure de la VM
t_vm *init_VM(char **argv)
{
  t_vm *vm;
  
  vm = malloc(sizeof(t_vm));
  vm->memoryMap = (char*) malloc(MEM_SIZE * sizeof(char *));
  vm->memoryReg = (char**) malloc(REG_NUMBER * sizeof(REG_SIZE));
  vm->cycleToDie = CYCLE_TO_DIE;
  //vm->cycleMax = argumend option -dump;
  vm->liveCount = 0; 
  //vm->champCount = 0;

  return(vm);
}

//int main(int argc, char **argv){
//  t_vm *vm;
//  vm = Setup_VM(argv);
//  printf("test");
//}
