NAME		=	n_puzzle
CXX			=	c++
FLAGS		=	-std=c++17 -Wall -Wextra -Werror -O3 -g3

SRCS		=	./src/main.cpp	\
				./src/Node.class.cpp	\
				./src/utils.cpp	\
				./src/Solution.class.cpp	\
				./src/NPuzzle.class.cpp ./src/Heap.cpp \
				./src/Pool.class.cpp
HEADERS		=	-I ./inc/

BUILD_DIR   =	./build
OBJS		=	$(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEP			=	$(OBJS:%.o=%.d)

all:	$(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "Compiling $(NAME)"

-include $(DEP)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CXX) $(FLAGS) -MMD $(HEADERS) -c  $< -o $@
	@echo "Compiling $<"

clean:
	@rm -rf $(OBJS) $(DEP)
	@echo "Cleaning..."

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BUILD_DIR)

re: fclean all

.PHONY : all clean fclean re
