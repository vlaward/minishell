include Colors.mk

# Names 
NAME		= minishell
FILES		= main.c executeur.c parser.c
F_BUILT		= echo.c env.c builtins.c
FILES		+= $(addprefix builtins/, $(F_BUILT))

# Paths
SRCS_PATH	= srcs/
INCS_PATH	= headers/
OBJS_PATH	= objs/

# Objects
SRCS		= $(addprefix $(SRCS_PATH), $(FILES))
OBJS		= $(addprefix $(OBJS_PATH), $(FILES:.c=.o))

# Flags + compilation
CFLAGS		= # -Wall -Wextra -Werror -g3
CC			= cc
INCS		= $(addprefix -I, $(INCS_PATH))
INCS		+= -lreadline libft/libft.a

# Create obj and dir
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@ $(INCS) 
			@echo "${MSG_COMP}$<"
			
# Compiling command
all:		${NAME}

${NAME}:	${OBJS}
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCS) 
			@echo "${MSG_BUILD}${NAME}${MSG_FINISH}"
			@echo "${FINISH}"

# Other rules
clean:
			@rm -rf ${OBJS_PATH}
			@echo "${MSG_RMV}${OBJS_PATH}*"

fclean:	
			@rm -rf ${OBJS_PATH}
			@echo "${MSG_RMV}${OBJS_PATH}*"
			@rm -rf ${NAME}
			@echo "${MSG_RMV}${NAME}"

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