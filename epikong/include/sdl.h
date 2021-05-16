#ifndef SDL_H_
# define SDL_H_

#include <SDL/SDL.h>
#include "event.h"

void		create_screen(SDL_Surface *screen, char *backgroundFile);
SDL_Surface	*resize_sdl(t_map *map);
int		sdl_launch();

#endif /* !SDL_H_ */
