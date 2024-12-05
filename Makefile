NAME		=	n_puzzle
CXX			=	c++
FLAGS		=	-Wall -Wextra -Werror -O3

SRCS		=	./src/main.cpp ./src/Node.class.cpp
HEADERS		=	-I ./inc
LIBS		=

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
