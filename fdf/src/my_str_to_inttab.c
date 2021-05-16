/*
** my_str_to_wordtab.c for my_str_to_wordtab in /exam//rendu/ex_5
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Sat Nov 10 12:32:57 2012 arnaud drain
** Last update Sun Dec  9 22:45:03 2012 arnaud drain
*/

#include <stdlib.h>
#include "header.h"

int	espaces(char *str)
{
  int	i;

  i = 0;
  while (str[i] == ' ' || str[i] == '	')
    i = i + 1;
  return (i);
}

int	nb_int(char *str)
{
  int	i;
  int	nb;

  nb = 1;
  i = espaces(str);
  while (str[i] != '\0' && str[i] != ' ' && str[i] != '	')
    {
      i = i + 1;
      if (str[i] == ' ' || str[i] == '	')
	{
	  i = i + espaces(str + i);
	  if (str[i] != '\0')
	    nb = nb + 1;
	}
    }
  return (nb);
}

int	*my_str_to_inttab(char *str, int mult)
{
  int	*ret;
  int  	tab;
  int	i;
  int	a;

  tab = 0;
  if ((ret = malloc(sizeof(int) * (nb_int(str) / mult + 1))) == NULL)
    return (NULL);
  i = espaces(str);
  while (str[i] != '\0' && str[i] != ' ' && str[i] != '	')
    {
      a = 0;
      ret[tab] = my_get_nbr(str + i);
      while (a < mult)
	{
	  while (str[i] != ' ' && str[i] != '	' && str[i] != '\0')
	    i = i + 1;
	  i = i + espaces(str + i);
	  a = a + 1;
	}
      tab = tab + 1;
    }
  ret[tab] = -1;
  return (ret);
}

int	**create_tmp(int **tab, int cas)
{
  int	**tmp;
  int	i;

  i = 0;
  if ((tmp = malloc(sizeof(int *) * (cas + 2))) == NULL)
    return (NULL);
  while (i < cas)
    {
      tmp[i] = tab[i];
      i = i + 1;
    }
  free(tab);
  tab = tmp;
  return (tab);
}

int	**create_table(int fd)
{
  int	**tab;
  char	*s;
  int	cas;
  int	mult;

  cas = 0;
  if ((tab = malloc(sizeof(int *))) == NULL)
    return (NULL);
  while ((s = get_next_line(fd)))
    {
      if ((mult = arrondi(s)) != 0)
	{
	  if ((tab = create_tmp(tab, cas)) == NULL)
	    return (NULL);
	  if ((tab[cas] = my_str_to_inttab(s, mult)) == NULL)
	    return (NULL);
	  cas = cas + 1;
	}
      free(s);
    }
  free(s);
  tab[cas] = NULL;
  return (tab);
}
