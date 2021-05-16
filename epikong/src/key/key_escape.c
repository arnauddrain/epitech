#include "key.h"
#include "event.h"

void		key_escape(int *stop, t_player *player, t_map *map)
{
  (void)player;
  (void)map;
  *stop = 1;
}
