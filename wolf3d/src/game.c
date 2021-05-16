/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sat Jan 12 15:30:11 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <X11/X.h>
#include "header.h"

int		wolf3d(t_all *all)
{
  int		fd;
  int		**map;

  if ((all->lvl = set_lvl(all, 1)) == NULL)
    return (1);
  circulaire(all);
  lvl_up(all);
  if ((all->wall = malloc(sizeof(t_wall))) == NULL)
    return (my_putstr("error in alloc\n"));
  if ((all->tmp = malloc(sizeof(t_wall))) == NULL)
    return (my_putstr("error in alloc\n"));
  mlx_do_key_autorepeaton(all->info->mlx_ptr);
  if (all->mode != NULL)
    {
      mlx_hook(all->info->win_ptr, KeyPress, KeyPressMask, gere_key, all);
      aff_map(all);
    }
  mlx_expose_hook(all->info->win_ptr, gere_expose, all->info);
  mlx_loop(all->info->mlx_ptr);
}

int		my_wait(int keycode, t_all *all)
{
  mlx_hook(all->info->win_ptr, KeyPress, KeyPressMask, gere_key, all);
  aff_map(all);
}

int		begin(t_all *all)
{
  t_info	*info;
  t_xpm		*title;

  info = all->info;
  if ((title = textures(all->info, "img/begin.xpm")) == NULL)
    return (my_putstr("Fail in texture load\n"));
  mlx_hook(all->info->win_ptr, KeyPress, KeyPressMask, my_wait, all);
  my_img_put_to_img(0, 0, all, title);
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img, 0, 0);
  return (0);
}

int		game(char *path)
{
  t_all		*all;
  t_info	*info;

  my_putstr("Loading...\n");
  if ((all = malloc(sizeof(*all))) == NULL)
    return (my_putstr("error in malloc\n"));
  if ((info = malloc(sizeof(*info))) == NULL)
    return (my_putstr("error in malloc\n"));
  if ((info->mlx_ptr = mlx_init()) == NULL)
    return (my_putstr("Fail in x-connect\n"));
  info->win_ptr = mlx_new_window(info->mlx_ptr, SIZE_X, SIZE_Y, "Wolf3D");
  if ((info->img = textures(info, NULL)) == NULL)
    return (my_putstr("Fail in texture load\n"));
  all->info = info;
  all->hands = 0;
  all->mode = path;
  if (all->mode == NULL)
    if (begin(all) != 0)
      return (1);
  if (wolf3d(all) == 1)
    return (1);
  return (0);
}
