/*
** lib.c for lib in /home/drain_a//tps/i_graph/fdf
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Nov 22 20:03:04 2012 arnaud drain
** Last update Fri Dec  7 12:42:21 2012 arnaud drain
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

int	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i] != 0)
    {
      my_putchar(str[i]);
      i = i + 1;
    }
  return (1);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != 0)
    i = i + 1;
  return (i);
}

void	my_put_nbr(int nb)
{
  if (nb < 0)
    {
      my_putchar('-');
      nb = -nb;
    }
  if (nb > 9)
    my_put_nbr(nb / 10);
  my_putchar(nb % 10 + '0');
}

int	my_get_nbr(char *str)
{
  int	i;
  int	mult;
  int	ret;

  ret = 0;
  mult = 1;
  i = 0;
  while (str[i] == '-' || str[i] == '+')
    i = i + 1;
  while (str[i] >= '0' && str[i] <= '9')
    i = i + 1;
  while (i > 0)
    {
      i = i - 1;
      if (str[i] == '-')
	ret = ret * -1;
      if (str[i] >= '0' || str[i] <= '9')
	ret = ret + (str[i] - '0') * mult;
      mult = mult * 10;
    }
  return (ret);
}
