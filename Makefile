NAME        = cub3D

BUILD_DIR   = build
BUILD_BONUS = build_bonus
INCLUDE_DIR = include
BONUS_INC   = bonus/include
LIBFT_DIR   = library/libft
GNL_DIR     = library/gnl
MLX_DIR     = library/minilibx-linux

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

# ==================== MANDATORY ====================
MAND_CFLAGS = $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

MAND_SRCS = \
	src/main.c \
	src/parsing/parse_file.c \
	src/parsing/parse_file_utils.c \
	src/parsing/parse_textures.c \
	src/parsing/parse_colors.c \
	src/parsing/parse_colors_utils.c \
	src/parsing/parse_map.c \
	src/parsing/validate_map.c \
	src/parsing/validate_map_utils.c \
	src/game/game.c \
	src/game/game_init.c \
	src/game/player/player_init.c \
	src/game/player/player_move.c \
	src/game/player/player_move_utils.c \
	src/game/key_hook.c \
	src/game/render/render.c \
	src/game/raycasting/draw_walls.c \
	src/game/raycasting/draw_pixel.c \
	src/game/raycasting/raycasting.c \
	src/utils/error.c \
	src/utils/free.c \
	src/utils/utils.c \
	src/utils/data_init.c

GNL_SRCS = \
	library/gnl/get_next_line.c \
	library/gnl/get_next_line_utils.c

MAND_OBJS = $(MAND_SRCS:src/%.c=$(BUILD_DIR)/%.o)
GNL_OBJS  = $(GNL_SRCS:library/gnl/%.c=$(BUILD_DIR)/gnl/%.o)

# ==================== BONUS ====================
BONUS_CFLAGS = $(CFLAGS) -I$(BONUS_INC) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

BONUS_SRCS = \
	bonus/src/core/main_bonus.c \
	bonus/src/core/game_bonus.c \
	bonus/src/core/render_bonus.c \
	bonus/src/core/free_bonus.c \
	bonus/src/player/mouse_rotation_bonus.c \
	bonus/src/player/collisions_bonus.c \
	bonus/src/player/player_movement_bonus.c \
	bonus/src/ui/minimap_bonus.c \
	bonus/src/entities/door_bonus.c \
	bonus/src/entities/pokemon_bonus.c \
	bonus/src/entities/animation_bonus.c \
	bonus/src/entities/door_interaction_bonus.c \
	bonus/src/shared/parsing/parse_file.c \
	bonus/src/shared/parsing/parse_file_utils.c \
	bonus/src/shared/parsing/parse_textures.c \
	bonus/src/shared/parsing/parse_colors.c \
	bonus/src/shared/parsing/parse_colors_utils.c \
	bonus/src/shared/parsing/parse_map.c \
	bonus/src/shared/parsing/validate_map.c \
	bonus/src/shared/parsing/validate_map_utils.c \
	bonus/src/shared/game_init.c \
	bonus/src/shared/player_init.c \
	bonus/src/shared/raycasting/draw_walls.c \
	bonus/src/shared/raycasting/draw_pixel.c \
	bonus/src/shared/raycasting/raycasting.c \
	bonus/src/shared/utils/error.c \
	bonus/src/shared/utils/free.c \
	bonus/src/shared/utils/utils.c \
	bonus/src/shared/utils/data_init.c

BONUS_OBJS     = $(BONUS_SRCS:bonus/src/%.c=$(BUILD_BONUS)/%.o)
BONUS_GNL_OBJS = $(GNL_SRCS:library/gnl/%.c=$(BUILD_BONUS)/gnl/%.o)

# ==================== COLORS ====================
RESET       = \033[0m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m

# ==================== RULES ====================

all: $(NAME)

# Mandatory build - only uses src/ files
$(NAME): $(MAND_OBJS) $(GNL_OBJS) $(LIBFT) $(MLX)
	@$(CC) $(MAND_CFLAGS) $(MAND_OBJS) $(GNL_OBJS) $(LIBFT) $(MLX_FLAGS) -o $@
	@echo "$(GREEN)✅ Mandatory build complete: $(NAME)$(RESET)"

# Bonus build - only uses bonus/ files
bonus: $(BONUS_OBJS) $(BONUS_GNL_OBJS) $(LIBFT) $(MLX)
	@$(CC) $(BONUS_CFLAGS) $(BONUS_OBJS) $(BONUS_GNL_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Bonus build complete: $(NAME)$(RESET)"

# Mandatory object files
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(MAND_CFLAGS) -c $< -o $@
	@echo "$(BLUE)[MAND]$(RESET) Compiled: $<"

$(BUILD_DIR)/gnl/%.o: library/gnl/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(MAND_CFLAGS) -c $< -o $@
	@echo "$(BLUE)[MAND]$(RESET) Compiled: $<"

# Bonus object files
$(BUILD_BONUS)/%.o: bonus/src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(BONUS_CFLAGS) -c $< -o $@
	@echo "$(BLUE)[BONUS]$(RESET) Compiled: $<"

$(BUILD_BONUS)/gnl/%.o: library/gnl/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(BONUS_CFLAGS) -c $< -o $@
	@echo "$(BLUE)[BONUS]$(RESET) Compiled: $<"

# Libraries
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -s -C $(MLX_DIR)

# Cleanup
clean:
	@rm -rf $(BUILD_DIR) $(BUILD_BONUS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "$(YELLOW)🧹 Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(RED)🗑️  All cleaned up.$(RESET)"

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
