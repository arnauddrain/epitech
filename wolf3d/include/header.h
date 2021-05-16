/*
** get_next_line.h for get_next_line in /home/drain_a//rendu_local/get_next_line
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Fri Nov 16 17:14:39 2012 arnaud drain
** Last update Sat Jan 12 15:37:29 2013 arnaud drain
*/

#ifndef HEADER_H_
# define HEADER_H_

#define	SIZE_X	(800)
#define	SIZE_Y	(800)
#define	PRECI	(10000)
#define	READ	(4000)
#define	ESCAPE	(65307)
#define	LEFT	(65361)
#define	RIGHT	(65363)
#define	TAB	(65289)
#define	UP	(65362)
#define	DOWN	(65364)

typedef struct	s_coord
{
  int		x;
  int		y;
}		t_coord;

typedef struct	s_pos
{
  int		x;
  int		y;
  int		alpha;
}		t_pos;

typedef struct	s_wall
{
  int		dist;
  int		x;
  int		text;
  int		color;
}		t_wall;

typedef struct	s_xpm
{
  void		*img;
  int		x;
  int		y;
  char		*data;
  int		sizeline;
  int		bpp;
  int		endian;
}		t_xpm;

typedef struct	s_info
{
  void		*mlx_ptr;
  void		*win_ptr;
  t_xpm		*img;
}		t_info;

typedef struct	s_texts
{
  t_xpm		*secret;
  t_xpm		*wall;
  t_xpm		*end;
  t_xpm		*hands;
}		t_texts;

typedef struct	s_lvl
{
  int		lvl;
  int		**map;
  t_coord	*max;
  t_texts	*texts;
  t_pos		*pos;
  struct s_lvl	*next;
}		t_lvl;

typedef struct	s_all
{
  int		**map;
  t_lvl		*lvl;
  t_pos		*pos;
  t_coord	*max;
  t_info	*info;
  t_texts	*texts;
  t_wall	*wall;
  t_wall	*tmp;
  int		hands;
  char		*mode;
}		t_all;

void		*my_puterror(char *str);
int		gere_expose(t_info *info);
int		gere_key(int keycode, t_all *all);
void		my_putchar(char c);
int		my_putstr(char *str);
void		my_put_nbr(int nb);
char		*get_next_line(int fd);
void		trace_col(t_all *all, int x, t_texts *texts);
void		set_base(t_info *info);
void		calc_dist(t_all *all, t_coord *vect);
int		aff_map(t_all *all);
int		**set_map(int fd, t_lvl *lvl);
t_xpm		*textures(t_info *info, char *path);
t_lvl		*set_lvl(t_all *all, int i);
int		my_wait(int keycode, t_all *all);

#endif /* !HEADER_H_ */
