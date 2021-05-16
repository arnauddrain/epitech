/*
** lib.c for lib in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 20:03:04 2012 arnaud drain
** Last update Fri Jan 11 22:20:42 2013 arnaud drain
*/

#include <stdlib.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  if (str != NULL)
    while (str[i] != 0)
      i = i + 1;
  return (i);
}

int	my_putstr(char *str)
{
  if (str != NULL)
    write(1, str, my_strlen(str));
  return (1);
}

void	*my_puterror(char *str)
{
  int	i;

  i = 0;
  while (str[i] != 0)
    {
      my_putchar(str[i]);
      i = i + 1;
    }
  return (NULL);
}

int	my_get_nbr(char *str)
{
  int	i;
  int	res;
  int	mult;

  i = 0;
  res = 0;
  mult = 1;
  while (str[i] == '-' || str[i] == '+')
    i = i + 1;
  while (str[i] >= '0' && str[i] <= '9')
    i = i + 1;
  while (i > 0)
    {
      i = i - 1;
      if (str[i] == '-')
	res = -res;
      if (str[i] >= '0' && str[i] <= '9')
	res = res + (str[i] - '0') * mult;
      mult = mult * 10;
    }
  return (res);
}
