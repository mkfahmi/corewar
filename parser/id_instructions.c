#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]) {
  t_instruction *tab_instructions = get_instructions(argv[1]);
  t_hex_instruction *hex_instructions = malloc(sizeof(t_hex_instruction) * size_array_struct);
  int i, j;
  for (i=0; i<size_array_struct; i++)
    hex_instructions[i] = instruction_to_hexa(tab_instructions[i]);


  FILE * fp;
  fp = fopen ("champ.cor", "w+");

  for (i=0; i<size_array_struct; i++) {
    if (strcmp(hex_instructions[i].label, "") !=0)
      fprintf(fp, "%s", hex_instructions[i].label);
    fprintf(fp, "%c", hex_instructions[i].opocode);
    if ((int) hex_instructions[i].coding_byte != 0)
      fprintf(fp, "%c", hex_instructions[i].coding_byte);
    for (j=0; j < hex_instructions[i].parameters_length; j++) {
      fprintf(fp, "%c", hex_instructions[i].parameters[j]);
    }
    //    fprintf(fp, "%s", hex_instructions[i].parameters);
  }
  fclose(fp);

  
  for (i=0; i < size_array_struct; i++) {
    if (strcmp(hex_instructions[i].label, "") !=0)
      printf("%s, ",  hex_instructions[i].label);
    printf("0x%02x, ", hex_instructions[i].opocode);
    if ((int) hex_instructions[i].coding_byte != 0)
      printf("0x%02x, ", hex_instructions[i].coding_byte);

    for (j=0; j < hex_instructions[i].parameters_length; j++) {    
      printf("0x%02x, ", hex_instructions[i].parameters[j]);
    }
    puts("");
  }   
  
}

/*
 * Decompose les instructions asm en {label, opocode, parametres} a partir du fichier asm champion. 
 * Cette fonction prends en parametre le nom du fichier asm (argv) et renvoie un tableau de structure s_instruction (type t_instruction)
 */
t_instruction *get_instructions(char *argv) {
  FILE *fp;
  char *line = NULL;
  int file_length;
  size_t len = 0;
  ssize_t read;
  
  fp = fopen(argv, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  fseek(fp, 0L, SEEK_END);
  file_length = ftell(fp);
  fseek(fp, 0L, SEEK_SET);


  t_instruction *tab_instructions = malloc(sizeof(t_instruction) * file_length);  
  int i = 0, j = 0, k = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    // detection LABEL
    tab_instructions[i].label = get_label(line);
    if (tab_instructions[i].label != "") { 
      j = strlen(tab_instructions[i].label);       //
      if (line[j] == ':')                          //
	(line[j+1] == ' ') ? k+=2 : k++;           // retirer le label de la ligne pour 
      else if (line[j] == ' ')                     // laisse l'opocode en premiere place
	(line[j+1] == ':') ? k+=2 : k++;           //
      line = str_cut(line, j+k, strlen(line));     //
    }
    // detection OPOCODE
    if (tab_instructions[i].opocode != "") {
      tab_instructions[i].opocode = get_opocode(line);
      j = strlen(tab_instructions[i].opocode);
      line = str_cut(line, j, strlen(line));
    }
    // detection PARAMETRES
    tab_instructions[i].parameters = get_parameters(line);
    i++;
  }

  size_array_struct = i; // variable globale de la taille de la structure

  fclose(fp);
  if (line)
    free(line);

  return (tab_instructions);
}

/*
 * Detecte les labels dans une instruction. Retourne le label s'il y en a un, rien ("") sinon.
 */
char *get_label(char *line) {
  int i = 0;
  int j = 0;
  int ok = 0;
  char *label = malloc(sizeof(char)*50);
  
  for(i = 0; line[i] != '\0'; i++) {
    if (line[i] == ' ')
      break;
    if (line[i] == ':') {
      ok = 1;
      break;
    }
  }

  if (ok == 1) {
    strncpy(label, line, i);
    return (label);
  } else {
    return ("");
  }
}

/*
 * Detecte et retourne l'opocode d'une instruction
 */
char *get_opocode(char *line) {
  int i = 0;
  int j = 0;
  int ok = 0;
  char *opocode = malloc(sizeof(char)*50);

  for (i = 0; line[i] != '\0'; i++) {
    if (line[i] == ' ') {
      ok = 1;
      break;
    }
  }
  if (ok == 1) {
    strncpy(opocode, line, i);
    return (opocode);
  } else {
    return ("");
  }
}

/*
 * Detecte les parametres de l'opocode et retourne un tableau de parametres 
 */
char **get_parameters(char *line) {
  char **parameters =  str_split(line, ',');
  return (parameters);
}

