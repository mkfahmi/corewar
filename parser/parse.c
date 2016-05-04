#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]) {
  t_instruction *tab_instructions = get_instructions(argv[1]);
  t_hex *hex_ins = file_hexa(size_array_struct, tab_instructions);
}

t_instruction *get_instructions(char *argv) {
  FILE *fp;
  char *line = NULL;
  int file_length;
  size_t len = 0;
  ssize_t read;
  

  fp = fopen(argv, "r");
  
  fseek(fp, 0L, SEEK_END);
  file_length = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  t_instruction *tab_instructions = malloc(sizeof(t_instruction) * file_length);
  
  if (fp == NULL)
    exit(EXIT_FAILURE);
  
  int i = 0, j = 0, k = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    tab_instructions[i].label = get_label(line);
    if (tab_instructions[i].label != "") {
      j = strlen(tab_instructions[i].label);
      if (line[j] == ':') 
	(line[j+1] == ' ') ? k+=2 : k++;
      else if (line[j] == ' ')
	(line[j+1] == ':') ? k+=2 : k++;
      line = str_cut(line, j+k, strlen(line));
      
    }
    if (tab_instructions[i].opocode != "") {
      tab_instructions[i].opocode = get_opocode(line);
      j = strlen(tab_instructions[i].opocode);
      line = str_cut(line, j, strlen(line));
    }
    tab_instructions[i].parameters = get_parameters(line);
    i++;
  }

  size_array_struct = i; // variable globale de la taille de la structure

  fclose(fp);
  if (line)
    free(line);

  return (tab_instructions);
}

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

char **get_parameters(char *line) {
  char **parameters =  str_split(line, ',');
  return (parameters);
}

