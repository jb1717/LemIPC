/*
** lemipc.h for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 14:50:31 2015 David Tran
** Last update Wed Mar  4 11:55:44 2015 Jean-Baptiste Grégoire
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
# define SQUARE(a)	(a) * (a)
# define MAP_LEN	10
# define MSG_BUF_SIZE	256
# define MSG_TYPE	1
# define WIN_LEN	1000

# define IA_COOP_RAD	3

typedef struct		s_pos
{
  int			x;
  int			y;
}			t_pos;

typedef struct		s_ia
{
  t_pos			ia;
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

typedef struct		s_radar
{
  t_pos			enemy;
  t_pos			friend;
}			t_radar;

void			launch_thread(t_princ *);
int			init_player(t_princ *, char *);
int			destroy_resources(t_princ *);

#endif /* !LEMIPC_H_ */
