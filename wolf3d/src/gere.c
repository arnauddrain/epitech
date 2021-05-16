/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sat Jan 12 10:11:30 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <X11/X.h>
#include "header.h"

int		gere_expose(t_info *info)
{
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img, 0, 0);
}

int		gere_key(int keycode, t_all *all)
{
  t_info	*info;
  t_pos		*pos;
  int		**map;

  info = all->info;
  pos = all->pos;
  map = all->map;
  if (keycode == ESCAPE)
    {
      my_putstr("Exit with success !\n");
      end(all);
    }
  if (keycode == LEFT || keycode == RIGHT)
    angle(all->pos, keycode);
  if (keycode == TAB)
    lvl_up(all);
  if (keycode == UP || keycode == DOWN)
    move(all->pos, all->map, keycode, all);
  if (map[pos->y / PRECI][pos->x / PRECI] == 2)
    lvl_up(all);
  aff_map(all);
}
