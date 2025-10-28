NAME        = cub3D

BUILD_DIR   = build
INCLUDE_DIR = include
LIBFT_DIR   = library/libft
MLX_DIR     = library/minilibx-linux
GNL_DIR     = library/gnl

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)
MLXFLAGS   = -lX11 -lXext -lm

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

SRCS = \
	src/main.c

OBJS = $(SRCS:src/%.c=$(BUILD_DIR)/%.o)

RESET       = \033[0m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@
	@echo "$(GREEN)✅ Build complete: $(NAME)$(RESET)"

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiled:$(RESET) $<"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -s -C $(MLX_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)🧹 Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(RED)🗑️  All cleaned up.$(RESET)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
