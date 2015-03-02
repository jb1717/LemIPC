##
## Makefile for LemiPC in /home/jibb/rendu/PSU_2014_lemipc
## 
## Made by Jean-Baptiste Grégoire
## Login   <jibb@epitech.net>
## 
## Started on  Fri Feb 27 11:27:47 2015 Jean-Baptiste Grégoire
## Last update Mon Mar  2 12:00:00 2015 David Tran
##

DEBUG		= 	no

NAME		=	lemipc

SRC		=	src/main.c

OBJ		=	$(SRC:.c=.o)

RM		=	rm -f

CC		=	gcc

INCLUDES	=	includes/

FOLDER_SRC	=	src/

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
