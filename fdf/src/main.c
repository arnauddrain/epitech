/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sun Dec  9 22:45:47 2012 arnaud drain
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include "header.h"

void		set_vars(t_vars *vars, int **tab)
{
  int		i;

  i = 0;
  while (tab[0][i] != -1)
    i = i + 1;
  vars->x = 0;
  vars->y = 0;
  vars->scale = 400 / i + 2;
  vars->up = 500 - vars->scale * i / 2;
  vars->left = 500;
  vars->tab = tab;
  vars->const1 = 75;
  vars->const2 = 75;
}

int		fdf(int **tab)
{
  t_vars	*vars;
  t_info	*info;

  if ((vars = malloc(sizeof(t_vars))) == NULL)
    return (1);
  set_vars(vars, tab);
  if ((info = malloc(sizeof(t_info))) == NULL)
    return (1);
  info->mlx_ptr = mlx_init();
  info->win_ptr = mlx_new_window(info->mlx_ptr, SIZE_X, SIZE_Y, "fdf");
  info->img_ptr = mlx_new_image(info->mlx_ptr, SIZE_X, SIZE_Y);
  vars->info = info;

  if (draw_graph(tab, vars) == 1)
    return (1);
  mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
  mlx_key_hook(info->win_ptr, gere_key, vars);
  mlx_expose_hook(info->win_ptr, &gere_expose, info);
  mlx_loop(info->mlx_ptr);
}

int		main(int argc, char **argv)
{
  int		fd;
  int		**tab;

  if (argc > 1)
    {
      fd = open(argv[1], O_RDONLY);
      if (fd < 0)
	my_putstr("Wrong file name\n");
      else
	{
	  if ((tab = create_table(fd)) == NULL)
	    return (my_putstr("Erroc on malloc"));
	  close(fd);
	  my_putstr("Use : move with zqsd and zoom and rotate with arrow.");
	  my_putstr(" Use space to reset\n");
	  if (fdf(tab) == 1)
	    {
	      perror(NULL);
	      return (1);
	    }
	}
    }
  else
    my_putstr("Please enter file name\n");
  return (0);
}
