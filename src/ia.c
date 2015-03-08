/*
** ia.c for lemipc in /home/jibb/rendu/PSU_2014_lemipc/src
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Tue Mar  3 15:50:38 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  8 15:26:52 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

void		ia_try_find_proc(t_ia *s, t_radar *r, t_princ *lemip, t_pos *pos)
{
  int		idx;

  idx = (s->ia.y + pos->y) * MAP_LEN + s->ia.x + pos->x;
  if (r->enemy.x == -1 && s->ia.x + pos->x >= 0 && s->ia.y + pos->y >= 0 &&
      lemip->map[idx] != s->team && lemip->map[idx] != 0)
    set_pos_value(&(r->enemy.x), &(r->enemy.y),
		  s->ia.x + pos->x, s->ia.y + pos->y);
  if (r->friend.x == -1 && s->ia.x + pos->x >= 0 && s->ia.y + pos->y >= 0 &&
      lemip->map[idx] == s->team && (s->ia.x + pos->x != lemip->player.ia.x ||
				     s->ia.y + pos->y != lemip->player.ia.y))
    set_pos_value(&(r->friend.x), &(r->friend.y), s->ia.x + pos->x,
		  s->ia.y + pos->y);
}

int		ia_check_square(t_ia *s, int radius, t_radar *r, t_princ *lemip)
{
  t_pos		pos;

  pos.y = 0;
  while (pos.y < 2 * radius + 1 && s->ia.y + pos.y < MAP_LEN)
    {
      pos.x = 0;
      while (pos.x < 2 * radius + 1 && s->ia.x + pos.x < MAP_LEN)
	{
	  ia_try_find_proc(s, r, lemip, &pos);
	  pos.x++;
	}
      pos.y++;
    }
  if (r->enemy.x != -1 && r->friend.x != -1)
    return (2);
  if (r->enemy.x != -1)
    return (1);
  return (0);
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
      direction->x = calc_direction(player->ia.x, r->enemy.x);
      direction->y = calc_direction(player->ia.y, r->enemy.y);
    }
  if ((d1 != -1 && d2 > IA_COOP_RAD) || (d1 == -1 && d2 != -1))
    {
      direction->x = calc_direction(player->ia.x, r->friend.x);
      direction->y = calc_direction(player->ia.y, r->friend.y);
    }
  if (d1 == -1 && d2 == -1)
    {
      direction->x = player->ia.x;
      direction->y = player->ia.y;
    }
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
      start.ia.x = player->ia.x - radius;
      start.ia.y = player->ia.y - radius;
      start.team = player->team;
      if (ia_check_square(&start, radius, &r, lemip) == 2)
	{
	  sleep(1);
	  ia_take_direction(&r, player, direction);
	  return ;
	}
      radius++;
    }
  ia_take_direction(&r, player, direction);
}

int		ia_intermediate(t_princ *lemip)
{
  char		is_alive;
  struct sembuf	sop;

  sop.sem_num = 1;
  sop.sem_flg = 0;
  is_alive = 1;
  while (is_alive)
    {
      sop.sem_op = 1;
      semop(lemip->sem_id, &sop, 1);
      if (is_dead(lemip) || lemip->map[MAP_LEN * MAP_LEN + 1] == -1)
	{
	  lemip->map[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] = 0;
	  send_msg("Aaaargh ! Je meurs !", lemip->key,
		   MSG_GEN, lemip);
	  is_alive = 0;
	}
      else
	ia_move(lemip);
      sop.sem_op = -1;
      semop(lemip->sem_id, &sop, 1);
    }
  return (0);
}
