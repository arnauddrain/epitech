#ifndef KEY_H__
# define KEY_H__

#include "map.h"

/*
** GAME
*/
void		key_move_up(int *stop, t_player *player, t_map *map);
void		key_move_down(int *stop, t_player *player, t_map *map);
void		key_move_left(int *stop, t_player *player, t_map *map);
void		key_move_right(int *stop, t_player *player, t_map *map);
void		key_space(int *stop, t_player *player, t_map *map);
void		key_escape(int *stop, t_player *player, t_map *map);
void		key_enter(int *stop, t_player *player, t_map *map);

/*
** MENU
*/
void		key_menu_escape(int *stop, int *choix);
void		key_menu_enter(int *stop, int *choix);
void		key_menu_right(int *stop, int *choix);
void		key_menu_left(int *stop, int *choix);

#endif /* !KEY_H__ */
