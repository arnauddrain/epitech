/*
** lvl.c for lvl in /home/drain_a//tps/i_graph/wolf3d/v4
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Tue Jan  8 06:11:50 2013 arnaud drain
** Last update Sat Jan 12 15:37:20 2013 arnaud drain
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "header.h"
#include "lvl.h"

void		lvl_up(t_all *all)
{
  if (all->lvl->lvl == 0)
    {
      my_putstr("Vous avez gagné ! C'est trop youpi-chouette bravo :)\n");
      end(all);
    }
  all->map = all->lvl->map;
  all->max = all->lvl->max;
  all->texts = all->lvl->texts;
  all->pos = all->lvl->pos;
  all->lvl->lvl = all->lvl->lvl - 1;
  all->lvl = all->lvl->next;
}

t_texts		*set_texts(t_info *info, int i)
{
  t_texts	*texts;
  char		*path;

  if ((texts = malloc(sizeof(*texts))) == NULL)
    return (NULL);
  path = g_lvl[i].secret;
  if ((texts->secret = textures(info, path)) == NULL)
    return (NULL);
  path = g_lvl[i].wall;
  if ((texts->wall = textures(info, path)) == NULL)
    return (NULL);
  path = g_lvl[i].end;
  if ((texts->end = textures(info, path)) == NULL)
    return (NULL);
  if ((texts->hands = textures(info, "img/hands.xpm")) == NULL)
    return (NULL);
  return (texts);
}

void		circulaire(t_all *all)
{
  t_lvl		*lvl;

  lvl = all->lvl;
  while (lvl->next != NULL)
    lvl = lvl->next;
  lvl->next = all->lvl;
}

int		set_lvl2(int i, t_lvl *lvl, t_all *all)
{
  if ((lvl->pos = malloc(sizeof(t_pos))) == NULL)
    return (my_putstr("error in alloc\n"));
  if (all->mode == NULL)
    {
      lvl->pos->x = g_lvl[i - 1].posx;
      lvl->pos->y = g_lvl[i - 1].posy;
      lvl->pos->alpha = ((1000 * g_lvl[i - 1].alpha) / 180) * M_PI;
    }
  else
    {
      lvl->pos->x = 1.5 * PRECI;
      lvl->pos->y = 1.5 * PRECI;
      lvl->pos->alpha = ((1000 * 45) / 180) * M_PI;
    }
  lvl->lvl = i;
  lvl->next = NULL;
  if (i < LVL && all->mode == NULL)
    if ((lvl->next = set_lvl(all, i + 1)) == NULL)
      return (1);
  return (0);
}

t_lvl		*set_lvl(t_all *all, int i)
{
  t_lvl		*lvl;
  char		*map_name;
  int		fd;

  if ((lvl = malloc(sizeof(t_lvl))) == NULL)
    return (my_puterror("Error in lvl load\n"));
  if (all->mode == NULL)
    map_name = g_lvl[i - 1].map;
  else
    map_name = all->mode;
  if ((fd = open(map_name, O_RDONLY)) == -1)
    return (my_puterror("error in open\n"));
  if ((lvl->max = malloc(sizeof(t_coord))) == NULL)
    return (my_puterror("error in alloc\n"));
  if ((lvl->map = set_map(fd, lvl)) == NULL)
    return (my_puterror("error in map load\n"));
  if ((lvl->texts = set_texts(all->info, i - 1)) == NULL)
    return (my_puterror("error in texture load\n"));
  if (set_lvl2(i, lvl, all) != 0)
    return (NULL);
  return (lvl);
}
