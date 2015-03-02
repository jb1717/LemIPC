/*
** main.c for main in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 15:08:16 2015 David Tran
** Last update Mon Mar  2 13:33:56 2015 Jean-Baptiste Grégoire
*/

#include <unistd.h>
#include "lemipc.h"

void		print_map(t_princ *lemip)
{
  char		*tmp;
  int		i;

  i = 0;
  tmp = (char *)lemip->addrmap;
  while (i < MAP_LEN * MAP_LEN)
    {
      printf("%d", tmp[i]);
      if ((i + 1) % MAP_LEN == 0)
	printf("\n");
      i++;
    }
}

int		main()
{
  t_princ	lemip;
  char		path[256];

  lemip.key = ftok(getcwd(path, 256), 0);
  if ((lemip.shm_id = shmget(lemip.key,
			     MAP_LEN * MAP_LEN, SHM_R | SHM_W)) == -1)
    {
      lemip.shm_id = shmget(lemip.key, MAP_LEN * MAP_LEN,
			    IPC_CREAT | SHM_R | SHM_W);
      lemip.addrmap = shmat(lemip.shm_id, NULL, SHM_R | SHM_W);
      bzero(lemip.addrmap, MAP_LEN * MAP_LEN);
    }
  else
    lemip.addrmap = shmat(lemip.shm_id, NULL, SHM_R | SHM_W);
  print_map(&lemip);
return (EXIT_SUCCESS);
}
