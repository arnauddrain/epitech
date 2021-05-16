/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sat Jan 12 15:29:31 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <X11/X.h>
#include "header.h"

t_xpm		*find_texture(int nb, t_texts *texts)
{
  if (nb > 10 && nb < 20)
    return (texts->secret);
  if (nb == 2)
    return (texts->end);
  return (texts->wall);
}

void		trace_col(t_all *all, int x, t_texts *texts)
{
  int		y;
  int		height;
  int		color;

  all->wall->dist = all->wall->dist + (all->wall->dist == 0) * PRECI;
  height = (SIZE_Y - SIZE_Y / (all->wall->dist / (double)PRECI)) / 2;
  color = mlx_get_color_value(all->info->mlx_ptr, 0x454545);
  y = 0;
  while (y < height)
    my_pixel_put_to_image(x, y++, all->info->img, color);
  y = (height < 0) * height + y * (height >= 0);
  height = (SIZE_Y - height) * (SIZE_Y > height) + SIZE_Y * (SIZE_Y < height);
  if (all->mode != NULL)
    {
      y = y * (y > 0);
      color = mlx_get_color_value(all->info->mlx_ptr, all->wall->color);
      while (y < height)
	my_pixel_put_to_image(x, y++, all->info->img, color);
    }
  else
    my_wall_put_to_image(x, y, all, find_texture(all->wall->text, texts));
  y = height;
  color = mlx_get_color_value(all->info->mlx_ptr, 0x666666);
  while (y < SIZE_Y)
    my_pixel_put_to_image(x, y++, all->info->img, color);
}

int		aff_map(t_all *all)
{
  t_coord	*vect;
  t_info	*info;
  t_xpm		*hands;
  int		x;
  int		y;

  if ((vect = malloc(sizeof(t_pos))) == NULL)
    return (my_putstr("error in malloc\n"));
  hands = all->texts->hands;
  calc_vect(all, vect);
  info = all->info;
  free(vect);
  x = SIZE_X / 2 - (hands->x / 2);
  y = SIZE_Y - hands->y + all->hands;
  my_img_put_to_img(x, y, all, hands);
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img, 0, 0);
}
