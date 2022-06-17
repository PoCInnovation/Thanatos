SRC = main.cpp	\
      manage_messages.cpp
SRC := $(addprefix src/, $(SRC))

OBJ = $(SRC:.cpp=.o)

CFLAGS = -I include/ -std=c++20 -Wall -Wextra

NAME = client

all: $(NAME)

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJ)
	g++ $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
