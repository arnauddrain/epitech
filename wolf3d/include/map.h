/*
** map.h for map in /home/drain_a//tps/i_graph/wolf3d/v7
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Thu Jan 10 18:32:57 2013 arnaud drain
** Last update Fri Jan 11 22:19:23 2013 arnaud drain
*/

#ifndef MAP_H_
# define MAP_H_

#define	SIZE_X	(800)
#define	SIZE_Y	(800)
#define	ESCAPE	(65307)
#define	ENTER	(65293)

typedef struct	s_coord
{
  int		x;
  int		y;
}		t_coord;

typedef struct	s_info
{
  void		*img_ptr;
  void		*mlx_ptr;
  void		*win_ptr;
}		t_info;

typedef struct	s_all
{
  int		**map;
  char		*path;
  t_coord	*size;
  t_info	*info;
}		t_all;

char		*get_next_line(int fd);
char		*get_map_name();
t_coord		*get_size();
int		**create_map(t_coord *size);

#endif /* !MAP_H_ */
