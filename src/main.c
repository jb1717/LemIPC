/*
** main.c for main in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Sun Mar  1 15:08:16 2015 David Tran
** Last update Sun Mar  8 21:49:09 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

int		init_memory(t_princ *lemip)
{
  int		ret;

  ret = EXIT_SUCCESS;
  lemip->sops.sem_num = 0;
  lemip->sops.sem_flg = 0;
  if ((lemip->shm_id = shmget(lemip->key,
			      MAP_LEN * MAP_LEN + 1, SHM_R | SHM_W)) == -1)
    {
      if ((lemip->shm_id = shmget(lemip->key, MAP_LEN * MAP_LEN + 1,
				  IPC_CREAT | SHM_R | SHM_W)) == -1)
	return (EXIT_FAILURE);
      if ((lemip->addrmap = shmat(lemip->shm_id, NULL,
				  SHM_R | SHM_W)) == (void *)-1)
	return (EXIT_FAILURE);
      bzero(lemip->addrmap, MAP_LEN * MAP_LEN + 2);
      ret = 2;
    }
  else
    lemip->addrmap = shmat(lemip->shm_id, NULL, SHM_R | SHM_W);
  return (ret);
}

t_princ			*init_resources(int flag)
{
  char			path[256];
  static t_princ	lemip;

  if (flag)
    return (&lemip);
  srand(time(NULL));
  if ((lemip.key = ftok(getcwd(path, 256), 0)) == -1)
    return (NULL);
  if ((lemip.first = init_memory(&lemip)) == EXIT_FAILURE)
    return (NULL);
  lemip.map = (char *)(lemip.addrmap);
  if ((lemip.msg_id = msgget(lemip.key, SHM_R | SHM_W)) == -1)
    if ((lemip.msg_id = msgget(lemip.key, IPC_CREAT | SHM_R | SHM_W)) == -1)
      return (NULL);
  if ((lemip.sem_id = semget(lemip.key, 1, SHM_R | SHM_W)) == -1)
    {
      if ((lemip.sem_id = semget(lemip.key, 1, IPC_CREAT | SHM_R | SHM_W))
	  == -1 || semctl(lemip.sem_id, 0, SETVAL, 1) == -1)
	return (NULL);
    }
  bzero(&(lemip.msgbuf), sizeof(t_msgbuf));
  signal(SIGINT, get_sigint);
  return (&lemip);
}

int		main(int argc, char **argv)
{
  t_princ	*lemip;

  if ((lemip = init_resources(0)) == NULL)
    {
      fprintf(stderr, "Can't create resources requiered for the battle !\n");
      return (EXIT_FAILURE);
    }
  if (init_player(lemip, argv[1], (argc > 1) ? argv[2] : NULL) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (lemip->first == 2)
    {
      exec_map(lemip);
      destroy_resources(lemip);
    }
  else
    (lemip->ia_take == 1) ? ia_intermediate(lemip) : ia_easy(lemip);
  return (EXIT_SUCCESS);
}
