NAME	= test

####################################################################################################
######################################### Compiler #################################################
####################################################################################################

CC		= c++
CFLAGS	= -Wall -Wextra -std=c++98 -g -Wshadow #-Werror

####################################################################################################
##################################### Include Folders ##############################################
####################################################################################################

INCLUDE =	$(addprefix -I ./includes, \
			/ \
			/0-Utilities \
			/1-Iterators \
			/2-Tree \
			)

####################################################################################################
######################################### Headers files ############################################
####################################################################################################

MAIN_HEADERS	= $(addprefix ./includes/, \
					ft_algorithm.hpp \
					ft_iterator_base.hpp \
					ft_iterator_types.hpp \
					ft_pair.hpp \
					map.hpp \
					vector.hpp \
					)

UTILS_HEADERS	= $(addprefix ./includes/0-Utilities/, \
					Colors.hpp \
					testsVector.hpp \
					)

ITERATORS_HEADERS	= $(addprefix ./includes/1-Iterators/, \
					BidirectionalIterator.hpp \
					IteratorVector.hpp \
					)

TREE_HEADERS	= $(addprefix ./includes/2-Tree/, \
					AVL.hpp \
					Node.hpp \
					)

####################################################################################################
########################################## Source files ############################################
####################################################################################################

SRC		= $(addprefix ./src/, \
          	ft-main.cpp \
          	testsVectorFT.cpp \
			)

####################################################################################################
########################################## Objects files ###########################################
####################################################################################################

%.o: %.cpp $(MAIN_HEADERS) $(UTILS_HEADERS) $(TREE_HEADERS) $(ITERATORS_HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:%.cpp=%.o)

OBJ		= $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

####################################################################################################
########################################## Default Rules ###########################################
####################################################################################################

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

####################################################################################################
####################################################################################################
####################################################################################################
