/*
** get_next_line.c for get_next_line in /home/drain_a//rendu_local/rush/rush1/racine/de/mon/super/repo/svn/etape_2
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Sat Dec  1 13:52:42 2012 arnaud drain
** Last update Fri Dec  7 12:39:58 2012 arnaud drain
*/

#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int		find_end(char *str, int *begin, int size)
{
  int		i;

  i = *begin;
  if (i >= size)
    return (0);
  while (str[i] != '\n' && str[i] != '\0')
    {
      i = i + 1;
      if (i >= size)
	return (0);
    }
  *begin = i + (str[i] != '\0');
  str[i] = 0;
  return (1);
}

void		butterfly(char **buffer, int pos, int size)
{
  if (pos >= size)
    {
      free(*buffer);
      *buffer = NULL;
    }
}

int		buffer_null(int fd, char **buffer, int *size, int pos)
{
  if (*buffer == NULL)
    {
      if ((*buffer = malloc(sizeof(char) * (READ + 1))) == NULL)
	return (-1);
      if ((*size = read(fd, *buffer, READ)) <= 0)
	return (-1);
      buffer[0][*size] = 0;
      return (0);
    }
  return (pos);
}

void		fuck(char *ret, int *pos_tmp, int *pos)
{
  ret[0] = 0;
  *pos_tmp = *pos;
}

char		*get_next_line(int fd)
{
  static char	*buffer;
  static int	pos;
  static int	size;
  char		*ret;
  int		pos_tmp;

  if ((pos = buffer_null(fd, &buffer, &size, pos)) == -1)
    return (NULL);
  if ((ret = malloc(sizeof(char))) == NULL)
    return (NULL);
  fuck(ret, &pos_tmp, &pos);
  while (find_end(buffer, &pos, size) == 0)
    {
      if ((ret = add_str_to_str(ret, buffer + pos_tmp)) == NULL)
	return (NULL);
      pos = 0;
      pos_tmp = 0;
      if ((size = read(fd, buffer, READ)) <= 0)
	return (NULL);
      buffer[size] = 0;
    }
  if ((ret = add_str_to_str(ret, buffer + pos_tmp)) == NULL)
    return (NULL);
  butterfly(&buffer, pos, size);
  return (ret);
}
