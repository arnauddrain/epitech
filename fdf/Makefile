##
## Makefile for makefile in /home/drain_a//tps/i_graph/fdf
## 
## Made by arnaud drain
## Login   <drain_a@epitech.net>
## 
## Started on  Thu Nov 22 20:06:27 2012 arnaud drain
## Last update Sun Dec  9 22:46:12 2012 arnaud drain
##

# Updated during refacto for MacOS (post-Epitech)

CC	= cc

NAME	= fdf

SRCS	= src/main.c \
	 src/gere.c \
	 src/fdf.c \
	 src/lib.c \
	 src/my_str_to_inttab.c \
	 src/get_next_line.c \
	 src/draw.c

OBJS	= $(SRCS:.c=.o)

RM	= rm -f

INC = -I/usr/X11/include -Iinclude

CFLAGS	= $(INC)

LDFLAGS = -L/usr/X11 -L/usr/X11/lib -lXext -lX11 -lmlx

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re