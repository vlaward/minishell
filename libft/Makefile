SRCS =    ft_atoi.c ft_bzero.c ft_calloc.c \
    ft_isalnum.c ft_isalpha.c ft_isascii.c \
    ft_isdigit.c ft_isprint.c ft_memchr.c \
    ft_memcmp.c ft_memcpy.c ft_memmove.c \
    ft_memset.c ft_strchr.c ft_strdup.c \
    ft_strlcat.c ft_strlcpy.c ft_strlen.c \
    ft_strncmp.c ft_strnstr.c ft_strrchr.c \
    ft_tolower.c ft_toupper.c ft_strjoin.c \
    ft_strtrim.c ft_substr.c ft_split.c \
    ft_itoa.c ft_strmapi.c ft_striteri.c \
    ft_putechar_fd.c ft_putenbr_fd.c ft_putestr_fd.c \
    ft_putendl_fd.c ft_lstnew.c ft_lstadd_front.c \
    ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
    ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstante.c \
    ft_isin_table.c ft_lstnodi.c ft_abs_v.c ft_getc.c ft_iswhitespace.c \
	ft_table_size.c
        
OBJS = $(addprefix srcs/, ${SRCS:.c=.o})
NAME = libft.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@${LIBC} ${NAME} ${OBJS}
	@echo "\033[1;36mLibft :\033[m \033[1;32mOK\033[m"

all: ${NAME}

clean:
	@${RM} ${OBJS} ${OBJSB}
	@echo "\033[1;36mLibft :\033[m \033[1;32mclean\033[m"

fclean: clean
	@${RM} ${NAME} ${bonus}
re: fclean all

.PHONY: all bonus clean fclean re
