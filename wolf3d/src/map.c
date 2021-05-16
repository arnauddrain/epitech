/*
** map.c for map in /home/drain_a//tps/i_graph/wolf3d/v7
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Jan 10 18:24:22 2013 arnaud drain
** Last update Fri Jan 11 22:21:57 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include "map.h"

int		gere_map_expose(t_info *info)
{
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
}

int		gere_map_key(int keycode, t_all *all)
{
  if (keycode == ESCAPE)
    exit(0);
  if (keycode == ENTER)
    create_file(all);
}

int		gere_map_mouse(int button, int x, int y, t_all *all)
{
  t_info	*info;

  info = all->info;
  x = x / ((double)SIZE_X / all->size->x);
  y = y / ((double)SIZE_Y / all->size->y);
  if (x != 1 || y != 1)
    if (x > 0 && x < all->size->x - 1 && y > 0 && y < all->size->y - 1)
      all->map[y][x] = (all->map[y][x] == 0);
  set_img(all);
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
}

t_info		*set_info(char *path)
{
  t_info	*info;

  if ((info = malloc(sizeof(*info))) == NULL)
    return (NULL);
  if ((info->mlx_ptr = mlx_init()) == NULL)
    return (NULL);
  info->win_ptr = mlx_new_window(info->mlx_ptr, SIZE_X, SIZE_Y, path);
  if ((info->img_ptr = mlx_new_image(info->mlx_ptr, SIZE_X, SIZE_Y)) == NULL)
    return (NULL);
  return (info);
}

int		map()
{
  t_all		*all;
  t_info	*info;

  if ((all = malloc(sizeof(*all))) == NULL)
    return (my_putstr("Error in alloc\n"));
  if ((all->path = get_map_name()) == NULL)
    return (my_putstr("Error in alloc\n"));
  if ((all->size = get_size()) == NULL)
    return (my_putstr("Error in alloc\n"));
  if ((all->info = set_info(all->path)) == NULL)
    return (my_putstr("Error in mlx connect\n"));
  if ((all->map = create_map(all->size)) == NULL)
    return (my_putstr("Error in alloc\n"));
  set_img(all);
  info = all->info;
  mlx_expose_hook(all->info->win_ptr, gere_map_expose, all->info);
  mlx_key_hook(all->info->win_ptr, gere_map_key, all);
  mlx_mouse_hook(all->info->win_ptr, gere_map_mouse, all);
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
  mlx_loop(all->info->mlx_ptr);
  return (0);
}
