#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "monsters.h"
#include "map.h"

static void	monstersMove_pos(t_map *map, t_monsters *tmp, int pos)
{
  if (map->map[tmp->posY][tmp->posX + pos] != 'w' &&
      (map->map[tmp->posY + 1][tmp->posX + pos] == 'w' ||
       map->map[tmp->posY + 1][tmp->posX + pos] == 's'))
    {
      (tmp->posX) += pos;
    }
  else
    {
      tmp->dir = !(tmp->dir);
      if (tmp->dir)
	tmp->file = "img/monster_right.bmp";
      else
	tmp->file = "img/monster_left.bmp";
    }
}

void		monstersMove(t_map *map, t_monsters *list)
{
  t_monsters	*tmp;

  tmp = list;
  while (tmp)
    {
      if (tmp->dir == LEFT)
	monstersMove_pos(map, tmp, -1);
      else
	monstersMove_pos(map, tmp, 1);
      tmp = tmp->next;
    }
}

void		aff_monsters(t_map *map, t_monsters *list, t_player *player,
			     SDL_Surface *screen)
{
  t_monsters	*tmp;
  SDL_Surface	*sprite;
  SDL_Rect	pos;

  tmp = list;
  while (tmp)
    {
      pos.x = tmp->posX - player->x + MAX_X / SPRITE_SIZE / 2;
      pos.x += get_diff(player->x, MAX_X / SPRITE_SIZE / 2, map->x);
      pos.y = tmp->posY - player->y + MAX_Y / SPRITE_SIZE / 2;
      pos.y += get_diff(player->y, MAX_Y / SPRITE_SIZE / 2, map->y);
      pos.x *= SPRITE_SIZE;
      pos.y *= SPRITE_SIZE;
      if (pos.x >= 0 && pos.x < MAX_X && pos.y >= 0 && pos.y < MAX_Y)
	{
	  if ((sprite = SDL_LoadBMP(tmp->file)))
	    {
	      SDL_SetColorKey(sprite, SDL_SRCCOLORKEY,
			      SDL_MapRGB(sprite->format, 14, 94, 241));
	      SDL_BlitSurface(sprite, NULL, screen, &pos);
	      SDL_FreeSurface(sprite);
	    }
	}
      tmp = tmp->next;
    }
}

static t_monsters	*monstersList_addElem(t_monsters *node, int x, int y)
{
  t_monsters		*new;
  t_monsters		*tmp;

  if (!(new = malloc(sizeof(*new))))
    {
      fprintf(stderr,
	      "error: malloc returned an error during list creation\n");
      return (NULL);
    }
  new->posX = x;
  new->posY = y;
  new->dir = rand() % 2;
  if (new->dir)
    new->file = "img/monster_right.bmp";
  else
    new->file = "img/monster_left.bmp";
  new->next = NULL;
  if (!node)
    return (new);
  tmp = node;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new;
  return (node);
}

t_monsters	*monstersList_init(t_map *map)
{
  t_monsters	*node;
  int		x;
  int		y;

  node = NULL;
  srand(time(NULL));
  y = 0;
  while (map->map[y])
    {
      x = 0;
      while (map->map[y][x])
	{
	  if (map->map[y][x] == MONSTER)
	    if (!(node = monstersList_addElem(node, x, y)))
	      return (NULL);
	  ++x;
	}
      ++y;
    }
  return (node);
}

void		collision(SDL_Surface *screen, t_monsters *list, t_player *player)
{
  SDL_Surface	*red_screen;
  SDL_Rect	pos;

  if (list)
    {
      if (list->posX == (int)player->x && list->posY == (int)player->y)
	{
	  pos.x = 0;
	  pos.y = 0;
	  red_screen = SDL_CreateRGBSurface(SDL_HWSURFACE, MAX_X,
					    MAX_Y, 32, 0, 0, 0, 0);
	  SDL_FillRect(red_screen, NULL,
		       SDL_MapRGB(red_screen->format, 255, 0, 0));
	  SDL_SetAlpha(red_screen, SDL_SRCALPHA, 128);
	  SDL_BlitSurface(red_screen, NULL, screen, &pos);
	  SDL_FreeSurface(red_screen);
	  --(player->life);
	  return;
	}
      collision(screen, list->next, player);
    }
}
