/*
** control_map.c for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Mon Mar  2 14:24:02 2015 David Tran
** Last update Sat Mar  7 18:21:37 2015 David Tran
*/

#include "lemipc.h"

int		search_others(t_princ *lemip)
{
  int		i;
  char		*str;

  i = 0;
  str = (char *) lemip->addrmap;
  while (i < MAP_LEN * MAP_LEN)
    {
      if (str[i] != 0 && str[i] != lemip->player.team)
	return (0);
      i++;
    }
  return (1);
}

void		exec_map(t_princ *lemip)
{
  char		*tmp;
  char		first;
  int		toto;

  tmp = (char *)lemip->addrmap;
  first = 0;
  while (42)
    {
      if ((toto = search_others(lemip) == 1) && first == 1)
	{
	  tmp[MAP_LEN * MAP_LEN + 1] = -1;
	  return ;
	}
      else if (first == 0 && toto == 0)
	first = 1;
      if (tmp[MAP_LEN * MAP_LEN + 1] == -1)
	return ;
      /*      if (msgrcv(lemip->msg_id, lemip->msgbuf, sizeof(t_msgbuf), MSG_GEN, 0) == -1)
	{
	  perror("Can't receive message");
	  return ((void *)(EXIT_FAILURE));
	  }*/
      sleep(1);
    }
}
