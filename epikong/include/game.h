#ifndef GAME_H_
# define GAME_H_

# define SPRITE_SIZE (16)

#include <SDL/SDL.h>
#include "map.h"

int	launch_game(int next);
void	game(char *background, SDL_Surface *screen, t_map *map);
void	loose();

#endif /* !GAME_H_ */
