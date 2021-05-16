/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sat Jan 12 14:48:39 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <X11/X.h>
#include <stdio.h>
#include "header.h"

int		is_to_print(t_all *all, int x, int y)
{
  int		x2;
  int		y2;
  int		pos;
  int		i;

  x2 = x / PRECI;
  y2 = y / PRECI;
  i = 0;
  pos = all->map[y2][x2];
  if (pos > 0 && pos < 10)
    return (1);
  if ((pos > 10) && (((pos % 2 == 1) && (y % PRECI == 0)) ||
		     ((pos % 2 == 0) && (x % PRECI == 0))))
    {
      i = (pos % 10 == 1 && all->pos->y < y);
      i = i + (pos % 10 == 3 && all->pos->y > y);
      i = i + (pos % 10 == 2 && all->pos->x < x);
      i = i + (pos % 10 == 4 && all->pos->x > x);
    }
  return (i);
}

void		calc_x(t_all *all, t_coord *vect, t_wall *wall)
{
  int		x;
  int		y;
  int		pos;
  int		k;

  x = (all->pos->x / PRECI + (vect->x < 0)) * PRECI;
  vect->x = vect->x + (vect->x == 0);
  while (x < all->max->x * PRECI && x >= 0 && wall->dist == 0)
    {
      k = (PRECI * (x - all->pos->x)) / vect->x;
      y = all->pos->y + (k * vect->y) / PRECI;
      pos = x - PRECI * (vect->x < 0);
      if (y < all->max->y * PRECI && y >= 0)
	if (pos >= 0 && pos < all->max->x * PRECI)
	  if ((k > 0) && (wall->dist == 0 || k < wall->dist))
	    if (is_to_print(all, pos, y))
	      {
		wall->dist = k;
		wall->x = y % PRECI;
		wall->text = all->map[y / PRECI][pos / PRECI];
	      }
      x = x + PRECI * (vect->x > 0) - PRECI * (vect->x < 0);
    }
}

void		calc_y(t_all *all, t_coord *vect, t_wall *wall)
{
  int		x;
  int		y;
  int		pos;
  int		k;

  y = (all->pos->y / PRECI + (vect->y < 0)) * PRECI;
  vect->y = vect->y + (vect->y == 0);
  while (y < all->max->y * PRECI && y >= 0 && wall->dist == 0)
    {
      k = (PRECI * (y - all->pos->y)) / vect->y;
      x = all->pos->x + (k * vect->x) / PRECI;
      pos = y - PRECI * (vect->y < 0);
      if (x < all->max->x * PRECI && x >= 0)
	if (pos >= 0 && pos < all->max->y * PRECI)
	  if ((k > 0) && (wall->dist == 0 || k < wall->dist))
	    if (is_to_print(all, x, pos))
	      {
		wall->dist = k;
		wall->x = x % PRECI;
		wall->text = all->map[pos / PRECI][x / PRECI];
	      }
      y = y + PRECI * (vect->y > 0) - PRECI * (vect->y < 0);
    }
}

void		calc_dist(t_all *all, t_coord *vect)
{
  t_wall	*wall;
  t_wall	*tmp;

  wall = all->wall;
  tmp = all->tmp;
  wall->dist = 0;
  tmp->dist = 0;
  wall->text = 1;
  calc_y(all, vect, wall);
  calc_x(all, vect, tmp);
  wall->color = 0x00ff00;
  if (vect->y > 0)
    wall->color = 0xff0000;
  if ((tmp->dist < wall->dist && tmp->dist != 0) || wall->dist == 0)
    {
      wall->dist = tmp->dist;
      wall->x = tmp->x;
      wall->text = tmp->text;
      wall->color = 0x0000ff;
      if (vect->x > 0)
	wall->color = 0xff00ff;
    }
}

void		calc_vect(t_all *all, t_coord *vect)
{
  int		i;
  int		tmp_x;
  int		tmp_y;
  double	cos_alpha;
  double	sin_alpha;

  i = 0;
  cos_alpha = cos(all->pos->alpha / 1000.0);
  sin_alpha = sin(all->pos->alpha / 1000.0);
  while (i < SIZE_X)
    {
      tmp_x = 0.5 * PRECI;
      tmp_y = (PRECI * (SIZE_X / 2 - i)) / SIZE_X;
      vect->x = tmp_x * cos_alpha - tmp_y * sin_alpha;
      vect->y = tmp_x * sin_alpha + tmp_y * cos_alpha;
      calc_dist(all, vect);
      i = i + 1;
      trace_col(all, SIZE_X - i, all->texts);
    }
}
