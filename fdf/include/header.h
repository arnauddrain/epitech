/*
** get_next_line.h for get_next_line in /home/drain_a//rendu_local/get_next_line
** 
** Made by arnaud drain
** Login   <drain_a@epitech.net>
** 
** Started on  Fri Nov 16 17:14:39 2012 arnaud drain
** Last update Sun Dec  9 20:22:10 2012 arnaud drain
*/

#ifndef HEADER_H_
# define HEADER_H_

#define READ	(5000)
#define	SIZE_X	(1000)
#define	SIZE_Y	(1000)

typedef struct	s_coord
{
  int		x;
  int		y;
}		t_coord;

typedef struct	s_info
{
  void		*mlx_ptr;
  void		*win_ptr;
  void		*img_ptr;
}		t_info;

typedef struct	s_vars
{
  int		scale;
  int		x;
  int		y;
  int		up;
  int		left;
  int		const1;
  int		const2;
  t_info	*info;
  int		**tab;
}		t_vars;

char	*get_next_line(int fd);
int		**create_table(int fd);
int		gere_key(int keycode, t_vars *vars);
int		gere_expose(t_info *info);
char	*add_str_to_str(char *ret, char *buffer);

/*
** Added during refacto for MacOS (post-Epitech)
*/
int   draw_graph(int **tab, t_vars *vars);
int   my_putstr(char *str);
int   nb_int(char *str);
int	  my_strlen(char *str);
void	set_vars(t_vars *vars, int **tab);
void	my_line_put_to_image(t_coord *pos1, t_coord *pos2, void *img, int col);
int 	my_get_nbr(char *str);
int		arrondi(char *str);

#endif /* !HEADER_H_ */
