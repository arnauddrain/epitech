#ifndef PLAYER_H_
# define PLAYER_H_

# define JUMP_LEFT	(1)
# define JUMP_RIGHT	(2)
# define JUMP_UP	(3)

#include <stdlib.h>
#include <SDL/SDL.h>
#include "map.h"

void		find_player(char **map, t_player *player);
void		aff_player(t_map *map, t_player *player, SDL_Surface *screen);
void		gravity(t_map *map, t_player *player);

#endif /* !PLAYER_H_ */
