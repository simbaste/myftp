##
## Makefile for server in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
##
## Made by stephanedarcy simomba
## Login   <simomb_s@epitech.net>
##
## Started on  Tue May  3 21:55:53 2016 stephanedarcy simomba
## Last update Sun May 15 12:25:40 2016 stephanedarcy simomba
##

CC	= gcc

NAME	= server

CFLAGS	+= -W -Wall -Werror -Wextra
CFLAGS	+= -Iinclude

SRCS	= src/main.c \
	  src/function.c \
	  src/string_func.c \
	  src/command_func.c \
	  src/socket_func.c \
	  src/login_func.c \
	  src/dir_func.c \
	  src/pasv_func.c \
	  src/help_func.c \
	  src/retr_func.c \
	  src/list_func.c \
	  src/quit_dele_func.c

OBJS	= $(SRCS:.c=.o)

RM	= rm -f
PRINTF	= @printf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
	$(PRINTF) '\033[1;32m> Compiled\033[0m\n'

clean:
	$(RM) $(OBJS)
	$(PRINTF) '\033[1;35m> Directory cleaned\033[0m\n'

fclean: clean
	$(RM) $(NAME)
	$(PRINTF) '\033[1;35m> Remove executable\033[0m\n'

re: fclean all

.PHONY: all clean fclean re
