#ifndef MAP_H_
# define MAP_H_

# define MAX_X (640)
# define MAX_Y (480)

#include <SDL/SDL.h>

typedef struct	s_map
{
  char		**map;
  size_t	x;
  size_t	y;
}		t_map;

typedef struct	s_player
{
  size_t	x;
  size_t	y;
  int		falling;
  int		key;
  int		jump;
  int		life;
  char		*file;
}		t_player;

typedef struct	s_background
{
  char		*file;
  char		*background;
}		t_background;

typedef struct	s_blockmap
{
  char		c;
  const char	*file;
}		t_blockmap;

typedef struct	s_mfile
{
  t_map		*map;
  FILE		*fp;
  char		*line;
  size_t	len;
  ssize_t	read;
}		t_mfile;

void	create_map(SDL_Surface *screen, t_map *map, t_player *player);
t_map	*get_map(char *mapfile);
int	get_diff(int pos, int max, int map);

#endif /* !MAP_H_ */
