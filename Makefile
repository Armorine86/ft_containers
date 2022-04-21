NAME 				=	ft_containers

OS					:= $(shell uname)

INC_PATH			=	src/includes/
OBJS_PATH 			=	obj/
SRCS_PATH 			=	src/
CC 					=	clang++
CFLAGS				=	-Wall -Werror -Wextra -Wpedantic -std=c++98
RM					=	rm -rf

INC_FILES 			=	defines.hpp colors.hpp

SRC_FILES			=	main.cpp

VECTOR_FILES		=	
VECTOR_HDRS			=	Vector.hpp Iterator.hpp Iterator_traits.hpp

MAP_FILES			=	
MAP_HDRS			=	
				
STACK_FILES			= 	
STACK_HDRS			= 	

TESTER_FILES		=	
TESTER_HDRS			=	

VECTOR_PATH			= 	$(SRCS_PATH)Vector/
# MAP_PATH			=	$(SRCS_PATH)Map
# STACK_PATH			=	$(SRCS_PATH)Stack
# TESTER_PATH			=	testers/

SRCS 				=	$(addprefix $(SRCS_PATH), $(SRC_FILES))
# VECTOR_SRCS			= 	$(addprefix $(VECTOR_PATH), $(VECTOR_FILES))
# MAP_SRCS				= 	$(addprefix $(MAP_PATH), $(MAP_FILES))
# STACK_SRCS			=	$(addprefix $(STACK_PATH), $(STACK_FILES))
# TESTER_SRCS			=	$(addprefix $(TESTER_PATH), $(TESTER_FILES))

OBJS_FILES			= 	$(SRC_FILES:.cpp=.o) #$(VECTOR_FILES:.cpp=.o) $(STACK_FILES:.cpp=.o)\
						$(MAP_FILES:.cpp=.o) $(TESTER_FILES:.cpp=.o)

INCLUDES			=	$(addprefix $(INC_PATH), $(INC_FILES))	
OBJS 				=	$(addprefix $(OBJS_PATH), $(OBJS_FILES))

VPATH				=	$(SRCS_PATH) #$(VECTOR_PATH) $(STACK_PATH) $(MAP_PATH) $(TESTER_PATH)

ALL_INCLUDES		= 	$(INC_PATH) \
					 	$(VECTOR_PATH) \
						# $(MAP_PATH) \
						$(STACK_PATH) \
						$(TESTER_PATH) \

USAGE				=	#Program Usage Message

$(OBJS_PATH)%.o: %.cpp
	$(CC) $(CFLAGS) $(addprefix -I, $(ALL_INCLUDES)) -c $< -o $@
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

# linux :	$(OBJS_PATH) $(OBJS)
# 	@echo "\033[95mCompiling Program\033[0m"
# 	$(CC) $(OBJS) -o $(NAME)
# 	@echo "\\n\033[32;1mProgram is Ready\033[0m \\n"
# 	@echo $(USAGE)

# linux_debug: CFLAGS += -g -fstandalone-debug -fno-limit-debug-info
# linux_debug: linux

# linux_redebug : fclean linux_debug

debug:	CFLAGS += -g -fstandalone-debug -fno-limit-debug-info
debug:	$(NAME)
	@printf "\033[32;1m\nCompiling with: \033[38;5;208m$(CFLAGS)\033[0m \\n"

redebug : fclean debug

fmt		:
	clang-format -i $(SRCS) $(addsuffix *, $(ALL_INCLUDES))

clean:
	@$(RM) $(OBJS_FILES) $(OBJS_PATH) 
	@echo "\033[34;1mCLEAN DONE\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[34;1mFCLEAN DONE\033[0m"

re: fclean all

redebug: fclean debug

.PHONY: all clean fclean re linux debug redebug fmt
