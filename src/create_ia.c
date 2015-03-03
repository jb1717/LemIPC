/*
** create_ia.c for lemipc in /home/jibb/rendu/PSU_2014_lemipc
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Tue Mar  3 10:53:23 2015 Jean-Baptiste Grégoire
** Last update Tue Mar  3 12:19:27 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

void		launch_player(t_princ *lemip)
{
  int		x;
  int		y;
  char		good;
  char		*tmp;

  good = 1;
  tmp = (char *)(lemip->addrmap);
  while (good)
    {
      x = rand() % MAP_LEN;
      y = rand() % MAP_LEN;
      if (tmp[y * MAP_LEN + x] == 0)
	{
	  tmp[y * MAP_LEN + x] = 1;
	  good = 0;
	}
    }
}
