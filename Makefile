NAME = minirt
CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lm
RM = rm -f
INCLUDES = -I./includes/ -I./libft/includes/

SRCS = src/main.c src/parser/parse_scene.c

OBJ_DIR = ./obj

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT = ./libft/libft.a

all: $(NAME)
$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/tokenizing $(OBJ_DIR)/parsing $(OBJ_DIR)/expanding \
	$(OBJ_DIR)/signals $(OBJ_DIR)/exec $(OBJ_DIR)/exec/built_ins \
	$(OBJ_DIR)/env $(OBJ_DIR)/exec/expansion $(OBJ_DIR)/heredoc \
	$(OBJ_DIR)/exec/non_builtin \

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re