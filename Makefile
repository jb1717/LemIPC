##
## Makefile for LemiPC in /home/jibb/rendu/PSU_2014_lemipc
## 
## Made by Jean-Baptiste Grégoire
## Login   <jibb@epitech.net>
## 
## Started on  Fri Feb 27 11:27:47 2015 Jean-Baptiste Grégoire
## Last update Fri Feb 27 11:29:04 2015 Jean-Baptiste Grégoire
##

DEBUG		= 	no

NAME		=	lemipc

SRC		=

OBJ		=	$(SRC:.c=.o)

RM		=	rm -f

CC		=	gcc

INCLUDES	=	includes/

CFLAGS		=	-W -Wall -Wextra -I $(INCLUDES)

ifeq ($(DEBUG),yes)
	CFLAGS 	+= -g3
else
	CFLAGS	+= -O3
endif

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHNOY:		re fclean clean all
