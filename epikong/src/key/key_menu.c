#include "key.h"

void		key_menu_escape(int *stop, int *choix)
{
  *stop = 1;
  *choix = 5;
}

void		key_menu_enter(int *stop, int *choix)
{
  (void)choix;
  *stop = 1;
}

void		key_menu_right(int *stop, int *choix)
{
  (void)stop;
  *choix = (*choix + 1) % 5;
}

void		key_menu_left(int *stop, int *choix)
{
  (void)stop;
  --(*choix);
  if (*choix < 0)
    *choix = 4;
}
