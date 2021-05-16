/*
** fdf.c for fdf in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 19:48:39 2012 arnaud drain
** Last update Sat Jan 12 15:00:41 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <X11/X.h>
#include "header.h"

void		end(t_all *all)
{
  exit(0);
}

int		find_option()
{
  char		*s;
  int		option;

  my_putstr("--Wolf3D--\n");
  my_putstr("Choose option (game by default)\n");
  my_putstr("1 : Game\n");
  my_putstr("2 : Map perso\n");
  my_putstr("3 : Map editor\n");
  if ((s = get_next_line(0)) == NULL)
    return (my_putstr("Error in alloc\n"));
  option = 1;
  if (s[0] == '2')
    option = 2;
  if (s[0] == '3')
    option = 3;
  free(s);
  return (option);
}

char		*get_map()
{
  char		*s;

  my_putstr("Enter map name :\n");
  if ((s = get_next_line(0)) == NULL)
    return (NULL);
  return (s);
}

int		main(int argc, char **argv)
{
  int		option;
  char		*path;

  option = (find_option());
  if (option == 1)
    return (game(NULL));
  if (option == 2)
    {
      if ((path = get_map()) == NULL)
	return (my_putstr("Wrong map name\n"));
      return (game(path));
    }
  if (option == 3)
    return (map());
  return (0);
}
