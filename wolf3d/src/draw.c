/*
** img1.c for tp in /home/drain_a//tps/i_graph/tp2
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 15 12:31:15 2012 arnaud drain
** Last update Sat Jan 12 10:20:14 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include "header.h"

int		my_pixel_put_to_image(int x, int y, t_xpm *img, int col)
{
  char		*color;
  int		pos;
  int		i;

  color = &col;
  if (x < 0 || y < 0 || x > SIZE_X || y > SIZE_Y)
    return (1);
  pos = (img->sizeline * y) + (x * (img->bpp / 8));
  i = 0;
  while (i < (img->bpp / 8))
    {
      img->data[pos + i] = color[i];
      i = i + 1;
    }
  return (0);
}

t_xpm		*textures(t_info *info, char *path)
{
  t_xpm		*xpm;
  int		bpp;
  int		sizeline;
  int		endian;

  if ((xpm = malloc(sizeof(*xpm))) == NULL)
    return (NULL);
  if (path != NULL)
    xpm->img = mlx_xpm_file_to_image(info->mlx_ptr, path, &xpm->x, &xpm->y);
  else
    {
      xpm->img = mlx_new_image(info->mlx_ptr, SIZE_X, SIZE_Y);
      xpm->x = SIZE_X;
      xpm->y = SIZE_Y;
    }
  if (xpm->img == NULL)
    return (NULL);
  xpm->data = mlx_get_data_addr(xpm->img, &bpp, &sizeline, &endian);
  if (xpm->data == NULL)
    return (NULL);
  xpm->bpp = bpp;
  xpm->sizeline = sizeline;
  xpm->endian = endian;
  return (xpm);
}

int		is_printable(t_xpm *texture, int pos, t_info *info)
{
  int		color;
  char		*col;
  int		i;

  color = mlx_get_color_value(info->mlx_ptr, 0x00ffff);
  col = &color;
  i = 0;
  while (i < (texture->bpp / 8))
    {
      if (texture->data[pos + i] != col[i])
	return (1);
      i = i + 1;
    }
  return (0);
}

void		my_img_put_to_img(int x, int y, t_all *all, t_xpm *texture)
{
  int		pos_t;
  int		pos_i;
  int		i;

  pos_i = all->info->img->sizeline * y + x * all->info->img->bpp / 8;
  pos_t = 0;
  y = 0;
  while (y < texture->y && y < all->info->img->y)
    {
      x = 0;
      while (x < texture->x && x < all->info->img->x)
	{
	  i = 0;
	  if (is_printable(texture, pos_t, all->info))
	    while (i < (all->info->img->bpp / 8))
	      all->info->img->data[pos_i + i] = texture->data[pos_t + i++];
	  pos_t = pos_t + (texture->bpp / 8);
	  pos_i = pos_i + (all->info->img->bpp / 8);
	  x = x + 1;
	}
      pos_i = pos_i + all->info->img->sizeline - x * (all->info->img->bpp / 8);
      pos_t = pos_t + texture->sizeline - x * (texture->bpp / 8);
      y = y + 1;
    }
}

void		my_wall_put_to_image(int x, int begin, t_all *all, t_xpm *texture)
{
  t_xpm		*img;
  int		size;
  int		pos_i;
  int		pos_t;
  int		i;

  img = all->info->img;
  size = SIZE_Y - 2 * begin;
  pos_i = (img->sizeline * begin) + (x * (img->bpp / 8));
  x = all->wall->x / ((double)PRECI / texture->y);
  begin = (-pos_i / img->sizeline) * (pos_i < 0);
  pos_i = pos_i * (pos_i > 0) + pos_i % img->sizeline * (pos_i < 0);
  pos_t = (texture->sizeline * (int)((begin / (double)size) * texture->y));
  pos_t = pos_t + (x % texture->x * (texture->bpp / 8));
  while (begin < size && (pos_i / img->sizeline) <= SIZE_Y)
    {
      i = 0;
      if ((pos_t / texture->sizeline) < texture->y)
	while (i < (img->bpp / 8))
	  img->data[pos_i + i] = texture->data[pos_t + i++];
      pos_i = pos_i + img->sizeline;
      begin = begin + 1;
      pos_t = texture->sizeline * (int)(begin / (double)size * texture->y);
      pos_t = pos_t + (x % texture->x * (texture->bpp / 8));
    }
}
