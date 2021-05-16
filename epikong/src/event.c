#include "player.h"
#include "event.h"
#include "key.h"

static t_event g_event[] =
  {
    {SDLK_ESCAPE, &key_escape},
    {SDLK_UP, &key_move_up},
    {SDLK_DOWN, &key_move_down},
    {SDLK_RIGHT, &key_move_right},
    {SDLK_LEFT, &key_move_left},
    {SDLK_SPACE, &key_space},
    {SDLK_KP_ENTER, &key_enter},
    {13, &key_enter},
    {0, NULL}
  };

static void	keyboard_event(int event, int *stop,
			       t_player *player, t_map *map)
{
  int		i;

  i = 0;
  while (g_event[i].function)
    {
      if (g_event[i].event == event)
	g_event[i].function(stop, player, map);
      ++i;
    }
}

void		manage_event(int *stop, t_player *player, t_map *map)
{
  SDL_Event	event;

  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT)
    *stop = 1;
  else if (event.type == SDL_KEYDOWN)
    keyboard_event(event.key.keysym.sym, stop, player, map);
}
