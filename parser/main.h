#ifndef __PARSE_H__
#define __PARSE_H__

static int size_array_struct = 0;
typedef struct s_instruction {
  char *label;
  char *opocode;
  char **parameters;
} t_instruction;

typedef struct s_hex_instruction{
  char *label;
  char opocode;
  char coding_byte;
  char *parameters;
  int parameters_length;
} t_hex_instruction;

char *get_label(char *line);
char *get_opocode(char *line);
char **get_parameters(char *line);
char *str_cut(char *str, int begin, int end);
char **str_split(char *a_str, const char a_delim);
t_instruction *get_instructions(char *argv);


char opocode_to_hex(char *opocode);
char get_coding_byte(char **parameters, char *opocode);
char *parameters_to_hex(char **parameters, char *opocode);
t_hex_instruction instruction_to_hexa(t_instruction instruction);

#endif
