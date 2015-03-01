/*
** lemipc.h for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
** 
** Made by David Tran
** Login   <tran_0@epitech.net>
** 
** Started on  Sun Mar  1 14:50:31 2015 David Tran
** Last update Sun Mar  1 20:49:57 2015 David Tran
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/msg.h>
# include <stdio.h>
# include <stdlib.h>

# define UNUSED		__attribute__((UNUSED))
# define MAP_LEN	100

typedef struct		s_princ
{
  key_t			key;
  int			shm_id;
  void			*addrmap;
}			t_princ;

#endif /* !LEMIPC_H_ */
