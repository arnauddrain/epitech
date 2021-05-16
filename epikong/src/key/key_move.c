#include "key.h"
#include "event.h"

static void	move_player(t_player *player, int new_x, int new_y, char **map)
{
  player->file = "img/player_left.bmp";
  if ((int)player->x < new_x)
    player->file = "img/player_right.bmp";
  else if (((int)player->y > new_y || (int)player->y < new_y) &&
	   map[new_y][new_x] == 's')
    player->file = "img/player_up.bmp";
  player->x = new_x;
  player->y = new_y;
}

void		key_move_up(int *stop, t_player *player, t_map *map)
{
  (void)stop;
  if (player->y > 0 && map->map[player->y - 1][player->x] != 'w' &&
      map->map[player->y][player->x] == 's')
    move_player(player, player->x, player->y - 1, map->map);
}

void		key_move_down(int *stop, t_player *player, t_map *map)
{
  (void)stop;
  if ((player->y + 1) < (map->y) && map->map[player->y + 1][player->x] == 's')
    move_player(player, player->x, player->y + 1, map->map);
}

void		key_move_left(int *stop, t_player *player, t_map *map)
{
  (void)stop;
  if (!(player->jump) && player->x > 0
      && map->map[player->y][player->x - 1] != 'w')
    move_player(player, player->x - 1, player->y, map->map);
}

void		key_move_right(int *stop, t_player *player, t_map *map)
{
  (void)stop;
  if (!(player->jump) && (player->x + 1) < (map->x) &&
      map->map[player->y][player->x + 1] != 'w')
    move_player(player, player->x + 1, player->y, map->map);
}
