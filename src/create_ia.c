/*
** create_ia.c for lemipc in /home/jibb/rendu/PSU_2014_lemipc
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Tue Mar  3 10:53:23 2015 Jean-Baptiste Grégoire
** Last update Tue Mar  3 15:13:23 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

static int	get_team_number(char *team_number)
{
  int		tmp;

  if ((tmp = atoi(team_number)) == 0)
    {
      printf("Invalid team number: must be different from zero\n");
      return (-1);
    }
  if (tmp < 0)
    {
      printf("Invalid team number: must be different from zero\n");
      return (-1);
    }
  return (tmp);
}

int		init_player(t_princ *lemip, char *team_number)
{
  char		good;
  char		*tmp;

  good = 1;
  if ((lemip->player.team = get_team_number(team_number)) == -1)
    return (EXIT_FAILURE);
  tmp = (char *)(lemip->addrmap);
  while (good)
    {
      lemip->player.pos_x = rand() % MAP_LEN;
      lemip->player.pos_y = rand() % MAP_LEN;
      if (tmp[lemip->player.pos_y * MAP_LEN + lemip->player.pos_x] == 0)
	{
	  tmp[lemip->player.pos_y * MAP_LEN + lemip->player.pos_x] = lemip->player.team;
	  good = 0;
	}
    }
  return (EXIT_SUCCESS);
}
