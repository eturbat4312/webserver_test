NAME = web

SRC = src/main.cpp src/config.cpp src/location.cpp src/serverdata.cpp src/servers.cpp src/webserver.cpp 

CC 		= c++

FLAGS	= -Wall -Wextra -Werror -std=c++98

OBJS 	= $(SRC:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS)

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(SRC:.cpp=.o)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re