/*
** gere_map.c for gere_map in /home/drain_a//tps/i_graph/wolf3d/v7
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Fri Jan 11 12:23:01 2013 arnaud drain
** Last update Fri Jan 11 23:10:26 2013 arnaud drain
*/

#include <stdlib.h>
#include <mlx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "map.h"

int             my_put_pixel_to_image(int x, int y, t_info *info, int col)
{
  char          *data;
  char          *color;
  int           bpp;
  int           sizeline;
  int           endian;
  int           pos;
  int           i;

  col = mlx_get_color_value(info->mlx_ptr, col);
  color = &col;
  data = mlx_get_data_addr(info->img_ptr, &bpp, &sizeline, &endian);
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

char		*create_text(char *str, t_coord *size, int **map, int i)
{
  int		x;
  int		y;

  if (size->y > 9)
    str[i++] = size->y / 10 + '0';
  str[i++] = size->y % 10 + '0';
  str[i++] = '\n';
  if (size->x > 9)
    str[i++] = size->x / 10 + '0';
  str[i++] = size->x % 10 + '0';
  str[i++] = '\n';
  y = 0;
  while (y < size->y)
    {
      x = 0;
      while (x < size->x)
	{
	  str[i++] = map[y][x++] + '0';
	  if (x < size->x)
	    str[i++] = ' ';
	}
      if (++y < size->y)
	str[i++] = '\n';
    }
  str[i] = 0;
}

void		create_file(t_all *all)
{
  int		fd;
  mode_t	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  char		*str;
  int		size;

  if ((fd = open(all->path, O_WRONLY | O_CREAT | O_TRUNC, mode)) == -1)
    exit(my_putstr("Error in file create\n"));
  size = 5 + (all->size->x > 9) + (all->size->y > 9);
  size = size + 2 * all->size->x * all->size->y;
  if ((str = malloc(sizeof(char) * size)) == NULL)
    exit(my_putstr("error in alloc\n"));
  create_text(str, all->size, all->map, 0);
  if (write(fd, str, my_strlen(str)) == -1)
    my_putstr("Error while writing in file\n");
  exit (0);
}

void	set_img(t_all *all)
{
  int	y;
  int	x;
  int	divy;
  int	divx;

  divx = (double)SIZE_X / all->size->x * 1000;
  divy = (double)SIZE_Y / all->size->y * 1000;
  y = 0;
  while (y < SIZE_Y)
    {
      x = 0;
      while (x < SIZE_X)
	{
	  if (x % (divx / 1000) == 0 || y % (divy / 1000) == 0)
	    my_put_pixel_to_image(x, y, all->info, 0x000000);
	  else if (all->map[1000 * y / divy][1000 * x / divx] == 0)
	    my_put_pixel_to_image(x, y, all->info, 0xffffff);
	  else
	    my_put_pixel_to_image(x, y, all->info, 0xaaaaaa);
	  x = x + 1;
	}
      y = y + 1;
    }
}

int	**create_map(t_coord *size)
{
  int	**map;
  int	y;
  int	x;

  if ((map = malloc(sizeof(*map) * size->y)) == NULL)
    return (NULL);
  y = 0;
  while (y < size->y)
    {
      if ((map[y] = malloc(sizeof(**map) * size->x)) == NULL)
	return (NULL);
      x = 0;
      while (x < size->x)
	{
	  map[y][x] = 0;
	  if (x == 0 || x == (size->x - 1) || y == 0 || y == (size->y - 1))
	    map[y][x] = 1;
	  ++x;
	}
      ++y;
    }
  return (map);
}
