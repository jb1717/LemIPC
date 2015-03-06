/*
** ia_easy.c for ia_easy in /home/tran_0/rendu/PSU_2014_lemipc
** 
** Made by David Tran
** Login   <tran_0@epitech.net>
** 
** Started on  Thu Mar  5 18:27:11 2015 David Tran
** Last update Fri Mar  6 20:48:39 2015 David Tran
*/

#include "lemipc.h"

int	is_alive(t_princ *lemip)
{
  char	*tmp;
  t_pos	square;
  char	ok;

  ok = 0;
  tmp = (char *)lemip->addrmap;
  square.y = lemip->player.ia.y - 1;
  while (square.y <= lemip->player.ia.y + 1)
    {
      square.x = lemip->player.ia.x - 1;
      while (square.x <= lemip->player.ia.x + 1)
	{
	  if (square.x >= 0 && square.x < MAP_LEN &&
	      square.y >= 0 && square.y < MAP_LEN &&
	      tmp[square.y * MAP_LEN + square.x] != 0 &&
	      tmp[square.y * MAP_LEN + square.x] != lemip->player.team)
	    ok++;
	  square.x++;
	}
      square.y++;
    }
  return (ok);
}

void	move_ia(t_princ *lemip)
{
  char	xmove;
  char	ymove;
  char	*tmp;

  srand(time(NULL));
  tmp = (char *)lemip->addrmap;
  xmove = rand() % 3 - 1;
  ymove = rand() % 3 - 1;
  if ((lemip->player.ia.x + xmove) >= 0 && (lemip->player.ia.y + ymove) >= 0 &&
      (lemip->player.ia.x + xmove) < MAP_LEN &&
      (lemip->player.ia.y + ymove) < MAP_LEN &&
      tmp[(lemip->player.ia.y + ymove) * MAP_LEN + lemip->player.ia.x + xmove]
      == 0)
    {
      tmp[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] = 0;
      lemip->player.ia.y += ymove;
      lemip->player.ia.x += xmove;
      tmp[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x]
	= lemip->player.team;
    }
}

int	ia_easy(t_princ *lemip)
{
  char	*tmp;

  tmp = (char *)lemip->addrmap;
  printf("enter\n");
  while (42)
    {
      lemip->sops.sem_op = -1;
      if (semop(lemip->sem_id, &lemip->sops, 1) == -1)
	return (-1);
      sleep(1);
      lemip->sops.sem_op = 1;
      if (is_alive(lemip) > 1)
	{
	  tmp[lemip->player.ia.y * MAP_LEN + lemip->player.ia.x] = 0;
	  if (semop(lemip->sem_id, &lemip->sops, 1) == -1)
	    return (-1);
	  return (2);
	}
      move_ia(lemip);
      if (semop(lemip->sem_id, &lemip->sops, 1) == -1)
	return (-1);
    }
}

void	*ia_thread(void *princ)
{
  ia_easy((t_princ *)princ);
  return (NULL);
}
