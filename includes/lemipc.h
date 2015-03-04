/*
** lemipc.h for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 14:50:31 2015 David Tran
** Last update Wed Mar  4 00:56:55 2015 David Tran
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
# include <SDL/SDL.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_gfxPrimitives.h>

# define UNUSED(a)    	__attribute__((UNUSED))a
# define MAP_LEN	10
# define MSG_BUF_SIZE	256
# define MSG_TYPE	1
# define WIN_LEN	1000

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

typedef struct		s_graph
{
  t_princ		princ;
  SDL_Surface		*screen;
  SDL_Surface		*quad;
  SDL_Rect		pos;
}			t_graph;

typedef struct		s_msgbuf
{
  long			mtype;
  char			mdata[MSG_BUF_SIZE];
}			t_msgbuf;

void			launch_thread(t_princ *);
int			init_player(t_princ *, char *);
int			destroy_resources(t_princ *);

#endif /* !LEMIPC_H_ */
