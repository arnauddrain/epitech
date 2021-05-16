#include "key.h"

void		key_enter(int *stop, t_player *player, t_map *map)
{
  (void)stop;
  if (map->map[player->y][player->x] == 'k')
    {
      player->key = 1;
      map->map[player->y][player->x] = '.';
    }
  if (map->map[player->y][player->x] == 'l')
    {
      if (player->life <= 5)
	++(player->life);
      map->map[player->y][player->x] = '.';
    }
}
