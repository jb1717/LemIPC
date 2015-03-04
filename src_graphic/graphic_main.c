/*
** graphic_main.c for lemipc in /home/tran_0/rendu/PSU_2014_lemipc/src
** 
** Made by David Tran
** Login   <tran_0@epitech.net>
** 
** Started on  Tue Mar  3 21:47:51 2015 David Tran
** Last update Wed Mar  4 22:21:39 2015 David Tran
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
	  if (str[y * MAP_LEN + x] != 0)
	    {
	      graph->pos.x = WIN_LEN / MAP_LEN * x;
	      graph->pos.y = WIN_LEN / MAP_LEN * y;
	      graph->pos.w = WIN_LEN / MAP_LEN;
	      graph->pos.h = WIN_LEN / MAP_LEN;
	      SDL_FillRect
		(graph->screen, &graph->pos, SDL_MapRGB
		 (graph->screen->format, (str[y * MAP_LEN + x] * 15) % 255,
		  (str[y * MAP_LEN + x] * 52) % 255,
		  (str[y * MAP_LEN + x] * 42)) % 255);
	    }
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
      printf("No Shared memory created.\nUSAGE : Launch once \'./lemipc [team number]'\n");
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

void		*event_SDL(void *graphs)
{
  t_graph	*graph;
  SDL_Event	event;

  graph = (t_graph *)graphs;
  while (42)
    {
      SDL_WaitEvent(&event);
      if (event.key.keysym.sym == SDLK_ESCAPE)
	{
	  graph->exit = 1;
	  SDL_FreeSurface(graph->screen);
	  SDL_Quit();
	  return (NULL);
	}
    }
}

int		main()
{
  t_graph	graph;
  pthread_t	event;

  graph.exit = 0;
  if (get_memory(&graph) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    return (EXIT_FAILURE);
  graph.screen = SDL_SetVideoMode(WIN_LEN, WIN_LEN, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("PSU_2014_lemipc", NULL);
  if (pthread_create(&event, NULL, event_SDL, &graph) != 0)
    return (EXIT_FAILURE);
  while (42)
    {
      if (graph.exit == 1)
	return (EXIT_SUCCESS);
      draw_shared_map(&graph);
      sleep(1);
    }
  return (EXIT_SUCCESS);
}
