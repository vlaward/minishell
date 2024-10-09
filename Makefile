# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncrombez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 10:12:45 by ncrombez          #+#    #+#              #
#    Updated: 2024/10/09 10:13:44 by ncrombez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include Colors.mk

# Names 
NAME		= minishell
MAIN		= srcs/exec/main.c
F_BUILT		= echo.c builtins.c env.c pwd.c exit.c export.c unset.c cd.c #list.c#cd.c error.c
FILES		+= $(addprefix builtins/, $(F_BUILT))
F_EXEC		= redirects.c ft_minisplit.c Les_Guillemets_UwU.c      \
				get_next_line.c all_good.c tokkens.c Das_signals.c here_doc.c \
				init_env.c init_cmd_list.c execute_cmd.c
FILES		+= $(addprefix exec/, $(F_EXEC))

# Paths
SRCS_PATH	= srcs/
INCS_PATH	= headers/
OBJS_PATH	= objs/

# Objects
SRCS		= $(addprefix $(SRCS_PATH), $(FILES))
OBJS		= $(addprefix $(OBJS_PATH), $(FILES:.c=.o))

# Flags + compilation
CFLAGS		= -Wall -Wextra -Werror -g
CC			= cc
INCS		= $(addprefix -I, $(INCS_PATH))
INCS		+= -lreadline

# Create obj and dir
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@ 
			@echo "${MSG_COMP}$<"
			
# Compiling command
all:		${NAME}

${NAME}:	libs ${OBJS}
			@$(CC) $(CFLAGS) $(MAIN) -o $(NAME) $(OBJS) $(INCS) libft/libft.a
			@echo "${MSG_BUILD}${NAME}${MSG_FINISH}"
			@echo "${FINISH}"

test:		libs ${OBJS}
			@$(CC) $(CFLAGS) srcs/exec/test.c -o minitest $(OBJS) $(INCS) libft/libft.a
			valgrind --suppressions=./readline.supp --track-fds=yes --leak-check=full --trace-children=yes --track-origins=yes --show-leak-kinds=all -s -q ./minitest


val:		libs ${OBJS}
			make
			valgrind --suppressions=./readline.supp --track-fds=yes --leak-check=full --trace-children=yes --track-origins=yes --show-leak-kinds=all -s -q ./minishell

libs :
	@echo "\033[1;33mBoup Bip Bip !\033[m \033[1;35m\nCompiling libs :\033[m"
	@make -s --no-print-directory -C libft

# Other rules
clean:
			@rm -rf ${OBJS_PATH}
			@echo "${MSG_RMV}${OBJS_PATH}*"
			@make fclean --no-print-directory -C libft
# 			@echo "\033[1;32mReaaaaally clean :D\033[m"

fclean:	
			@rm -rf ${OBJS_PATH}
			@echo "${MSG_RMV}${OBJS_PATH}*"
			@rm -rf ${NAME}
			@echo "${MSG_RMV}${NAME}"
			@make clean --no-print-directory -C libft
#			@echo "\033[1;32mEvrything's clean now 0w0\

re:			
			@rm -rf ${OBJS_PATH}
			@echo "${MSG_RMV}${OBJS_PATH}*"
			@rm -rf ${NAME}
			@echo "${MSG_RMV}${NAME}"
			@make -s

panda:
			@echo "${PANDA}"

shrek:
			@echo "${SHREK}"

cat:
			@echo "${CAT}"


.PHONY:		all clean fclean re
