CC =		gcc
NAME =		parser
SRC =		str_func.c			\
		op.c				\
		to_hex.c			\
		id_instructions.c		

OBJ =		$(SRC:%.c=%.o)
RM =		rm -f *~

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
