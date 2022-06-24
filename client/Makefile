rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2)	\
			$(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard, src, *.cpp)

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
