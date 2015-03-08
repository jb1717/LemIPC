/*
** graphic_setpos.c for graphic_setpos in /home/tran_0/rendu/PSU_2014_lemipc/src_graphic
** 
** Made by David Tran
** Login   <tran_0@epitech.net>
** 
** Started on  Sun Mar  8 19:05:14 2015 David Tran
** Last update Sun Mar  8 19:07:54 2015 David Tran
*/

#include "lemipc.h"

void		init_pos(t_graph *graph, int x, int y)
{
  graph->pos.x = WIN_LEN / MAP_LEN * x;
  graph->pos.y = WIN_LEN / MAP_LEN * y;
  graph->pos.w = WIN_LEN / MAP_LEN;
  graph->pos.h = WIN_LEN / MAP_LEN;
}

void		fill_point_rect(t_graph *graph, int x, int y, char *str)
{
  if (str[y * MAP_LEN + x] != 0)
    SDL_FillRect
      (graph->screen, &graph->pos, SDL_MapRGB
       (graph->screen->format, (str[y * MAP_LEN + x] * 15) % 255,
	(str[y * MAP_LEN + x] * 52) % 255,
	(str[y * MAP_LEN + x] * 82) % 255));
  else
    SDL_FillRect
      (graph->screen, &graph->pos, SDL_MapRGB
       (graph->screen->format, 0, 0, 0));
}
