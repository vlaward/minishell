NAME  = minishell
MAIN  = main.c
LIBS = -lreadline libft/libft.a
SRCS = parser.o redirects.o ft_minisplit.o Les_Guillemets_UwU.o get_next_line.o
FLAGS = -g3 -Werror -Wextra -Wall

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@

all : libs $(SRCS)
	@gcc $(MAIN) -o $(NAME) $(SRCS) $(LIBS) $(FLAGS)
	@echo "\033[1;33mCompil complete !\033[m"


libs :
	@echo "\033[1;33mBoup Bip Bip !\033[m \033[1;35m\nCompiling libs :\033[m"
	@make -s --no-print-directory -C libft
