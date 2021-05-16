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

static t_mfile	*fill_map(t_mfile *mf)
{
  mf->line = NULL;
  mf->len = 0;
  while ((mf->read = getline((&(mf->line)), (&(mf->len)), mf->fp)) > 0)
    {
      ++(mf->map->y);
      if (mf->line[mf->read - 1] == '\n')
	mf->line[mf->read - 1] = 0;
      if (!(mf->map->map =
	    realloc(mf->map->map, sizeof(*(mf->map->map)) * (mf->map->y + 1))))
	{
	  fprintf(stderr, "An error has occured on realloc\n");
	  return (NULL);
	}
      if (!(mf->map->map[mf->map->y - 1] = strdup(mf->line)))
	{
	  fprintf(stderr, "Error in strdup\n");
	  return (NULL);
	}
      mf->map->map[mf->map->y] = NULL;
    }
  free(mf->line);
  return (mf);
}

static int	check2(char **map)
{
  SDL_Rect	size;
  int		flag[3] = {0};

  size.x = 0;
  while (map[size.x])
    {
      size.y = 0;
      while (map[size.x][size.y])
	{
	  flag[0] += (map[size.x][size.y] == 'i');
	  flag[1] += (map[size.x][size.y] == 'o');
	  flag[2] += (map[size.x][size.y] == 'k');
	  if (((size.x == 0 || map[size.x + 1] == NULL) &&
	       map[size.x][size.y] != 'w') ||
	      (!(size.x == 0 || map[size.x + 1] == NULL) &&
	       map[size.x][0] != 'w' && map[size.x][strlen(map[size.x])] != 'w'))
	    return (-1);
	  ++size.y;
	}
      ++size.x;
    }
  if (flag[0] != 1 && flag[1] != 1 && flag[2] != 1)
    return (-1);
  return (0);
}

static int	check_case(char c)
{
  int		i;

  i = 0;
  while (i >= 0 && g_blockmap[i].c)
    {
      if (g_blockmap[i].c == c)
	i = -2;
      ++i;
    }
  if (i >= 0)
    return (1);
  return (0);
}

static int	check_map(char **map, size_t *len)
{
  int		ite[2] = {0};

  *len = strlen(map[0]);
  ite[0] = 0;
  while (map[ite[0]])
    {
      ite[1] = 0;
      if (strlen(map[ite[0]]) != *len)
	return (fprintf(stderr, "Line %d has wrong size\n", ite[0]));
      if (check2(map) == -1)
	return (fprintf(stderr, "Bad map\n"));
      while (map[ite[0]][ite[1]])
	{
	  if (check_case(map[ite[0]][ite[1]]))
	    return (fprintf(stderr,
			    "Wrong char at %d:%d\n", ite[1] + 1, ite[0] + 1));
	  ++ite[1];
	}
      ++ite[0];
    }
  return (0);
}

t_map		*get_map(char *mapfile)
{
  t_mfile	mf;

  if ((mf.map = malloc(sizeof(*(mf.map)))) == NULL)
    {
      fprintf(stderr, "An error has occuerd on malloc\n");
      return (NULL);
    }
  mf.map->map = NULL;
  mf.map->y = 0;
  if (!(mf.fp = fopen(mapfile, "r")))
    {
      fprintf(stderr, "Error while opening the file %s\n", mapfile);
      return (NULL);
    }
  if (!fill_map(&mf))
    return (NULL);
  if (!mf.map->map)
    {
      fprintf(stderr, "Error map is empty\n");
      free(mf.map);
      return (NULL);
    }
  if (check_map(mf.map->map, &(mf.map->x)))
    return (NULL);
  return (mf.map);
}
