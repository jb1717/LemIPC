/*
** lemipc.h for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 14:50:31 2015 David Tran
** Last update Sun Mar  8 20:01:04 2015 David Tran
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
# include <time.h>
# include <strings.h>
# include <unistd.h>
# include <pthread.h>
# include <math.h>
# include <signal.h>
# include <SDL/SDL.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_gfxPrimitives.h>

# define UNUSED(a)    	__attribute__((UNUSED))a
# define SQUARE(a)	(a) * (a)
# define MAP_LEN	100
# define MSG_BUF_SIZE	256
# define MSG_TYPE	1
# define WIN_LEN	1000
# define MSG_GEN	10
# define TEAM_DEF	10
# define PLAYER_IA	1
# define IA_COOP_RAD	2

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

typedef struct		s_msgbuf
{
  long			mtype;
  char			mdata[MSG_BUF_SIZE];
  char			team;
}			t_msgbuf;

typedef struct		s_princ
{
  key_t			key;
  int			shm_id;
  int			msg_id;
  int			sem_id;
  void			*addrmap;
  char			*map;
  t_ia			player;
  struct sembuf		sops;
  t_msgbuf		msgbuf;
  char			ia_take;
}			t_princ;

typedef struct		s_graph
{
  t_princ		princ;
  SDL_Surface		*screen;
  SDL_Surface		*quad;
  SDL_Rect		pos;
  char			exit;
}			t_graph;

typedef struct		s_radar
{
  t_pos			enemy;
  t_pos			friend;
}			t_radar;

void			launch_thread(t_princ *);
void			find_free_block(t_princ *, t_pos *);
void			send_msg(char *, int, long, t_princ *);
void			ia_scan_map(t_princ *, t_ia *, t_pos *);
void			exec_map(t_princ *);
int			init_player(t_princ *, char *, char *);
int			destroy_resources(t_princ *);
int			ia_intermediate(t_princ *);
int			set_pos_value(int *, int *, int, int);
int			calc_direction(int, int);
int			is_dead(t_princ *);
int			ia_move(t_princ *);
int			ia_easy(t_princ *);
void			*ia_thread(void *);
void			init_pos(t_graph *, int, int);
void			fill_point_rect(t_graph *, int, int , char *);

#endif /* !LEMIPC_H_ */
