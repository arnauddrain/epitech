#ifndef EVENT_H_
# define EVENT_H_

#include "player.h"
#include "map.h"

typedef struct	s_event
{
  int		event;
  void		(*function)();
}		t_event;

void	manage_event(int *stop, t_player *player, t_map *map);

#endif /* !EVENT_H_ */
