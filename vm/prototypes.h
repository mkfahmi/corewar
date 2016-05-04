/*
** prototypes.h for prototypes in /root/perso/etna/corewar/scheduler
** 
** Made by BOEHM Steven, DENOYELLE Boris, FAHMI Mohamad, LALOS Bastien
** Login   <boehm_s, denoye_b, fahmi_m, lalos_b@etna-alternance.net>
** 
** Started on  Mon Apr 18 11:55:47 2016 BOEHM Steven, DENOYELLE Boris, FAHMI Mohamad, LALOS Bastien
** Last update Mon Apr 18 12:35:25 2016 BOEHM Steven, DENOYELLE Boris, FAHMI Mohamad, LALOS Bastien
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_champion
{
  char          *name;
  char          *comment;
  int           champ_index;
  int           champ_nbr;
  int           live;
  int           carry;
  char          current_instruction;
  int           nb_cycles;
  int           num_cycle;
  char          params[4][4];
  char          *types_param;
} t_champion;

void	live(char *arg1, char *arg2, char *arg3, char *arg4);
void	ld(char *arg1, char *arg2, char *arg3, char *arg4);
void	get_instruction(int num_champion);
int	*scheduler(t_champion *tab_champions, int cycles_live);
void	virtual_machine(t_champion *tab_champions);

typedef struct s_psf {
  void  (*psf)(char *arg1, char *arg2, char *arg3, char *arg4);
  char  hexa_code;
  char  *name;
} t_psf;

t_psf   pf[17] = {
  {&live, 0x01, "live"},
  {&ld, 0x02, "ld"},
  //{&st, 0X03, "st"},
  //{&add, 0x04, "add"},
  //{&sub, 0x05, "sub"},
  //{&and, 97, "and"},
  //{&or, 0x07, "or"},
  //{&xor, 0x08, "xor"},
  //{&zjmp, 0x09, "zjmp"},
  //{&ldi, 0x0a, "ldi"},
  //{&sti, 0x0b, "sti"},
  //{&ffork, 0x0c, "ffork"},
  //{&lld, 0x0d, "lld"},
  //{&lldi, 0x0e, "lldi"},
  //{&lfork, 0x0f, "lfork"},
  //{&aff, 0x10, "aff"},
  {NULL, '\0'}
};
