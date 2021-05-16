/*
** get_next_line.c for get_next_line in /home/drain_a//rendu_local/get_next_line/v2
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Mon Dec 10 17:25:45 2012 arnaud drain
** Last update Thu Dec 13 12:11:03 2012 arnaud drain
*/

#include <stdlib.h>
#include "header.h"

char		*add_str_to_str(char *ret, char *buffer, int *pos, int size)
{
  char		*str;
  int		i;
  int		a;

  if (size == 0)
    return (ret);
  i = my_strlen(ret) + my_strlen(buffer + *pos) + 1;
  if ((str = malloc(sizeof(char) * i)) == NULL)
    return (NULL);
  i = 0;
  while (ret[i] != 0)
    {
      str[i] = ret[i];
      i = i + 1;
    }
  a = i;
  while (buffer[i - a + *pos] != 0)
    {
      str[i] = buffer[i - a + *pos];
      i = i + 1;
    }
  str[i] = 0;
  *pos = (i - a + 1 + *pos) * ((i - a + 1 + *pos) < size);
  free(ret);
  return (str);
}

int		find_end(char *str, int size, int *pos)
{
  int		i;

  i = *pos;
  if (i == size)
    return (1);
  while (str[i] != 0 && str[i] != '\n')
    {
      i = i + 1;
      if (i == size)
	return (1);
    }
  str[i] = 0;
  return (0);
}

char		*get_next_line2(int fd, char *ret, int *pos, char **buffer)
{
  static int	size;

  if (*buffer == NULL)
    {
      if ((*buffer = malloc(sizeof(char) * (READ + 1))) == NULL)
	return (NULL);
      if ((size = read(fd, *buffer, READ)) <= 0)
	return (NULL);
      *pos = 0;
      buffer[0][size] = 0;
    }
  while (find_end(*buffer, size, pos) && size > 0)
    {
      if ((ret = add_str_to_str(ret, *buffer, pos, size)) == NULL)
	return (NULL);
      if ((size = read(fd, *buffer, READ)) == -1)
        return (NULL);
      buffer[0][size] = 0;
    }
  if ((ret = add_str_to_str(ret, *buffer, pos, size)) == NULL)
    return (NULL);
  return (ret);
}

char		*get_next_line(int fd)
{
  char		*ret;
  static int	pos;
  static char	*buffer;

  if (READ <= 0)
    {
      my_putstr("Vilains Asteks !\n");
      return (NULL);
    }
  if ((ret = malloc(sizeof(char))) == NULL)
    return (NULL);
  *ret = 0;
  ret = get_next_line2(fd, ret, &pos, &buffer);
  if (pos == 0)
    {
      free(buffer);
      buffer = NULL;
    }
  return (ret);
}
