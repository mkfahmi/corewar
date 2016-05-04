CC =		gcc
NAME =		parser
SRC =		vm.c		\
		str_func.c	\
		op.c		\
		inst.c		\
		calc.c

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
