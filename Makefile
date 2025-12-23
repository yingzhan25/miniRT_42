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
UNAME_S 		= $(shell uname)
RM 				= rm -rf
MKDIR			= mkdir -p

SRCS 			= src/main.c src/parser/parse_scene.c src/parser/parse_camera.c src/parser/parse_utils.c \
				src/parser/parse_ambient.c src/parser/parse_objects.c src/parser/parse_obj_utils.c \
				src/math/vector_ops.c src/math/vector_utils.c src/parser/parse_light.c src/utils/error.c \
				src/parser/parse_sphere.c src/parser/parse_plane.c src/parser/parse_cylinder.c \
				src/math/math_helper.c src/utils/validation.c src/render/camera.c src/render/ray.c \
				src/render/render.c src/window/init.c src/window/image.c src/window/event.c src/intersect/sphere.c \
				src/intersect/intersect.c src/lighting/lighting.c src/lighting/ambient.c src/lighting/diffuse.c \
				src/lighting/shadow.c

OBJ_DIR 		= ./obj
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBS := -lm
LIBS += -L$(LIBFT_DIR) -lft
INCLUDES += -I./includes/

# Count total files to compile
TOTAL_FILES := $(words $(SRCS))
# Variable to track current file number
CURR_FILE := 0

# Platform-specific MLX configuration
ifeq ($(UNAME_S),Linux)
    LIBS += -L./mlx -lmlx -lXext -lX11 -ldl
endif

ifeq ($(UNAME_S),Darwin)
    LIBS += -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
    INCLUDES += -Imlx_macos
endif

all: $(NAME)

#	Building LIBFT
$(LIBFT):
	@echo "$(GREEN)Building Libft...$(RESET)"
	@make -C $(LIBFT_DIR) --silent
	@echo "$(GREEN)Libft built!$(RESET)"

#  Build the executable
$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\n$(CYAN)Build complete!$(RESET)"

#  Create object files directory
$(OBJ_DIR):
	@echo "$(YELLOW)Creating object files directory...$(RESET)"
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(YELLOW)Directory created!$(RESET)"

#  Compile source files to object files
$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@$(eval CURR_FILE=$(shell echo $$(($(CURR_FILE) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURR_FILE) * 100 / $(TOTAL_FILES)))))
	@$(eval PROGRESS=$(shell echo $$(($(CURR_FILE) * 30 / $(TOTAL_FILES)))))
	@printf "\r$(BLUE)Minirt Building: [%-30s] %3d%%$(RESET)" \
		"$(shell printf '#%.0s' $$(seq 1 $(PROGRESS)))" \
		"$(PERCENT)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@echo "$(RED)Object files cleaned!$(RESET)"

# Full clean up
fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@echo "$(RED)Executable cleaned!$(RESET)"

# Rebuild the project
re: fclean all
	@echo "$(GREEN)Rebuild complete!$(RESET)"

# Phony targets
.PHONY: all clean fclean re