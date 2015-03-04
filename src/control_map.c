/*
** control_map.c for lemipc in /home/tran_0/rendu/PSU_2014_lemipc
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Mon Mar  2 14:24:02 2015 David Tran
** Last update Wed Mar  4 21:41:53 2015 David Tran
*/

#include "lemipc.h"

void		*launch_map_IA(void *iathread)
{
  t_princ	*lemip;
  t_msgbuf	*msgbuf;

  msgbuf = NULL;
  while (42)
     {
       lemip = (t_princ *)(iathread);
       if (msgrcv(lemip->msg_id, msgbuf, sizeof(t_msgbuf), MSG_GEN, 0) == -1)
	 {
	   perror("Can't receive message");
	   return ((void *)(EXIT_FAILURE));
	 }
     }
  return ((void *)(EXIT_SUCCESS));
}

void		launch_thread(t_princ *lemip)
{
  pthread_t	take_map;
  int		back;

  if ((back = pthread_create(&take_map, NULL, launch_map_IA, lemip)) == 0)
    pthread_join(take_map, NULL);
  else if (back == -1)
    return ;
  /* else */
  /*    launch_player(lemip); */
}
