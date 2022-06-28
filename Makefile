NAME 				=	ft_containers

OS					:= $(shell uname)

INC_PATH			=	includes/
OBJS_PATH 			=	obj/
SRCS_PATH 			=	src/
CC 					=	clang++
CFLAGS				=	-Wall -Werror -Wextra -Wpedantic -std=c++98
RM					=	rm -rf

COLORS 				=	colors.hpp

SRC_FILES			=	main.cpp
GEN_HDRS			=	utilities.hpp colors.hpp

VECTOR_FILES		=	
VECTOR_HDRS			=	Vector.hpp Iterator.hpp Iterator_traits.hpp

MAP_FILES			=	
MAP_HDRS			=	map.hpp pair.hpp
RBTREE_HDRS			=	RBtree.hpp tree_iterator.hpp tree_node_types.hpp tree_utils.hpp\
						tree_algos.hpp
				
STACK_FILES			= 	
STACK_HDRS			= 	Stack.hpp

TESTER_FILES		=	map.cpp set.cpp stack.cpp vector.cpp
TESTER_HDRS			=	

ITERATOR_PATH		= 	Iterator/
MAP_PATH			=	Map/
TREE_PATH			=	RBTree/

STACK_PATH			=	Stack/
TESTER_PATH			=	tester
TESTER_FILES_PATH	= 	$(TESTER_PATH)/tests/

SRCS 				=	$(addprefix $(SRCS_PATH), $(SRC_FILES))
ITERATOR_SRCS		= 	$(addprefix $(ITERATOR_PATH), $(VECTOR_FILES))
TREE_SRCS			= 	$(addprefix $(TREE_PATH), $(RBTREE_HDRS))

TESTER_SRCS			=	$(addprefix $(TESTER_FILES_PATH), $(TESTER_FILES))

OBJS_FILES			= 	$(SRC_FILES:.cpp=.o)

OBJS 				=	$(addprefix $(OBJS_PATH), $(OBJS_FILES))

VPATH				=	$(SRCS_PATH) $(ITERATOR_PATH) $(TESTER_PATH)

ALL_INCLUDES		= 	$(addprefix $(INC_PATH), $(TREE_PATH))\
						$(addprefix $(INC_PATH), $(ITERATOR_PATH))\
						$(addprefix $(INC_PATH), $(TREE_PATH))\
						$(INC_PATH)
						

$(OBJS_PATH)%.o: %.cpp
	@$(CC) $(CFLAGS) $(addprefix -I, $(ALL_INCLUDES)) -c $< -o $@
	@printf "\033[93m▓▓▓\033[0m"

all:	$(NAME)

$(NAME):	$(OBJS_PATH) $(OBJS) 
	@$(CC) $(OBJS) -o $(NAME)
	@echo "\\n\033[32;1m\nProgram is Ready\033[0m\\n"
	@echo $(USAGE)

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@echo "\033[34;1mCreating Object Directory\n\033[0m"
	@printf "\033[32;1m\nCompiling with: \033[38;5;208m$(CFLAGS)\033[0m\\n\\n"

release: CFLAGS += -O3
release: all

debug:	CFLAGS += -g -fstandalone-debug -fno-limit-debug-info
debug:	$(NAME)

redebug : fclean debug

fmt:
	clang-format -i $(TESTER_SRCS)
	clang-format -i $(addsuffix *.hpp, $(ALL_INCLUDES))

clean:
	@$(RM) $(OBJS_FILES) $(OBJS_PATH) 
	@echo "\033[34;1mCLEAN DONE\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[34;1mFCLEAN DONE\033[0m"

re: fclean all

.PHONY: all clean fclean re linux debug redebug fmt release
