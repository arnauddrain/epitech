/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sun Dec  9 22:46:01 2012 arnaud drain
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include "header.h"

int		calc_pos(int x, int y, int z, t_vars *vars)
{
  int		res;

  if (z <= 0)
    {
      res = z + vars->const1 / 2 * vars->scale * x / 100;
      res = res + vars->const2 / 2 * vars->scale * y / 100 + vars->up;
    }
  else
    {
      res = vars->const1 * x * vars->scale / 100;
      res = res - vars->const2 * y * vars->scale / 100 + vars->left;
    }
  return (res);
}

int		find_coord(t_coord **pos1, t_coord **pos2, int **tab, t_vars *vars)
{
  int		x;
  int		y;
  int		z;
  int		color;

  color = mlx_get_color_value(vars->info->mlx_ptr, 0x0000ff);
  if ((*pos1 = malloc(sizeof(t_coord))) == NULL)
    return (1);
  if ((*pos2 = malloc(sizeof(t_coord))) == NULL)
    return (1);
  x = vars->x;
  y = vars->y;
  z = -tab[y][x];
  pos1[0]->y = calc_pos(x, y, z, vars);
  pos1[0]->x = calc_pos(x, y, 1, vars);
  pos2[0]->x = calc_pos(x, y + 1, 1, vars);
  if (tab[y + 1] != NULL)
    {
      z = -tab[y + 1][x];
      pos2[0]->y = calc_pos(x, y + 1, z, vars);
      my_line_put_to_image(*pos1, *pos2, vars->info->img_ptr, color);
    }
  return (0);
}

void		find_coord2(t_coord *pos1, t_coord *pos2, int **tab, t_vars *vars)
{
  int		x;
  int		y;
  int		z;
  int		color;

  color = mlx_get_color_value(vars->info->mlx_ptr, 0x0000ff);
  x = vars->x;
  y = vars->y;
  z = -tab[y][x + 1];
  if (z <= 0)
    pos2->y = calc_pos(x + 1, y, z, vars);
  pos2->x = calc_pos(x + 1, y, 1, vars);
  if (tab[y][x + 1] >= 0)
    my_line_put_to_image(pos1, pos2, vars->info->img_ptr, color);
}

int		draw_graph(int **tab, t_vars *vars)
{
  t_coord	*pos1;
  t_coord	*pos2;
  int		x;
  int		y;

  x = vars->x;
  y = vars->y;
  if (find_coord(&pos1, &pos2, tab, vars) == 1)
    return (1);
  find_coord2(pos1, pos2, tab, vars);
  vars->y = y + 1;
  if (tab[y + 1] != NULL)
    draw_graph(tab, vars);
  else
    {
      vars->y = 0;
      vars->x = x + 1;
      if (tab[0][x + 1] >= 0)
	draw_graph(tab, vars);
    }
  free(pos1);
  free(pos2);
  return (0);
}
