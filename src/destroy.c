/*
** destroy_resources.c for lemipc in /home/jibb/rendu/PSU_2014_lemipc/src
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Tue Mar  3 11:33:29 2015 Jean-Baptiste Grégoire
** Last update Tue Mar  3 12:59:55 2015 Jean-Baptiste Grégoire
*/

#include "lemipc.h"

int		destroy_resources(t_princ *lemip)
{
  if (shmdt(lemip->addrmap) == -1)
    {
      perror("Destruction of shared memory error");
      return (EXIT_FAILURE);
    }
  if (msgctl(lemip->msg_id, IPC_RMID, NULL) == -1)
    {
      perror("Destruction of message queue error");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
