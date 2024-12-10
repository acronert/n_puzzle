NAME		=	n_puzzle
CXX			=	c++
FLAGS		=	-std=c++17 -Wall -Wextra -Werror -O3 -g3

SRCS		=	./src/main.cpp ./src/Node.class.cpp ./src/utils.cpp ./src/Heap.cpp
HEADERS		=	-I ./inc/ -I ./cpp_heap/

OBJS		=	$(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "Compiling $(NAME)"

%.o: %.cpp
	@$(CXX) $(FLAGS) $(HEADERS) $(LIBS) -c  $< -o $@
	@echo "Compiling $<"

clean:
	@rm -rf $(OBJS)
	@echo "Cleaning..."

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
