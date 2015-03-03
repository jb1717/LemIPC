/*
** lemipc.h for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 14:50:31 2015 David Tran
** Last update Tue Mar  3 16:01:52 2015 Jean-Baptiste Grégoire
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/msg.h>
# include <sys/sem.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <pthread.h>

# define UNUSED(a)    	__attribute__((UNUSED))a
# define MAP_LEN	10
# define MSG_BUF_SIZE	256
# define MSG_TYPE	1

typedef struct		s_ia
{
  int			pos_x;
  int			pos_y;
  char			team;
}			t_ia;

typedef struct		s_princ
{
  key_t			key;
  int			shm_id;
  int			msg_id;
  int			sem_id;
  void			*addrmap;
  t_ia			player;
}			t_princ;

typedef struct		s_msgbuf
{
  long			mtype;
  char			mdata[MSG_BUF_SIZE];
}			t_msgbuf;

void			launch_thread(t_princ *);
int			init_player(t_princ *, char *);
int			destroy_resources(t_princ *);

#endif /* !LEMIPC_H_ */
