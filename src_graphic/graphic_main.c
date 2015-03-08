/*
** graphic_main.c for lemipc in /home/tran_0/rendu/PSU_2014_lemipc/src
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Tue Mar  3 21:47:51 2015 David Tran
** Last update Sun Mar  8 21:18:20 2015 David Tran
*/

#include "lemipc.h"

void	draw_quadra(t_graph *graph)
{
  int	i;

  i = 0;
  while (i < MAP_LEN)
    {
      vlineColor(graph->screen, WIN_LEN / MAP_LEN * i, 0, WIN_LEN, 0xFFFFFF);
      i++;
    }
  i = 0;
  while (i < MAP_LEN)
    {
      hlineColor(graph->screen, 0, WIN_LEN, WIN_LEN / MAP_LEN * i, 0xFFFFFF);
      i++;
    }
  graph->pos.x = 0;
  graph->pos.y = 0;
  SDL_Flip(graph->screen);
}

void		draw_shared_map(t_graph *graph)
{
  int		x;
  int		y;
  char		*str;

  y = 0;
  str = (char *)graph->princ.addrmap;
  while (y < MAP_LEN)
    {
      x = 0;
      while (x < MAP_LEN)
	{
	  init_pos(graph, x, y);
	  fill_point_rect(graph, x, y, str);
	  x++;
	}
      y++;
    }
  SDL_Flip(graph->screen);
}

int		get_memory(t_graph *graph)
{
  char		path[256];

  if ((graph->princ.key = ftok(getcwd(path, 256), 0)) == -1)
    return (EXIT_FAILURE);
  if ((graph->princ.shm_id = shmget(graph->princ.key,
				   MAP_LEN * MAP_LEN, SHM_R | SHM_W)) == -1)
    {
      printf("No Shared memory created.\nUSAGE ");
      printf(": Launch once \'./lemipc [team number]'\n");
      return (EXIT_FAILURE);
    }
  if ((graph->princ.shm_id = shmget(graph->princ.key,
			      MAP_LEN * MAP_LEN, SHM_R | SHM_W)) == -1)
    return (EXIT_FAILURE);
  if ((graph->princ.addrmap = shmat(graph->princ.shm_id, NULL,
			      SHM_R | SHM_W)) == (void *)-1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

void		launch_all(t_graph *graph, SDL_Event *event)
{
  char		*tmp;

  tmp = (char *)graph->princ.addrmap;
  while (42)
    {
      SDL_PollEvent(event);
      draw_shared_map(graph);
      if (event->key.keysym.sym == SDLK_ESCAPE || event->type == SDL_QUIT ||
	  tmp[MAP_LEN * MAP_LEN + 1] == -1)
	{
	  tmp[MAP_LEN * MAP_LEN + 1] = -1;
	  SDL_FreeSurface(graph->screen);
	  SDL_Quit();
	  return ;
	}
      sleep(0.5);
    }
}

int		main()
{
  t_graph	graph;
  SDL_Event	even;

  graph.exit = 0;
  if (get_memory(&graph) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    return (EXIT_FAILURE);
  graph.screen = SDL_SetVideoMode(WIN_LEN, WIN_LEN, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("PSU_2014_lemipc", NULL);
  launch_all(&graph, &even);
  return (EXIT_SUCCESS);
}
