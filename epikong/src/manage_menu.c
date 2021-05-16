/*
** manage_menu.c for epikong in /home/watana_s/rendu/T2Rush1/etape_2
** 
** Made by susumu-clement watanabe
** Login   <watana_s@epitech.net>
** 
** Started on  Sat Mar  8 19:19:10 2014 susumu-clement watanabe
** Last update Sun Mar  9 20:29:39 2014 arnaud drain
*/

#include <SDL/SDL.h>
#include <string.h>
#include "sdl.h"
#include "event.h"
#include "map.h"
#include "menu.h"
#include "key.h"

static t_background	g_background[] =
  {
    {"maps/stage1.map", "img/background1.bmp"},
    {"maps/stage2.map", "img/background2.bmp"},
    {"maps/stage3.map", "img/background3.bmp"},
    {"maps/stage4.map", "img/backgroundpenis.bmp"},
    {"maps/stage5.map", "img/background5.bmp"},
    {NULL, NULL}
  };

static t_event	g_event[] =
  {
    {SDLK_ESCAPE, &key_menu_escape},
    {13, &key_menu_enter},
    {SDLK_KP_ENTER, &key_menu_enter},
    {SDLK_RIGHT, &key_menu_right},
    {SDLK_LEFT, &key_menu_left},
    {0, NULL},
  };

static void	keyboard_event(int event, int *stop, int *choix)
{
  int		i;

  i = 0;
  while (g_event[i].event != event && g_event[i].event)
    ++i;
  if (g_event[i].event)
    g_event[i].function(stop, choix);
}

static void	manage_menu(SDL_Surface *screen, int *stop, int *choix)
{
  SDL_Event	event;

  SDL_Flip(screen);
  SDL_WaitEvent(&event);
  if (event.type == SDL_QUIT)
    {
      *choix = 5;
      *stop = 1;
    }
  else if (event.type == SDL_KEYDOWN)
    keyboard_event(event.key.keysym.sym, stop, choix);
}

t_background	getNext(int set)
{
  static int	pos = 0;

  if (set >= 0)
    pos = set;
  else
    ++pos;
  return (g_background[pos]);
}

t_background	menu(SDL_Surface *screen)
{
  SDL_Surface	*background;
  SDL_Surface	*filter;
  SDL_Rect	pos;
  int		choix;
  int		stop;

  choix = 0;
  stop = 0;
  background = SDL_LoadBMP("img/menu.bmp");
  filter = SDL_CreateRGBSurface(SDL_HWSURFACE, 116, 86, 32, 0, 0, 0, 0);
  SDL_FillRect(filter, NULL, SDL_MapRGB(filter->format, 172, 17, 123));
  SDL_SetAlpha(filter, SDL_SRCALPHA, 128);
  while (!stop)
    {
      pos.x = 0;
      pos.y = 0;
      SDL_BlitSurface(background, NULL, screen, &pos);
      pos.x = 2 + choix * (116 + 4);
      pos.y = 456;
      SDL_BlitSurface(filter, NULL, screen, &pos);
      manage_menu(screen, &stop, &choix);
    }
  SDL_FreeSurface(filter);
  SDL_FreeSurface(background);
  return (getNext(choix));
}
