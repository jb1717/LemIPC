/*
** main.c for main in /home/tran_0/rendu/PSU_2014_lemipc
** 
** Made by David Tran
** Login   <tran_0@epitech.net>
** 
** Started on  Sun Mar  1 15:08:16 2015 David Tran
** Last update Sun Mar  1 20:52:01 2015 David Tran
*/

#include "lemipc.h"

int		main(UNUSED int ac, UNUSED char **av)
{
  t_princ	lemip;
  char		*path;

  if (!(path = getcwd()))
    return (EXIT_FAILURE);
  lemip.key = ftok(path, 0);
  if ((lemip.shm_id = shmget(lemip.key,
			     MAP_LEN * MAP_LEN, SHM_R | SHM_W)) == -1)
    {
      lemip.shm_id = shmget(lemip.key, MAP_LEN * MAP_LEN,
			    IPC_CREATE | SHM_R | SHM_W);
    }
  lemip.addrmap = shmat(lemip.shm_id, NULL, SHM_R | SHM_W);
}
