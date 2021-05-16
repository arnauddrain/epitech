#include <SDL/SDL.h>
#include "sdl.h"
#include "game.h"

void		loose()
{
  SDL_Surface	*screen;
  int		exit;
  SDL_Event	event;

  if (!(screen = SDL_SetVideoMode(581, 621, 32, SDL_HWSURFACE)))
    return;
  create_screen(screen, "img/gameover.bmp");
  SDL_Flip(screen);
  SDL_Delay(1000);
  exit = 0;
  while (!exit)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT)
	exit = 1;
    }
  SDL_FreeSurface(screen);
  launch_game(0);
}
