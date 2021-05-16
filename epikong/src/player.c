#include <SDL/SDL.h>
#include "player.h"
#include "game.h"

void	find_player(char **map, t_player *player)
{
  int	x;
  int	y;

  y = 0;
  while (map[y])
    {
      x = 0;
      while (map[y][x])
	{
	  if (map[y][x] == 'i')
	    {
	      player->x = x;
	      player->y = y;
	    }
	  ++x;
	}
      ++y;
    }
  player->falling = 0;
  player->key = 0;
  player->life = 3;
  player->file = "img/player_left.bmp";
}

void		aff_player(t_map *map, t_player *player, SDL_Surface *screen)
{
  SDL_Surface	*sprite;
  SDL_Rect	pos;

  if (!(sprite = SDL_LoadBMP(player->file)))
    return;
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY,
		  SDL_MapRGB(sprite->format, 14, 94, 241));
  pos.x = MAX_X / 2;
  pos.x += SPRITE_SIZE * get_diff(player->x, MAX_X / SPRITE_SIZE / 2, map->x);
  pos.y = MAX_Y / 2;
  pos.y += SPRITE_SIZE * get_diff(player->y, MAX_Y / SPRITE_SIZE / 2, map->y);
  SDL_BlitSurface(sprite, NULL, screen, &pos);
  SDL_FreeSurface(sprite);
}

void	jump(t_map *map, t_player *player)
{
  if (player->jump < 0)
    player->jump *= -1;
  else if (player->jump)
    {
      if (player->jump == JUMP_UP && map->map[player->y - 1][player->x] != 'w')
	--(player->y);
      else if (player->jump == JUMP_LEFT &&
	       map->map[player->y][player->x - 1] != 'w')
	--(player->x);
      else if (player->jump == JUMP_RIGHT &&
	       map->map[player->y][player->x + 1] != 'w')
	++(player->x);
      player->jump = 0;
      return;
    }
}

void	gravity(t_map *map, t_player *player)
{
  int	speed;
  int	i;

  speed = (player->falling * 2) + (player->falling == 0);
  player->falling = 0;
  if (player->jump)
    jump(map, player);
  else if (map->map[player->y][player->x] == 's')
    return;
  else if (map->map[player->y + 1][player->x] != 's' &&
      map->map[player->y + 1][player->x] != 'w')
    {
      i = 0;
      while (map->map[player->y + i][player->x] != 's' &&
	     map->map[player->y + i][player->x] != 'w')
	++i;
      if (i <= speed)
	speed = i - 1;
      player->y += speed;
      player->falling = speed;
    }
}
