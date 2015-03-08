/*
** create_ia.c for lemipc in /home/jibb/rendu/PSU_2014_lemipc
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Tue Mar  3 10:53:23 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  8 23:11:46 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

static int	get_team_number(char *team_number)
{
  int		tmp;

  if (!team_number)
    tmp = TEAM_DEF;
  else
    {
      if ((tmp = atoi(team_number)) == 0)
	{
	  printf("Invalid team number: must be different from zero\n");
	  return (-1);
	}
      if (tmp < 0)
	{
	  printf("Invalid team number: must be > 0\n");
	  return (-1);
	}
    }
  return (tmp);
}

int		init_player(t_princ *lemip, char *team_number, char *ia_int)
{
  char		good;
  char		*tmp;

  good = 1;
  if ((lemip->player.team = get_team_number(team_number)) == -1)
    return (EXIT_FAILURE);
  tmp = (char *)(lemip->addrmap);
  while (good)
    {
      lemip->player.ia.x = rand() % MAP_LEN;
      lemip->player.ia.y = rand() % MAP_LEN;
      if (tmp[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] == 0)
	{
	  tmp[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] =
	    lemip->player.team;
	  good = 0;
	}
    }
  if (ia_int && ia_int[0] == '0')
    lemip->ia_take = 0;
  else
    lemip->ia_take = 1;
  return (EXIT_SUCCESS);
}
