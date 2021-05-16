/*
** header.h for header in /home/drain_a//rendu_local/my_ls
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Tue Nov 27 15:48:37 2012 arnaud drain
** Last update Fri Jan 11 12:38:35 2013 arnaud drain
*/

#ifndef LVL_H_
# define LVL_H_

#define LVL	(3)

typedef struct	s_lvl_info
{
  char		*map;
  char		*secret;
  char		*wall;
  char		*end;
  int		posx;
  int		posy;
  int		alpha;
}		t_lvl_info;

t_lvl_info	g_lvl[LVL] =
  {
    {
      "maps/lvl1.map",
      "img/secret1.xpm",
      "img/wall1.xpm",
      "img/end.xpm",
      2.5 * PRECI, 2.5 * PRECI, 45
    },
    {
      "maps/lvl2.map",
      "img/secret2.xpm",
      "img/wall2.xpm",
      "img/end.xpm",
      4.5 * PRECI, 2.5 * PRECI, 135
    },
    {
      "maps/lvl3.map",
      "img/secret3.xpm",
      "img/wall3.xpm",
      "img/end.xpm",
      2.5 * PRECI, 2.5 * PRECI, 90
    }
  };

#endif /* !LVL_H_ */
