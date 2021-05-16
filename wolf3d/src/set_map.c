/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sat Jan 12 08:55:22 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <X11/X.h>
#include "header.h"

int		calc_map(int fd, int **ret, int size_y, int size_x)
{
  int		x;
  int		y;
  int		i;
  char		*s;

  y = 0;
  while (y < size_y)
    {
      x = 0;
      i = 0;
      s = get_next_line(fd);
      while (x < size_x)
	{
	  if (i >= my_strlen(s))
	    return (-1);
	  ret[y][x++] = my_get_nbr(s + i);
	  while (s[i] != ' ' && s[i] != '	')
	    i = i + 1;
	  while (s[i] == ' ' || s[i] == '	')
	    i = i + 1;
	}
      free(s);
      y = y + 1;
    }
  return (0);
}

int		**set_map(int fd, t_lvl *lvl)
{
  int		**ret;
  char		*s;
  int		y;

  if ((s = get_next_line(fd)) == NULL)
    return (NULL);
  lvl->max->y = my_get_nbr(s);
  free(s);
  if ((s = get_next_line(fd)) == NULL)
    return (NULL);
  lvl->max->x = my_get_nbr(s);
  free(s);
  if ((ret = malloc(sizeof(int *) * lvl->max->y)) == NULL)
    return (NULL);
  y = 0;
  while (y < lvl->max->y)
    {
      if ((ret[y] = malloc(sizeof(int *) * lvl->max->x)) == NULL)
	return (NULL);
      y = y + 1;
    }
  if ((calc_map(fd, ret, lvl->max->y, lvl->max->x)) == -1)
    return (NULL);
  return (ret);
}
