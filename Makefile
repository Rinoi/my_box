NAME		=	my_box

SRCS		=	src/main.c		\
					src/utils.c		\
					src/my_box.c	\
					src/my_world.c	\

OBJS		=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS		=	-I./include -W -Wall -Wextra -g

LDFLAGS		=	-L/usr/local/lib/ -lcsfml-system  -lcsfml-window -lcsfml-graphics -lm

all: 		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		rm -f $(OBJS)

fclean: 	clean
		rm -f $(NAME)

re:		fclean all
