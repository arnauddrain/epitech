#include <SDL/SDL.h>
#include <string.h>
#include <unistd.h>
#include "sdl.h"
#include "event.h"
#include "monsters.h"
#include "player.h"
#include "menu.h"
#include "game.h"

int		launch_game(int next)
{
  SDL_Surface	*screen;
  t_map		*map;
  t_background	background;

  if (!next)
    {
      if (!(screen = SDL_SetVideoMode(600, 553, 32, SDL_HWSURFACE)))
	return (fprintf(stderr, "Erreur lors du chargement du mode vidéo : %s\n",
			SDL_GetError()));
      background = menu(screen);
      SDL_FreeSurface(screen);
    }
  else
    background = getNext(-1);
  if (!(background.file))
    return (-1);
  if (!(map = get_map(background.file)))
    return (-1);
  if (!(screen = resize_sdl(map)))
    return (-1);
  game(background.background, screen, map);
  return (0);
}

static void	life(SDL_Surface *screen, t_player *player)
{
  int		i;
  SDL_Surface	*life;
  SDL_Rect	pos;

  pos.y = 0;
  i = 0;
  if (!(life = SDL_LoadBMP("img/life.bmp")))
    return;
  SDL_SetColorKey(life, SDL_SRCCOLORKEY,
		  SDL_MapRGB(life->format, 14, 94, 241));
  while (i < player->life)
    {
      pos.x = i * SPRITE_SIZE;
      SDL_BlitSurface(life, NULL, screen, &pos);
      ++i;
    }
  SDL_FreeSurface(life);
}

static void	key(SDL_Surface *screen)
{
  SDL_Surface	*key;
  SDL_Rect	pos;

  pos.y = SPRITE_SIZE;
  pos.x = 0;
  if (!(key = SDL_LoadBMP("img/redshroom.bmp")))
    return;
  SDL_SetColorKey(key, SDL_SRCCOLORKEY,
		  SDL_MapRGB(key->format, 14, 94, 241));
  SDL_BlitSurface(key, NULL, screen, &pos);
  SDL_FreeSurface(key);
}

static void	list_events(t_map *map, SDL_Surface *screen,
			    t_player *player, t_monsters *monsters)
{
  gravity(map, player);
  create_map(screen, map, player);
  monstersMove(map, monsters);
  aff_monsters(map, monsters, player, screen);
  collision(screen, monsters, player);
  aff_player(map, player, screen);
  life(screen, player);
  if (player->key)
    key(screen);
  SDL_Flip(screen);
}

void		game(char *background, SDL_Surface *screen, t_map *map)
{
  int		stop;
  t_monsters	*monsters;
  t_player	player;

  stop = 0;
  find_player(map->map, &player);
  monsters = monstersList_init(map);
  while (!stop && player.life && player.falling <= 4 &&
	 (map->map[player.y][player.x] != 'o' || !(player.key)))
    {
      SDL_Delay(75);
      create_screen(screen, background);
      list_events(map, screen, &player, monsters);
      manage_event(&stop, &player, map);
    }
  SDL_FreeSurface(screen);
  if (player.life == 0 || player.falling > 4)
    loose();
  else
    launch_game(!stop);
}
