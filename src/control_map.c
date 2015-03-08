/*
** control_map.c for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Mon Mar  2 14:24:02 2015 David Tran
** Last update Sun Mar  8 21:17:28 2015 David Tran
*/

#include "lemipc.h"

int		search_others(t_princ *lemip)
{
  int		i;
  char		*str;
  char		check;

  i = 0;
  check = -1;
  str = (char *) lemip->addrmap;
  while (i < MAP_LEN * MAP_LEN)
    {
      if (str[i] != 0 && check == -1)
	check = str[i];
      if (str[i] != 0 && str[i] != check && check != -1)
	return (0);
      i++;
    }
  return (1);
}

void		check_for_messages(t_princ *lemip)
{
  while (msgrcv(lemip->msg_id, &(lemip->msgbuf),
		sizeof(t_msgbuf), MSG_GEN, IPC_NOWAIT) != -1)
    printf("The player of team %d say: %s\n",
    	   lemip->msgbuf.team, lemip->msgbuf.mdata);
}

void		exec_map(t_princ *lemip)
{
  char		*tmp;
  char		first;
  int		toto;

  tmp = (char *)lemip->addrmap;
  first = 0;
  lemip->exit = 0;
  while (42)
    {
      if (tmp[MAP_LEN * MAP_LEN + 1] == -1)
	return ;
      if ((toto = search_others(lemip) == 1) && first == 1)
	{
	  tmp[MAP_LEN * MAP_LEN + 1] = -1;
	  lemip->exit = 1;
	  return ;
	}
      else if (first == 0 && toto == 0)
	first = 1;
      launch_ia_easy(lemip, tmp);
      check_for_messages(lemip);
      sleep(1);
    }
}
