#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

NAME	=	so_long
LIBFT	= 	libft.a
LDIR	=	libft/
LMLX	=	MLX42/

# Color
GREEN	=	\033[0;32m
RED		=	\033[0;31m
BLUE	=	\033[0;34m
WHITE	=	\033[0m

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -f

# Sources are all .c files  
SRCS	=	so_long.c\
			parse.c\
			init.c\
			explore.c\
			so_long_utils.c\

OBJS	=	$(SRCS:.c=.o)
#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling . . .$(WHITE)\n"
	@printf "$(BLUE)MLX42: $(WHITE)"; cd MLX42/ && make && cd ..
	@printf "$(BLUE)LIBFT: $(WHITE)"; cd LIBFT/ && make && cd ..
	@$(CC) $(CFLAGS) $(SRCS) MLX42/libmlx42.a $(LDIR)$(LIBFT) -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)
	@echo "$(BLUE)Create objects$(WHITE)"

bonus: CFLAGS += -D BONUS
bonus: fclean all

glfwdown:
	brew install glfw

# Removes objects
clean:
	@$(RM) $(OBJS)
	@cd LIBFT/ && make clean && cd ..
	@cd MLX42/ && make clean && cd ..
	@echo "$(RED)Removes objects$(WHITE)"

# Removes objects and executables
fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LDIR)$(LIBFT)
	@$(RM) MLX42/libmlx42.a
	@echo "$(RED)Removes executables$(WHITE)"

# Removes objects and executables and remakes
re: fclean all
	@echo "\n$(GREEN)Remake complete$(WHITE)"
