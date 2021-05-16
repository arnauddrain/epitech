#ifndef MONSTERS_H_
# define MONSTERS_H_

# define		LEFT	(0)
# define		RIGHT	(1)
# define		MONSTER ('m')

#include "map.h"

typedef struct		s_monsters
{
  int			posX;
  int			posY;
  int			dir;
  char			*file;
  struct s_monsters	*next;
}			t_monsters;

void			monstersMove(t_map *map, t_monsters *list);
void			aff_monsters(t_map *map, t_monsters *list, t_player *player,
				     SDL_Surface *screen);
t_monsters		*monstersList_init(t_map *map);

void		collision(SDL_Surface *screen, t_monsters *list, t_player *player);

#endif /* !MONSTERS_H_ */
