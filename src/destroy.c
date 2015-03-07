/*
** destroy_resources.c for lemipc in /home/jibb/rendu/PSU_2014_lemipc/src
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Tue Mar  3 11:33:29 2015 Jean-Baptiste Grégoire
** Last update Sat Mar  7 19:01:29 2015 David Tran
*/

#include "lemipc.h"

int		destroy_resources(t_princ *lemip)
{
  if (shmctl(lemip->shm_id, IPC_RMID, NULL) == -1)
    {
      perror("Destruction of shared memory error");
      return (EXIT_FAILURE);
    }
  if (msgctl(lemip->msg_id, IPC_RMID, NULL) == -1)
    {
      perror("Destruction of message queue error");
      return (EXIT_FAILURE);
    }
  if (semctl(lemip->sem_id, lemip->sops.sem_num, IPC_RMID) == -1)
    {
      perror("Destruction of Semaphore error");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
