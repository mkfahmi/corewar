#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op.h"
#include "main.h"

static int param_length;

t_hex_instruction instruction_to_hexa(t_instruction instruction) {
  t_hex_instruction hexa_instruction;

  if (strcmp(instruction.label, "") != 0) {
    hexa_instruction.label = calloc(strlen(instruction.label) + 4, sizeof(char));
    char* ins;
    ins = malloc(strlen(instruction.label)+1+4);
    strcpy(ins, "#");
    strcat(ins, instruction.label);
    strcat(ins, "#");
    hexa_instruction.label = ins;
  } else
    hexa_instruction.label = "";

  //  printf("LABEL : %s", hexa_instruction.label);
  hexa_instruction.opocode = opocode_to_hex(instruction.opocode);
  //  printf("OPOCODE : %c\n", hexa_instruction.opocode);
  hexa_instruction.coding_byte = get_coding_byte(instruction.parameters, instruction.opocode);
  //  printf("OCTET DE CODAGE : %c\n", hexa_instruction.coding_byte);
  hexa_instruction.parameters = parameters_to_hex(instruction.parameters, instruction.opocode);
  //  printf("PARAMETRES : %s\n", hexa_instruction.parameters);
  hexa_instruction.parameters_length = param_length;

  return (hexa_instruction);
}

char opocode_to_hex(char *opocode) {
  int i;
  char hex;
  for (i=0; op_tab[i].mnemonique != 0; i++) {
    if (strcmp(op_tab[i].mnemonique, opocode) == 0)
      return (op_tab[i].code);      
  }
  return (-1);
}

char get_coding_byte(char **parameters, char *opocode){
  int i, j, k, is_coding_byte, bin;
  char binstr[8] = "00000000";

  is_coding_byte = 0;
  for (j=0; op_tab[j].mnemonique != 0; j++)
    if (strcmp(opocode, "live") == 0 || strcmp(opocode, "zjmp") == 0 || strcmp(opocode, "fork") == 0 || strcmp(opocode, "lfork") == 0 || strcmp(opocode, "aff") == 0) {
      is_coding_byte = 1;
      bin = 0;
    }
  
  if (is_coding_byte == 0) {
    for (i=0; parameters[i] != '\0'; i++) {
      
      k = 0;
      if (parameters[i][0] == '\\' || parameters[i][0] == ' ') k++;
      if (parameters[i][k] == '\\') k++;

      if (parameters[i][k] == 'r') {
	binstr[2*i] = '0';
	binstr[2*i+1] = '1';
      }
      else if (parameters[i][k] == '%') {
	binstr[2*i] = '1';
	binstr[2*i+1] = '0';
      }
      else {
	binstr[2*i] = '1';
	binstr[2*i+1] = '1';
      }
    }
    bin = strtol(binstr, NULL, 2);
  }
  return (bin);
}

char *parameters_to_hex(char **parameters, char *opocode) { // verifier si INDEX ?  ==> [zjmp]0x09(1), [ldi]0x0a(1,2), [sti]0x0b(2,3)
  int i, j, k, l, m, n, final_index;
  int num, tmp2;
  unsigned char *tmp = malloc(sizeof(char)*50);
  unsigned char *res;
  unsigned char *parameter_res = calloc(100, sizeof(char));

  final_index = 0;

  for (i=0; parameters[i] != '\0'; i++) {
    n = 0;
    k = 0;
    if (parameters[i][k] == '\\' || parameters[i][k] == ' ') k++;
    if (parameters[i][k] == '\\') k++;

    switch (parameters[i][k]) {
    case 'r' :
      k++;
      m = 0;
      for (l=k; parameters[i][l] != '\0'; l++) {
	tmp[m] = parameters[i][l];
	m++;
      }
      tmp[m] = '\0';

      res = calloc(1, sizeof(char));
      res[0] = (int) strtol(tmp, NULL, 10);
      res[1] = '\0';
      // test
      //printf("registre : %s ==> 0x%02x\n", res, res[0]);
      break;
    case '%' : 
      if (parameters[i][k+1] == ':') {
	k+=2;
	m = 1;
	tmp[0] = '@';
	for (l=k; parameters[i][l] != '\0'; l++) {
	  tmp[m] = parameters[i][l];
	  m++;
	}
	if (tmp[m-1] == '\n') m--;
	tmp[m] = '@';
	tmp[m+1] = '\0';

	res = tmp;

	// test
	//printf("LABEL : %s\n", res);
	
      } else {
	k++;
	m = 0;
	for (l=k; parameters[i][l] != '\0'; l++) {
	  tmp[m] = parameters[i][l];
	  m++;
	}
	tmp[m] = '\0';
	tmp2 = (int) strtol(tmp, NULL, 10);


	// bou
	if (strcmp("zjmp", opocode) == 0) {
	  res = calloc(IND_SIZE + 1, sizeof(char));	
	  for (n=0; n < IND_SIZE; n++)
	    res[n] = (tmp2 >> (8*(IND_SIZE-n-1))) &0xFF;
	} else if (strcmp("ldi", opocode) == 0 && (i == 0 || i == 1)) {
	  res = calloc(IND_SIZE + 1, sizeof(char));	
	  for (n=0; n < IND_SIZE; n++)
	    res[n] = (tmp2 >> (8*(IND_SIZE-n-1))) &0xFF;	  
	} else if (strcmp("sti", opocode) == 0 && (i == 1 || i == 2)) {
	  res = calloc(IND_SIZE + 1, sizeof(char));	
	  for (n=0; n < IND_SIZE; n++)
	    res[n] = (tmp2 >> (8*(IND_SIZE-n-1))) &0xFF;	  
	} else {
	  res = calloc(DIR_SIZE + 1, sizeof(char));	
	  for (n=0; n < DIR_SIZE; n++)
	    res[n] = (tmp2 >> (8*(DIR_SIZE-n-1))) &0xFF;
	}
	// test
	//printf("direct : %s ==> 0x%02x 0x%02x 0x%02x 0x%02x\n", res, res[0], res[1], res[2], res[3]);
      }
      break;
    default:
      m = 0;
      for (l=k; parameters[i][l] != '\0'; l++) {
	tmp[m] = parameters[i][l];
	m++;
      }
      tmp[m] = '\0';

      tmp2 = (int) strtol(tmp, NULL, 10);
      res = calloc(IND_SIZE, sizeof(char));
      for (n=0; n < IND_SIZE; n++)
	res[n] = (tmp2 >> (8*(IND_SIZE-n-1))) &0xFF;

      // test
      //printf("indirect : %s ==> 0x%02x 0x%02x \n", res, res[0], res[1]);
      break;
    }
    //    printf("RES : 0x%02x, 0x%02x, 0x%02x, 0x%02x\n", res[0], res[1], res[2], res[3]);

    printf("RES : ");
    int g;
    if (n == DIR_SIZE) {
      for (g=0; g < DIR_SIZE; g++) {
	//	printf("0x%02x, ", res[g]);
	parameter_res[final_index] = res[g];
	final_index++;
      }
    } else if (n == IND_SIZE) {
      for (g=0; g < IND_SIZE; g++) {
	//        printf("0x%02x, ", res[g]);
	parameter_res[final_index] = res[g];
	final_index++;
      }
    } else {
      for (g=0; res[g] != '\0'; g++) {
	//	printf("0x%02x, ", res[g]);
	parameter_res[final_index] = res[g];
	final_index++;
      }
    }
    puts("");
  }
  param_length = final_index;
  return (parameter_res);
} 
