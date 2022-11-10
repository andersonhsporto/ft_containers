NAME	= test

CC		= c++
CFLAGS	= -Wall -Wextra -g -Wshadow -std=c++98 #-Werror
INCLUDE = -I ./includes
HEADERS	= $(addprefix ./includes/, \
			Colors.hpp \
			ft_algorithm.hpp \
			ft_iterator_base.hpp \
			ft_iterator_types.hpp \
			ft_utility.hpp \
			IteratorVector.hpp \
			Vector.hpp \
			)

SRC		= $(addprefix ./src/, \
          	ft-main.cpp \
          	testsVectorFT.cpp \
           )

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:%.cpp=%.o)

OBJ		= $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
