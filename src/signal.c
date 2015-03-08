/*
** signal.c for LemIPC in /home/jibb/rendu/PSU_2014_lemipc/src
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Sun Mar  8 14:31:28 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  8 22:09:46 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

void		get_sigint(int sig)
{
  t_princ	*lemip;

  if (sig == SIGINT)
    {
      lemip = init_resources(1);
      lemip->map[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] = 0;
      if (lemip->first == 2)
	{
	  lemip->map[MAP_LEN * MAP_LEN + 1] = -1;
	  destroy_resources(lemip);
	}
      exit(EXIT_SUCCESS);
    }
}
