/*
** img1.c for tp in /home/drain_a//tps/i_graph/tp2
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 15 12:31:15 2012 arnaud drain
** Last update Sat Dec  8 11:38:33 2012 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include "header.h"

int		my_pixel_put_to_image(int x, int y, void *img_ptr, int col)
{
  char		*data;
  char		*color;
  int		bpp;
  int		sizeline;
  int		endian;
  int		pos;
  int		i;

  color = &col;
  data = mlx_get_data_addr(img_ptr, &bpp, &sizeline, &endian);
  if (x <= 0 || y <= 0 || x >= SIZE_X || y >= SIZE_Y)
    return (1);
  pos = (sizeline * y) + (x * (bpp / 8));
  i = 0;
  while (i < (bpp / 8))
    {
      data[pos + i] = color[i];
      i = i + 1;
    }
  return (0);
}

void		draw_cas_un(t_coord *pos1, t_coord *pos2, void *img, int col)
{
  int		x;
  int		y;
  t_coord	*tmp;

  if (pos1->x > pos2->x)
    {
      tmp = pos1;
      pos1 = pos2;
      pos2 = tmp;
    }
  x = pos1->x;
  while (x <= pos2->x)
    {
      y = pos1->y + (pos2->y - pos1->y) * (x - pos1->x) / (pos2->x - pos1->x);
      my_pixel_put_to_image(x, y, img, col);
      x = x + 1;
    }
}

void		draw_cas_deux(t_coord *pos1, t_coord *pos2, void *img, int col)
{
  int		x;
  int		y;
  t_coord	*tmp;

  if (pos1->y > pos2->y)
    {
      tmp = pos1;
      pos1 = pos2;
      pos2 = tmp;
    }
  y = pos1->y;
  while (y <= pos2->y)
    {
      x = pos1->x + (pos2->x - pos1->x) * (y - pos1->y) / (pos2->y - pos1->y);
      my_pixel_put_to_image(x, y, img, col);
      y = y + 1;
    }
}

void		my_line_put_to_image(t_coord *pos1, t_coord *pos2, void *img, int col)
{
  int		width;
  int		height;

  if (pos1->x > pos2->x)
    width = pos1->x - pos2->x;
  else
    width = pos2->x - pos1->x;
  if (pos1->y > pos2->y)
    height = pos1->y - pos2->y;
  else
    height = pos2->y - pos1->y;
  if (width > height)
    draw_cas_un(pos1, pos2, img, col);
  else
    draw_cas_deux(pos1, pos2, img, col);
}
