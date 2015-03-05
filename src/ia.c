/*
** ia.c for lemipc in /home/jibb/rendu/PSU_2014_lemipc/src
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Tue Mar  3 15:50:38 2015 Jean-Baptiste Grégoire
** Last update Thu Mar  5 00:50:43 2015 David Tran
*/

#include "lemipc.h"

int		set_pos_value(int *x, int *y, int x_value, int y_value)
{
  *x = x_value;
  *y = y_value;
  return (1);
}

// Attiention le t_ia ne représente pas un joueur mais est une structure temporaire contenant
// la position du début du scan (le coin du carré) ainsi que l'équipe de l'ia avec qui l'on effectue le scan
int		ia_check_square(t_ia *start, int radius, t_radar *r, t_princ *lemip)
{
  int		i;
  int		j;
  int		ret;
  char		*tmp;

  i = 0;
  tmp = (char *)(lemip->addrmap);
  ret = 0;
  printf("enter\n");
  while (i < radius && start->ia.y + radius < MAP_LEN && i < MAP_LEN)
    {
      j = 0;
      while (j < radius && start->ia.x + radius < MAP_LEN)
	{
	  printf("ret : %d -> enemy : %d -> me : %d -> team : %d -> team_case : %d -> x : %d, x_a : %d\n", ret, (start->ia.y + i) * MAP_LEN + start->ia.x + j, start->ia.y * MAP_LEN + start->ia.x, start->team, tmp[(start->ia.y + i) * MAP_LEN + start->ia.x + j], r->enemy.x, r->friend.x);
	  if (r->enemy.x == -1 && tmp[(start->ia.y + i) * MAP_LEN + start->ia.x + j] != start->team && tmp[(start->ia.y + i) * MAP_LEN + start->ia.x + j] != 0)
	    ret += set_pos_value(&(r->enemy.x), &(r->enemy.y), start->ia.x + j, start->ia.y + i);
	  if (r->friend.x == -1 && tmp[(start->ia.y + i) * MAP_LEN + start->ia.x + j] == start->team)
	    ret += set_pos_value(&(r->friend.x), &(r->friend.y), start->ia.x + j, start->ia.y + i);
	  if (ret == 2)
	    return (1);
	  j++;
	  sleep(0.5);
	}
      i++;
    }
  return (ret == 1 ? 1 : 0);
}

static int	calc_direction(int src, int dest)
{
  if (src == dest)
    return (src);
  else if (src < dest)
    return (src + 1 > MAP_LEN ? src + 1 : src);
  else
    return (src - 1 < 0 ? src - 1 : 0);
}

void		ia_take_direction(t_radar *r, t_ia *player, t_pos *direction)
{
  int		d1;
  int		d2;

  d1 = (r->enemy.x != -1 ? sqrt(SQUARE(player->ia.x - r->enemy.x) +
				 SQUARE(player->ia.y - r->enemy.y)) : -1);
  d2 = (r->friend.x != -1 ? sqrt(SQUARE(player->ia.x - r->friend.x) +
				  SQUARE(player->ia.y - r->friend.y)) : -1);
  if (d2 != -1 && d2 <= IA_COOP_RAD)
    {
      // si il est avec au moins un allié
      direction->x = calc_direction(player->ia.x, r->enemy.x);
      direction->y = calc_direction(player->ia.y, r->enemy.y);
    }
  if (d1 != -1 && d2 > IA_COOP_RAD)
    {
      // si il est tout seul
      direction->x = calc_direction(player->ia.x, r->friend.x);
      direction->y = calc_direction(player->ia.y, r->friend.y);
    }
  //  printf("x : %d, y : %d\n", direction->x, direction->y);
}

void		ia_scan_map(t_princ *lemip, t_ia *player, t_pos *direction)
{
  int		radius;
  t_ia		start;
  t_radar	r;

  radius = 1;
  r.enemy.x = -1;
  r.enemy.y = -1;
  r.friend.x = -1;
  r.friend.y = -1;
  while (radius < MAP_LEN)
    {
      //      printf("radius: %d\n", radius);
      start.ia.x = (player->ia.x - radius >= 0 ? player->ia.x - radius : 0);
      start.ia.y = (player->ia.y - radius >= 0 ? player->ia.y - radius : 0);
      start.team = player->team;
      if (ia_check_square(&start, radius, &r, lemip) == 1)
	{
	  printf("inside\n");
	  ia_take_direction(&r, player, direction);
	  return ;
	}
      radius++;
    }
}

void		find_free_block(t_princ *lemip, t_pos *pos)
{
  int		i;
  int		j;
  int		idx;
  char		*tmp;

  i = 0;
  tmp = (char *)(lemip->addrmap);
  while (i < 3)
    {
      j = 0;
      while (j < 3)
	{
	  idx = (lemip->player.ia.y - 1 + i) * MAP_LEN + lemip->player.ia.x - 1 + j;
	  if (tmp[idx] == 0)
	    {
	      pos->x = lemip->player.ia.x - 1 + j;
	      pos->y = lemip->player.ia.y - 1 + i;
	      return ;
	    }
	  j++;
	}
      i++;
    }
}

int		is_dead(t_princ *lemip)
{
  int		i;
  int		j;
  int		idx;
  int		count;
  char		*tmp;

  i = 0;
  count = 0;
  tmp = (char *)(lemip->addrmap);
  while (i < 3)
    {
      j = 0;
      while (j < 3)
	{
	  idx = (lemip->player.ia.y - 1 + i) * MAP_LEN + lemip->player.ia.x - 1 + j;
	  if (tmp[idx] != 0)
	    count++;
	  j++;
	}
      i++;
    }
  return (count >= 2 ? 1 : 0);
}

void		send_msg(char *msg, int msgid, long canal)
{
  t_msgbuf	msgbuf;
  char		*tmp;

  tmp = strdup(msg);
  msgbuf.mtype = canal;
  strcpy(tmp, &(*msgbuf.mdata));
  msgsnd(msgid, &msgbuf, sizeof(msgbuf), 0);
}

int		ia_move(t_princ *lemip)
{
  char		is_alive;
  t_pos		direction;
  struct sembuf	sop;
  char		*tmp;

  tmp = (char *)(lemip->addrmap);
  direction.x = -1;
  direction.y = -1;
  sop.sem_num = 1;
  sop.sem_flg = 0;
  is_alive = 1;
  while (is_alive)
    {
      sop.sem_op = 1;
      semop(lemip->key, &sop, 1);
      ia_scan_map(lemip, &(lemip->player), &direction);
      if (tmp[direction.y * MAP_LEN + direction.x] != 0)
	find_free_block(lemip, &direction);
      if (direction.x != -1)
	{
	  tmp[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] = 0;
	  tmp[direction.y * MAP_LEN + direction.x] = lemip->player.team;
	}
      if (is_dead(lemip))
	{
	  tmp[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] = 0;
	  send_msg("Aaaargh ! Je meurs !", lemip->key, MSG_GEN);
	  is_alive = 0;
	}
      sop.sem_op = -1;
      semop(lemip->key, &sop, 1);
    }
  return (0);
}
