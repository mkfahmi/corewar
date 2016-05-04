/*
** vm.c for vm in /root/perso/etna/corewar/scheduler
** 
** Made by BOEHM Steven, DENOYELLE Boris, FAHMI Mohamad, LALOS Bastien
** Login   <boehm_s, denoye_b, fahmi_m, lalos_b@etna-alternance.net>
** 
** Started on  Sat Apr 16 20:17:47 2016 BOEHM Steven, DENOYELLE Boris, FAHMI Mohamad, LALOS Bastien
** Last update Mon Apr 18 13:17:15 2016 BOEHM Steven, DENOYELLE Boris, FAHMI Mohamad, LALOS Bastien
*/

#include "prototypes.h"
#include "../src/op/op.h"

void	live(char *arg1, char *arg2, char *arg3, char *arg4)
{
  printf("\n\nSalut, je suis live !!!\n\n");
}

void	ld(char *arg1, char *arg2, char *arg3, char *arg4)
{
  printf("\n\nSalut, je suis ld !!!\n\n");
}

// Declaration des champions et du tableau de champions
t_champion	champion1;
t_champion	champion2;
t_champion	tab_champions[2];

void	get_instruction(int num_champion)
{
  if(num_champion == 0) {
    tab_champions[num_champion].current_instruction = 0x01;
    tab_champions[num_champion].nb_cycles = 4;
    //tab_champions[num_champion].params = tab_params1;
  }
  else {
    tab_champions[num_champion].current_instruction = 0x02;
    tab_champions[num_champion].nb_cycles = 6;
    //tab_champions[num_champion].params = tab_params2;
  }
}

// Scheduler qui repartit les instructions des champions pour simuler le parallelisme lors de l'execution
int	*scheduler(t_champion *tab_champions, int cycles_live)
{
  int	i = 0;         // Numero du champion
  int	j;             // Parcours du tableau de pointeurs sur focntions
  int	cycles_nb = 0; // Nombre de cycles executes avant d'atteindre CYCLE_TO_DIE
  int	live_nb = 0;
  int	last_champion_alive = 0;
  int	*result = malloc(3 * sizeof(int));
  
  get_instruction(i);
  get_instruction(i + 1);
  
  while(cycles_nb < CYCLE_TO_DIE) {
    j = 0;
    // On parcourt le tableau des psf
    while(1)
      {
	// Si on trouve la fonction de current_instruction dans le tableau de psf
	if(pf[j].hexa_code == tab_champions[i].current_instruction) {
	  printf("Champion %d :\n", i);
	  // Si les cycles de l'instruction en cours ne sont pas finis, on les incremente
	  if(tab_champions[i].num_cycle < tab_champions[i].nb_cycles) {
	    printf("Suite de %s (cycle %d)\n", pf[j].name, tab_champions[i].num_cycle);
	    tab_champions[i].num_cycle++;
	  }
	  // Sinon, on execute l'instruction, on reinitialise le numero de cycle et on demande a l'interpreteur de nous donner l'instruction suivante
	  else {
	    printf("Debut de %s (cycle %d)", pf[j].name, tab_champions[i].num_cycle);
	    pf[j].psf(tab_champions[i].params[0], tab_champions[i].params[1], tab_champions[i].params[2], tab_champions[i].params[3]);
	    tab_champions[i].num_cycle = 0;
	    get_instruction(i);
	    if(pf[j].hexa_code == 0x01) {
	      live_nb++;
	      last_champion_alive = i;
	    }
	  }
	  // On incremente le nombre global de cycle pour atteindre CYCLE_TO_DIE
	  cycles_nb++;
	  break;
	}
	j++;
      }
    
    if(i + 1 < 2)
      i++;
    else
      i = 0;
  }

  result[0] = cycles_live++;
  result[1] = live_nb;
  result[2] = last_champion_alive;

  return(result);
}

void	virtual_machine(t_champion *tab_champions)
{
  int	live_nb;                         // Nombre d'instructions live executees
  int	last_champion_alive;             // Nom du dernier champion en vie
  int	cycles_live;                     // Nombre de fois ou CYCLE_TO_DIE cycles sont executes avant d'atteindre NBR_LIVE
  int	cycle_to_die = CYCLE_TO_DIE;
  int	cycle_delta = CYCLE_DELTA;

  while(live_nb != 0)
    {
      live_nb = 0;
      last_champion_alive = 0;
      cycles_live = 0;

      while(cycles_live < 40)
	{
	  // Scheduler
	  cycles_live = scheduler(tab_champions, cycles_live)[0];
	  live_nb = scheduler(tab_champions, cycles_live)[1];
	  last_champion_alive = scheduler(tab_champions, cycles_live)[2];

	  if(live_nb == 0)
	    {
	      printf("Le joueur %s a gagne.", tab_champions[last_champion_alive].name);
	      break;
	    }
	}
      cycle_to_die = cycle_to_die - cycle_delta;
    }
}

int     main(int argc, char *argv[])
{
  int	i;
  int	j;
  
  char	tab1[4][4] = {
    {0x02, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02}
  };
  
  char	tab2[4][4] = {
    {0x02, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02}
  };
  
  champion1.name = "Mohamad";
  champion1.current_instruction = '\0';
  
  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      champion1.params[i][j] = tab1[i][j];
    }
    i++;
  }
  
  champion2.name = "Steven";
  champion2.current_instruction = '\0';

  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      champion2.params[i][j] = tab2[i][j];
    }
    i++;
  }
  
  tab_champions[0] = champion1;
  tab_champions[1] = champion2;

  virtual_machine(tab_champions);

  return(0);
}
