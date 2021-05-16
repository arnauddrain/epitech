NAME	= 	epikong

SRCS	= 	src/main.c \
		src/game.c \
		src/event.c \
		src/map.c \
		src/map2.c \
		src/manage_menu.c \
		src/sdl.c \
		src/player.c \
		src/monsters.c \
		src/key/key_move.c \
		src/key/key_menu.c \
		src/key/key_escape.c \
		src/key/key_space.c \
		src/key/key_enter.c \
		src/loose.c

OBJS	= 	$(SRCS:.c=.o)

CC	= 	gcc

CFLAGS	= 	-Iinclude -W -Wall -Werror -Wextra

RM	= 	rm -f

all: 		$(NAME)

$(NAME): 	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) -lSDL

clean:		
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
