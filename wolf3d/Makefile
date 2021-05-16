##
## Makefile for makefile in /home/drain_a//tps/i_graph/fdf
## 
## Made by arnaud drain
## Login   <drain_a@epitech.net>
## 
## Started on  Thu Nov 22 20:06:27 2012 arnaud drain
## Last update Fri Jan 11 12:28:49 2013 arnaud drain
##

# Updated during refacto for MacOS (post-Epitech)

CC	= cc

NAME	= wolf3d

SRCS	= src/main.c \
	src/game.c \
	src/map.c \
	src/gere.c \
	src/lib.c \
	src/get_next_line.c \
	src/draw.c \
	src/set_map.c \
	src/aff_win.c \
	src/calc_win.c \
	src/lvl.c \
	src/move.c \
	src/map_begin.c \
	src/gere_map.c

OBJS	= $(SRCS:.c=.o)

RM	= rm -f

INC = -I/usr/X11/include -Iinclude

CFLAGS	= $(INC) -Wno-implicit-function-declaration

LDFLAGS = -L/usr/X11 -L/usr/X11/lib -lXext -lX11 -lmlx

all: $(NAME)

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS) $(LDFLAGS)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re