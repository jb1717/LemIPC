/*
** lemipc.h for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 14:50:31 2015 David Tran
** Last update Mon Mar  2 16:35:51 2015 Jean-Baptiste Grégoire
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/msg.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <pthread.h>

# define UNUSED(a)    	__attribute__((UNUSED))a
# define MAP_LEN	10
# define MSG_BUF_SIZE	256
# define MSG_TYPE	1

typedef struct		s_princ
{
  key_t			key;
  int			shm_id;
  int			msg_id;
  void			*addrmap;
}			t_princ;

typedef struct		s_msgbuf
{
  long			mtype;
  char			mdata[MSG_BUF_SIZE];
}			t_msgbuf;

void			launch_thread(t_princ *);

#endif /* !LEMIPC_H_ */
