#include <SDL/SDL.h>
#include "game.h"
#include "menu.h"
#include "map.h"

void			create_screen(SDL_Surface *screen, char *backgroundFile)
{
  SDL_Surface		*background;
  SDL_Rect		pos;

  pos.x = 0;
  pos.y = 0;
  background = SDL_LoadBMP(backgroundFile);
  SDL_BlitSurface(background, NULL, screen, &pos);
  SDL_FreeSurface(background);
}

static int	init_sdl()
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    return (fprintf(stderr, "Erreur lors de l'initialisation de la SDL : %s\n",
		    SDL_GetError()));
  SDL_WM_SetIcon(SDL_LoadBMP("img/samus.bmp"), NULL);
  SDL_WM_SetCaption("EpiKong", NULL);
  SDL_EnableKeyRepeat(75, 75);
  return (0);
}

SDL_Surface	*resize_sdl(t_map *map)
{
  SDL_Surface	*screen;
  int		x;
  int		y;

  y = (map->y * SPRITE_SIZE <= MAX_Y) ? (map->y * SPRITE_SIZE) : MAX_Y;
  x = (map->x * SPRITE_SIZE <= MAX_X) ? (map->x * SPRITE_SIZE) : MAX_X;
  if (!(screen = SDL_SetVideoMode(x, y, 32, SDL_HWSURFACE)))
    {
      fprintf(stderr, "Erreur lors du chargement du mode vidéo : %s\n",
	     SDL_GetError());
      return (NULL);
    }
  return (screen);
}

int			sdl_launch()
{
  if (init_sdl())
    return (-1);
  launch_game(0);
  SDL_Quit();
  return (0);
}
