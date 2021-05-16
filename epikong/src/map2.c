#include "game.h"
#include "map.h"

static t_blockmap g_blockmap[] =
  {
    {'w', "img/wall.bmp"},
    {'s', "img/ladder.bmp"},
    {'m', NULL},
    {'o', "img/exit.bmp"},
    {'i', NULL},
    {'k', "img/redshroom.bmp"},
    {'l', "img/life.bmp"},
    {'g', "img/flower.bmp"},
    {'.', NULL},
    {0, NULL}
  };

int	get_diff(int pos, int max, int map)
{
  if (map < (max * 2))
    return (pos - max);
  if (pos - max < 0)
    return (pos - max);
  if (pos + max > map)
    return (pos + max - map);
  return (0);
}

static void	check_texture(SDL_Surface *screen,
			      char c, SDL_Rect *pos_tmp)
{
  SDL_Surface	*bloc;
  int		i;

  i = 0;
  while (g_blockmap[i].c)
    {
      if (g_blockmap[i].file && g_blockmap[i].c == c)
	{
	  if ((bloc = SDL_LoadBMP(g_blockmap[i].file)))
	    {
	      SDL_SetColorKey(bloc, SDL_SRCCOLORKEY,
			      SDL_MapRGB(bloc->format, 14, 94, 241));
	      SDL_BlitSurface(bloc, NULL, screen, pos_tmp);
	      SDL_FreeSurface(bloc);
	    }
	}
      ++i;
    }
}

void	create_map(SDL_Surface *screen, t_map *map, t_player *player)
{
  SDL_Rect	pos_tmp;
  SDL_Rect	tab_pos;
  size_t	x;
  size_t	y;

  y = 0;
  while (y < (MAX_Y / SPRITE_SIZE) && y < map->y)
    {
      tab_pos.y = player->y + y - MAX_Y / SPRITE_SIZE / 2;
      tab_pos.y -= get_diff(player->y, MAX_Y / SPRITE_SIZE / 2, map->y);
      pos_tmp.y = SPRITE_SIZE * y;
      x = 0;
      while (x < (MAX_X / SPRITE_SIZE) && x < map->x)
	{
	  tab_pos.x = player->x + x - MAX_X / SPRITE_SIZE / 2;
	  tab_pos.x -= get_diff(player->x, MAX_X / SPRITE_SIZE / 2, map->x);
	  pos_tmp.x = SPRITE_SIZE * x;
	  check_texture(screen, map->map[tab_pos.y][tab_pos.x], &pos_tmp);
	  ++x;
	}
      ++y;
    }
}
