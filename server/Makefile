SRC =	main.cpp		\
		Server.cpp		\

SRC := $(addprefix src/, $(SRC))

OBJ = $(SRC:.cpp=.o)

CFLAGS = -I include/ -std=c++20 `mysql_config --cflags --libs`

NAME = server

all: $(NAME)

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJ)
	g++ $^ -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
