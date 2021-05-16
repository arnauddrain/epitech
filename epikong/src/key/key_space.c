#include "key.h"
#include "event.h"
#include "player.h"

void		key_space(int *stop, t_player *player, t_map *map)
{
  Uint8		*keystate;

  (void)stop;
  if (map->map[player->y][player->x] != 's' &&
      (map->map[player->y + 1][player->x] == 's' ||
       map->map[player->y + 1][player->x] == 'w'))
    {
      if (map->map[player->y - 1][player->x] != 'w')
	--(player->y);
      keystate = SDL_GetKeyState(NULL);
      if (keystate[SDLK_RIGHT])
	{
	  if (map->map[player->y][player->x + 1] != 'w')
	    ++(player->x);
	  player->jump = -JUMP_RIGHT;
	}
      else if (keystate[SDLK_LEFT])
	{
	  if (map->map[player->y][player->x - 1] != 'w')
	    --(player->x);
	  player->jump = -JUMP_LEFT;
	}
      else
	player->jump = -JUMP_UP;
    }
}
