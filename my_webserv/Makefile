SRCS = src/main.cpp src/config.cpp src/location.cpp src/serverdata.cpp src/servers.cpp src/webserver.cpp 
OBJS = ${SRCS:.c=.o}
HEADER = includes
NAME = webserver
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
GCC = c++ -g
CC = c++ -g -lreadline


FLAGS += -I$(HOME)/.brew/opt/readline/include
READLINE += -L$(HOME)/.brew/opt/readline/lib


.c.o:
			${GCC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}	
				${CC} ${OBJS} ${CFLAGS} ${FLAGS} ${READLINE} -o ${NAME}

all: $(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re