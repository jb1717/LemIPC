/*
** main.c for main in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 15:08:16 2015 David Tran
** Last update Mon Mar  2 16:49:27 2015 Jean-Baptiste Grégoire
*/

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

int		init_resources(t_princ *lemip)
{
  char		path[256];

  if ((lemip->key = ftok(getcwd(path, 256), 0)) == -1)
    return (EXIT_FAILURE);
  if ((lemip->shm_id = shmget(lemip->key,
			     MAP_LEN * MAP_LEN, SHM_R | SHM_W)) == -1)
    {
      if ((lemip->shm_id = shmget(lemip->key, MAP_LEN * MAP_LEN,
				 IPC_CREAT | SHM_R | SHM_W)) == -1)
	return (EXIT_FAILURE);
      if ((lemip->addrmap = shmat(lemip->shm_id, NULL,
				 SHM_R | SHM_W)) == (void *)-1)
	return (EXIT_FAILURE);
      if ((lemip->msg_id = msgget(lemip->key,
				 IPC_CREAT | SHM_R | SHM_W)) == -1)
	return (EXIT_FAILURE);
      bzero(lemip->addrmap, MAP_LEN * MAP_LEN);
      launch_thread(lemip);
      shmctl(lemip->shm_id, IPC_RMID, NULL);
    }
  else
    lemip->addrmap = shmat(lemip->shm_id, NULL, SHM_R | SHM_W);
  return (EXIT_SUCCESS);
}

int		main()
{
  t_princ	lemip;

  if (init_resources(&lemip) == -1)
    {
      fprintf(stderr, "Can't create resources requiered for the battle !\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
