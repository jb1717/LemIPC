/*
** ia_utils.c for LemIPC in /home/jibb/rendu/PSU_2014_lemipc
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Sat Mar  7 17:00:48 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  8 14:02:49 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

int		set_pos_value(int *x, int *y, int x_value, int y_value)
{
  *x = x_value;
  *y = y_value;
  return (1);
}

int		calc_direction(int src, int dest)
{
  if (src == dest)
    return (src);
  else if (src < dest)
    return (src + 1 < MAP_LEN ? src + 1 : src);
  else
    return (src - 1 > 0 ? src - 1 : 0);
}

void		find_free_block(t_princ *lemip, t_pos *pos)
{
  int		i;
  int		j;
  int		idx;
  int		x;
  int		y;

  i = 0;
  while (i < 3)
    {
      j = 0;
      while (j < 3)
	{
	  x = lemip->player.ia.x - 1;
	  y = lemip->player.ia.y - 1;
	  idx = ((x > 0 && y > 0) ? (y + i) * MAP_LEN + x + j : -1);
	  if (idx != -1 && lemip->map[idx] == 0)
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

void		send_msg(char *msg, int msgid, long canal, t_princ *lemip)
{
  lemip->msgbuf.mtype = canal;
  strcpy(lemip->msgbuf.mdata, msg);
  lemip->msgbuf.team = lemip->player.team;
  msgsnd(msgid, &(lemip->msgbuf), sizeof(t_msgbuf) - sizeof(long), 0);
}

int		is_dead(t_princ *lemip)
{
  int		i;
  int		j;
  int		x;
  int		y;
  int		idx;
  int		count;

  i = 0;
  count = 0;
  while (i < 3)
    {
      j = 0;
      while (j < 3)
	{
	  x = (lemip->player.ia.x - 1 >= 0 ? lemip->player.ia.x - 1 : 0);
	  y = (lemip->player.ia.y - 1 >= 0 ? lemip->player.ia.y - 1 : 0);
	  idx = (y + i) * MAP_LEN + x + j;
	  if (lemip->map[idx] != 0 && lemip->map[idx] != lemip->player.team)
	    count++;
	  j++;
	}
      i++;
    }
  return (count >= 2 ? 1 : 0);
}
