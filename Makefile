NAME	= test

CC		= c++
CFLAGS	= -Wall -Wextra -std=c++98 -g -Wshadow #-Werror
INCLUDE =	-I ./includes \
			-I ./includes/Tree \
			-I ./includes/Iterators

MAIN_HEADERS	= $(addprefix ./includes/, \
					Colors.hpp \
					ft_algorithm.hpp \
					ft_iterator_base.hpp \
					ft_iterator_types.hpp \
					map.hpp \
					pair.hpp \
					testsVector.hpp \
					vector.hpp \
					)

ITERATORS_HEADERS	= $(addprefix ./includes/Iterators/, \
					BidirectionalIterator.hpp \
					IteratorVector.hpp \
					)

TREE_HEADERS	= $(addprefix ./includes/Tree/, \
					AVL.hpp \
					Node.hpp \
					)

SRC		= $(addprefix ./src/, \
          	ft-main.cpp \
          	testsVectorFT.cpp \
			)

%.o: %.cpp $(MAIN_HEADERS) $(TREE_HEADERS) $(ITERATORS_HEADERS)
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
