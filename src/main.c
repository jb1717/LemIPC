/*
** main.c for main in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 15:08:16 2015 David Tran
** Last update Tue Mar  3 12:57:58 2015 Jean-Baptiste Grégoire
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

  srand(time(NULL));
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
      shmctl(lemip->shm_id, IPC_RMID, NULL);
    }
  else
    lemip->addrmap = shmat(lemip->shm_id, NULL, SHM_R | SHM_W);
  return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
  t_princ	lemip;

  if (argc != 2)
    {
      printf("Usage: %s [number team]\n", argv[0]);
      return (EXIT_SUCCESS);
    }
  if (init_resources(&lemip) == -1)
    {
      fprintf(stderr, "Can't create resources requiered for the battle !\n");
      return (EXIT_FAILURE);
    }
  init_player(&lemip, argv[2]);
  return (EXIT_SUCCESS);
}
