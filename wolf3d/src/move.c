/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Fri Jan 11 12:53:01 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <X11/X.h>
#include "header.h"

int		player_pos(t_all *all)
{
  int		ret;

  ret = all->map[all->pos->y / PRECI][all->pos->x / PRECI];
  return (ret);
}

void		hands(t_all *all)
{
  static int	sens;

  sens = sens * (all->hands != 0) + 2 * (all->hands == 0);
  all->hands = all->hands + sens;
  if (all->hands == 10)
    sens = -2;
}

void		angle(t_pos *pos, int keycode)
{
  int		angle;

  if (keycode == RIGHT)
    angle = pos->alpha + 3000 / 180 * M_PI;
  if (keycode == LEFT)
    angle = pos->alpha - 3000 / 180 * M_PI;
  angle = (int)(angle + 2000 * M_PI) % (int)(2000 * M_PI);
  pos->alpha = angle;
}

int		verif_move(int **map, int x, int y)
{
  if (map[(y + 5) / PRECI][(x + 5) / PRECI] == 1)
    return (0);
  if (map[(y + 5) / PRECI][(x - 5) / PRECI] == 1)
    return (0);
  if (map[(y - 5) / PRECI][(x + 5) / PRECI] == 1)
    return (0);
  if (map[(y - 5) / PRECI][(x - 5) / PRECI] == 1)
    return (0);
  return (1);
}

void		move(t_pos *pos, int **map, int keycode, t_all *all)
{
  double	angle;
  int		x;
  int		y;

  angle = (double)pos->alpha / 1000;
  if (keycode == UP)
    {
      x = pos->x + cos(angle) * PRECI / 10;
      y = pos->y + sin(angle) * PRECI / 10;
    }
  if (keycode == DOWN)
    {
      x = pos->x - cos(angle) * PRECI / 10;
      y = pos->y - sin(angle) * PRECI / 10;
    }
  if (verif_move(map, x, y))
    {
      pos->x = x;
      pos->y = y;
    }
  else if (verif_move(map, x, pos->y))
    pos->x = x;
  else if (verif_move(map, pos->x, y))
    pos->y = y;
  hands(all);
}
