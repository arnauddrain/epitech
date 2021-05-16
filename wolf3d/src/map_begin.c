/*
** map.c for map in /home/drain_a//tps/i_graph/wolf3d/v7
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Jan 10 18:24:22 2013 arnaud drain
** Last update Fri Jan 11 22:39:31 2013 arnaud drain
*/

#include <mlx.h>
#include <stdlib.h>
#include "map.h"

int	match(char *s1, char *s2)
{
  if (*s1 == '\0' && (*s2 == '\0' || s2[*s2 == '*'] == '\0'))
    return (1);
  if (*s1 == s2[(*s2 == '*')])
    return match(s1 + 1, s2 + 1 + (*s2 == '*'));
  if (*s2 == '*' && *s1!= '\0')
    return match(s1 + (s2[1] != '*'), s2 + (s2[1] == '*'));
  return (0);
}

char	*add_extension(char *str, char *extension)
{
  char	*ret;
  int	i;
  int	a;

  ret = malloc(sizeof(char) * (my_strlen(str) + my_strlen(extension) + 1));
  if (ret == NULL)
    return (NULL);
  i = 0;
  while (i < my_strlen(str))
    ret[i] = str[i++];
  a = i;
  while ((i - a) < my_strlen(extension))
    ret[i] = extension[i++ - a];
  ret[i] = 0;
  return (ret);
}

char	*get_map_name()
{
  char	*path;
  char	*s;

  path = NULL;
  my_putstr("Please enter map name\n");
  while (path == NULL)
    {
      if ((s = get_next_line(0)) == NULL)
	return (NULL);
      if (match(s, "lvl*"))
        my_putstr("File cannot begin with \"lvl\"\n");
      else
        if ((path = add_extension(s, ".map")) == NULL)
	  return (NULL);
      free(s);
    }
  return (path);
}

t_coord		*get_size()
{
  char		*s;
  t_coord	*size;

  if ((size = malloc(sizeof(*size))) == NULL)
    return (NULL);
  my_putstr("width = ");
  if ((s = get_next_line(0)) == NULL)
    return (NULL);
  size->x = my_get_nbr(s);
  size->x = size->x * (size->x >= 3) + 3 * (size->x < 3);
  size->x = size->x % 100;
  free(s);
  my_putstr("height = ");
  if ((s = get_next_line(0)) == NULL)
    return (NULL);
  size->y = my_get_nbr(s);
  size->y = size->y * (size->y >= 3) + 3 * (size->y < 3);
  size->y = size->y % 100;
  free(s);
  return (size);
}
