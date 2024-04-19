NAME  = minishell
MAIN  = main.c
LIBS = -lreadline libft/libft.a
SRCS = parser.o executeur.o
FLAGS = -g

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@

all : libs $(SRCS)
	@gcc $(MAIN) -o $(NAME) $(SRCS) $(LIBS) $(FLAGS)
	@echo "\033[1;33mCompil complete !\033[m"


libs :
	@echo "\033[1;33mBoup Bip Bip !\033[m \033[1;35m\nCompiling libs :\033[m"
	@make -s --no-print-directory -C libft

# # Names + files
# NAME	= minishell
# FILES	= parser.c executeur.c
# LIBS	= -lreadline libft/libft.a

# # Colors
# _END		= \033[0m
# _COMP		= \033[1;33m
# _BUILD		= \033[1;32m
# _REMOVE		= \033[1;31m
# _LIB		= \033[1;30m
# _FINISH		= \033[1;3;96m

# # Messages
# COMP		= Compiling
# BUILD		= Building
# REMOVE		= Removing
# LIBX		= Building lib
# FINISH		= \n\n		o(〃＾▽＾〃)o
# MSG_COMP	= ${_COMP}${COMP}:	${_END}
# MSG_BUILD	= ${_BUILD}${BUILD}:	${_END}
# MSG_RMV		= ${_REMOVE}${REMOVE}:	${_END}
# MSG_LIB		= ${_LIB}${LIBX}:	${_END}
# MSG_FINISH	= ${_FINISH}${FINISH}${_END}

# # Paths
# SRCS_PATH	= srcs/
# INCS_PATH	= usr/include headers/
# OBJS_PATH	= objs/

# # Objects
# OBJS	= $(addprefix $(OBJS_PATH), $(FILES:.c=.o))

# # Flags + compilation
# FLAGS	= # -Wall -Wextra -Werror
# CC		= cc
# INC		= $(addprefix -I, $(INCS_PATH))

# # Function to display progress bar
# define progress_bar
# 	@printf "["
# 	@for i in $(shell seq 1 $(1)); do \
# 		if [ $$i -le $(2) ]; then \
# 			printf "="; \
# 		else \
# 			printf " "; \
# 		fi; \
# 	done
# 	@printf "] $(3)%\r"
# endef

# # Create obj and dir
# $(OBJS_PATH)%.o: $(SRCS_PATH)%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(FLAGS) $(INC) -O3 -c $< -o $@
# 	@$(call progress_bar,$(words $(FILES)),$(words $(wildcard $(OBJS_PATH)*.o)),$(shell echo $$((($(words $(wildcard $(OBJS_PATH)*.o)) * 100) / $(words $(FILES))))))

# # Compiling command
# all:		${NAME}

# ${NAME}:	libs ${OBJS}
# 	@$(CC) $(FLAGS) $(OBJS) $(LIB_INC) $(INC) -o $(NAME) 
# 	@echo "${MSG_BUILD}${NAME}${MSG_FINISH}"

# libs :
# 	@echo "\033[1;33mBoup Bip Bip !\033[m \033[1;35m\nCompiling libs :\033[m"
# 	@make -s --no-print-directory -C libft

# clean:
# 	@rm -rf ${OBJS_PATH}
# 	@echo "${MSG_RMV}${OBJS_PATH}*"

# fclean:		clean
# 	@rm -rf ${NAME}
# 	@echo "${MSG_RMV}${NAME}"

# re:			fclean all


# .PHONY:        all clean fclean re
