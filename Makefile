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
BONUS_ICON		= 💎

# Program name
NAME 			= miniRT
BONUS_NAME      = bonus_miniRT

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g

# Directories
LIBFT_DIR		= libft
BONUS_DIR		= bonus

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

SRCS 			= src/main.c src/parser/parse_scene.c src/parser/parse_camera.c src/utils/parse_utils_1.c \
				src/utils/parse_utils_2.c src/utils/parse_utils_atof.c src/parser/parse_ambient.c \
				src/parser/parse_objects.c src/utils/parse_obj_utils.c \
				src/math/vector_ops.c src/math/vector_utils.c src/parser/parse_light.c \
				src/parser/parse_sphere.c src/parser/parse_plane.c src/parser/parse_cylinder.c \
				src/math/math_helper.c src/utils/validation.c src/render/camera.c src/render/ray.c \
				src/render/render.c src/window/init.c src/window/image.c src/window/event.c src/intersect/sphere.c \
				src/intersect/intersect.c src/lighting/lighting.c src/lighting/ambient.c src/lighting/diffuse.c \
				src/intersect/plane.c src/lighting/shadow.c src/intersect/cylinder.c

BONUS_SRCS		= $(BONUS_DIR)/src/main.c $(BONUS_DIR)/src/parser/parse_scene.c $(BONUS_DIR)/src/parser/parse_camera.c $(BONUS_DIR)/src/utils/parse_utils_1.c \
				$(BONUS_DIR)/src/utils/parse_utils_2.c $(BONUS_DIR)/src/utils/parse_utils_atof.c $(BONUS_DIR)/src/parser/parse_ambient.c \
				$(BONUS_DIR)/src/parser/parse_objects.c $(BONUS_DIR)/src/utils/parse_obj_utils.c $(BONUS_DIR)/src/utils/parse_obj_utils_1.c \
				$(BONUS_DIR)/src/math/vector_ops.c $(BONUS_DIR)/src/math/vector_utils.c $(BONUS_DIR)/src/parser/parse_light.c \
				$(BONUS_DIR)/src/parser/parse_sphere.c $(BONUS_DIR)/src/parser/parse_plane.c $(BONUS_DIR)/src/parser/parse_cylinder.c \
				$(BONUS_DIR)/src/math/math_helper.c $(BONUS_DIR)/src/utils/validation.c $(BONUS_DIR)/src/render/camera.c $(BONUS_DIR)/src/render/ray.c \
				$(BONUS_DIR)/src/render/render.c $(BONUS_DIR)/src/window/init.c $(BONUS_DIR)/src/window/image.c $(BONUS_DIR)/src/window/event.c $(BONUS_DIR)/src/intersect/sphere.c \
				$(BONUS_DIR)/src/intersect/intersect.c $(BONUS_DIR)/src/lighting/lighting.c $(BONUS_DIR)/src/lighting/ambient.c $(BONUS_DIR)/src/lighting/diffuse.c \
				$(BONUS_DIR)/src/intersect/plane.c $(BONUS_DIR)/src/lighting/shadow.c $(BONUS_DIR)/src/intersect/cylinder.c $(BONUS_DIR)/src/utils/print.c \
				$(BONUS_DIR)/src/lighting/specular.c $(BONUS_DIR)/src/parser/parse_cone.c $(BONUS_DIR)/src/utils/intersection_utils.c $(BONUS_DIR)/src/intersect/cone.c \
				$(BONUS_DIR)/src/textures/checkerboard.c $(BONUS_DIR)/src/textures/bump_texture.c $(BONUS_DIR)/src/textures/uv.c

OBJ_DIR 		= ./obj
BONUS_OBJ_DIR 		= $(BONUS_DIR)/bonus_obj
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
BONUS_OBJS = $(patsubst $(BONUS_DIR)/%.c,$(BONUS_OBJ_DIR)/%.o,$(BONUS_SRCS))

LIBS := -lm
LIBS += -L$(LIBFT_DIR) -lft
INCLUDES = -I./includes/
BONUS_INCLUDES = -I$(BONUS_DIR)/includes/

# Count total files to compile
TOTAL_FILES := $(words $(SRCS))
BONUS_TOTAL_FILES := $(words $(BONUS_SRCS))
# Variable to track current file number
CURR_FILE := 0

# Platform-specific MLX configuration
ifeq ($(UNAME_S),Linux)
    LIBS += -L./mlx -lmlx -lXext -lX11 -ldl
endif

ifeq ($(UNAME_S),Darwin)
    LIBS += -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
    INCLUDES += -Imlx_macos
	BONUS_INCLUDES += -Imlx_macos
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

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJ_DIR) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)
	@echo "\n$(BONUS_ICON)$(CYAN)Build bonus complete!$(RESET)"

#  Create object files directory
$(OBJ_DIR):
	@echo "$(YELLOW)Creating object files directory...$(RESET)"
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(YELLOW)Directory created!$(RESET)"

$(BONUS_OBJ_DIR):
	@echo "$(YELLOW)Creating bonus object files directory...$(RESET)"
	@$(MKDIR) $(BONUS_OBJ_DIR)
	@echo "$(BONUS_ICON)$(YELLOW)Directory for bonus created!$(RESET)"

#  Compile source files to object files
$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@$(eval CURR_FILE=$(shell echo $$(($(words $(wildcard $(OBJ_DIR)/*.o $(OBJ_DIR)/*/*.o $(OBJ_DIR)/*/*/*.o)) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURR_FILE) * 100 / $(TOTAL_FILES)))))
	@$(eval PROGRESS=$(shell echo $$(($(CURR_FILE) * 30 / $(TOTAL_FILES)))))
	@printf "\r$(BLUE)Minirt Building: [%-30s] %3d%%$(RESET)" \
		"$(shell printf '#%.0s' $$(seq 1 $(PROGRESS)))" \
		"$(PERCENT)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@$(MKDIR) $(dir $@)
	@$(eval CURR_FILE=$(shell echo $$(($(words $(wildcard $(BONUS_OBJ_DIR)/*.o $(BONUS_OBJ_DIR)/*/*.o $(BONUS_OBJ_DIR)/*/*/*.o)) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURR_FILE) * 100 / $(BONUS_TOTAL_FILES)))))
	@$(eval PROGRESS=$(shell echo $$(($(CURR_FILE) * 30 / $(BONUS_TOTAL_FILES)))))
	@printf "\r$(BLUE)Minirt Bonus Building: [%-30s] %3d%%$(RESET)" \
		"$(shell printf '#%.0s' $$(seq 1 $(PROGRESS)))" \
		"$(PERCENT)"
	@$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@

# Clean up object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@echo "$(RED)Object files cleaned!$(RESET)"

# Full clean up
fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@echo "$(RED)Executable cleaned!$(RESET)"

# Rebuild the project
re: fclean all
	@echo "$(GREEN)Rebuild complete!$(RESET)"

rebonus: fclean bonus
	@echo "$(BONUS_ICON)$(GREEN)Rebuild bonus complete!$(RESET)"

# Phony targets
.PHONY: all clean fclean re bonus rebonus