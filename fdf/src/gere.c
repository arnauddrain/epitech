/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sun Dec  9 22:44:56 2012 arnaud drain
*/

#include <stdlib.h>
#include <mlx.h>
#include "header.h"

int		arrondi(char *str)
{
  static int	i;
  static int	mult;

  if (mult == 0)
    mult = nb_int(str) / 200 + 1;
  i = i + 1;
  if (i % mult == 0)
    return (mult);
  return (0);
}

char		*add_str_to_str(char *ret, char *buffer)
{
  char		*tmp;
  int		size;
  int		pos1;
  int		pos2;

  size = my_strlen(ret) + my_strlen(buffer) + 1;
  if ((tmp = malloc(sizeof(char) * size)) == NULL)
    return (NULL);
  pos1 = 0;
  while (ret[pos1] != 0)
    {
      tmp[pos1] = ret[pos1];
      pos1 = pos1 + 1;
    }
  pos2 = 0;
  while (buffer[pos2] != 0)
    {
      tmp[pos1] = buffer[pos2];
      pos1 = pos1 + 1;
      pos2 = pos2 + 1;
    }
  tmp[pos1] = 0;
  free(ret);
  return (tmp);
}

void		gere_key2(int keycode, t_vars *vars)
{
  if (keycode == 65363 && vars->const1 < 100)
    {
      vars->const1 = vars->const1 + 1;
      vars->const2 = vars->const2 - 1;
    }
  if (keycode == 65361 && vars->const1 > 50)
    {
      vars->const1 = vars->const1 - 1;
      vars->const2 = vars->const2 + 1;
    }
  if (keycode == 32)
    set_vars(vars, vars->tab);
}

int		gere_key(int keycode, t_vars *vars)
{
  t_info	*info;

  info = vars->info;
  vars->up = vars->up + 10 * (keycode == 115) - 10 * (keycode == 122);
  vars->left = vars->left + 10 * (keycode == 100) - 10 * (keycode == 113);
  if (keycode == 65362)
    vars->scale = vars->scale + 2;
  if (keycode == 65364 && vars->scale > 3)
    vars->scale = vars->scale - 2;
  gere_key2(keycode, vars);
  vars->x = 0;
  vars->y = 0;
  free(info->img_ptr);
  info->img_ptr = mlx_new_image(info->mlx_ptr, SIZE_X, SIZE_Y);
  if (draw_graph(vars->tab, vars) == 1)
    return (1);
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
  if (keycode == 65307)
    {
      mlx_destroy_window(info->mlx_ptr, info->win_ptr);
      free(vars->info);
      exit(0);
    }
}

int		gere_expose(t_info *info)
{
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
}
