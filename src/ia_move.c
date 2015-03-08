/*
** ia_move.c for LemIPC in /home/jibb/rendu/PSU_2014_lemipc/src
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Sat Mar  7 19:07:25 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  8 23:12:53 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

int		ia_move(t_princ *lemip)
{
  t_pos		direction;

  direction.x = -1;
  direction.y = -1;
  ia_scan_map(lemip, &(lemip->player), &direction);
  if (direction.x == -1 || lemip->map[direction.y *
				      MAP_LEN + direction.x] != 0)
    find_free_block(lemip, &direction);
  if (direction.x != -1)
    {
      lemip->map[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] = 0;
      lemip->player.ia.x = direction.x;
      lemip->player.ia.y = direction.y;
      lemip->map[direction.y * MAP_LEN + direction.x] = lemip->player.team;
    }
  return (0);
}
