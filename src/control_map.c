/*
** control_map.c for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
** 
** Made by David Tran
** Login   <tran_0@epitech.net>
** 
** Started on  Mon Mar  2 14:24:02 2015 David Tran
** Last update Mon Mar  2 15:32:59 2015 David Tran
*/

#include "lemipc.h"

void	*launch_map_IA(void *iathread)
{
  return (0);
}

void		launch_thread(t_princ *lemip)
{
  pthread_t	take_map;
  int		back;

  if ((back = pthread_create(&take_map, NULL, launch_map_IA, lemip)) == 0)
    pthread_join(take_map, NULL);
  else if (back == -1)
    return ;
  //  else
  //  launch_player(lemip);
}
