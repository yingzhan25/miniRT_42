# Color definitions
RESET      = \033[0m
RED        = \033[31m
GREEN      = \033[32m
YELLOW     = \033[33m
BLUE       = \033[34m
CYAN       = \033[36m
BOLD       = \033[1m
UNDERLINE  = \033[4m

# Emojis
SUCCESS			= ✅
BUILD			= 🔨
CLEAN			= 🧹

# Program name
NAME 			= minirt

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g

# Directories
LIBFT_DIR		= libft

# Library files
LIBFT			= $(LIBFT_DIR)/libft.a

# Library flags
LFLAGS      = -L$(LIBFT_DIR) -lft

# Math library
MATH_LIB		= -lm

# Platform detection
RM 				= rm -f
MKDIR			= mkdir -p
RMDIR			= rm -rf

INCLUDES 		= -I./includes/ -I$(LIBFT_DIR)/includes

SRCS 			= src/main.c src/parser/parse_scene.c src/parser/parse_elements.c src/parser/parse_utils.c

OBJ_DIR 		= ./obj

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(LIBFT):
	@echo "$(GREEN)Building Libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft built!$(RESET)"

#  Build the executable
$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	@echo "$(CYAN)Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(MATH_LIB) -o $(NAME)
	@echo "$(CYAN)Build complete!$(RESET)"

#  Create object files directory
$(OBJ_DIR):
	@echo "$(YELLOW)Creating object files directory...$(RESET)"
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(YELLOW)Directory created!$(RESET)"

#  Compile source files to object files
$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(BLUE)Compiled $< to $@$(RESET)"

# Clean up object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)Object files cleaned!$(RESET)"

# Full clean up
fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)Executable cleaned!$(RESET)"

# Rebuild the project
re: fclean all
	@echo "$(GREEN)Rebuild complete!$(RESET)"

# Phony targets
.PHONY: all clean fclean re valgrind