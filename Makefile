NAME        = cub3D

BUILD_DIR   = build
INCLUDE_DIR = include
LIBFT_DIR   = library/libft
GNL_DIR     = library/gnl
MLX_DIR		= library/minilibx-linux

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd

SRCS = \
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

BONUS_SRCS = \
	bonus/main_bonus.c \
	bonus/game_bonus.c \
	bonus/mouse_rotation_bonus.c \
	bonus/collisions_bonus.c \
	bonus/player_movement_bonus.c \
	bonus/render_bonus.c \
	src/parsing/parse_file.c \
	src/parsing/parse_file_utils.c \
	src/parsing/parse_textures.c \
	src/parsing/parse_colors.c \
	src/parsing/parse_colors_utils.c \
	src/parsing/parse_map.c \
	src/parsing/validate_map.c \
	src/parsing/validate_map_utils.c \
	src/game/game_init.c \
	src/game/player/player_init.c \
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

OBJS = $(SRCS:src/%.c=$(BUILD_DIR)/%.o)

BONUS_OBJS_BONUS = $(BUILD_DIR)/bonus/main_bonus.o \
	$(BUILD_DIR)/bonus/game_bonus.o \
	$(BUILD_DIR)/bonus/mouse_rotation_bonus.o \
	$(BUILD_DIR)/bonus/collisions_bonus.o \
	$(BUILD_DIR)/bonus/player_movement_bonus.o \
	$(BUILD_DIR)/bonus/render_bonus.o

BONUS_OBJS_SRC = $(BUILD_DIR)/parsing/parse_file.o \
	$(BUILD_DIR)/parsing/parse_file_utils.o \
	$(BUILD_DIR)/parsing/parse_textures.o \
	$(BUILD_DIR)/parsing/parse_colors.o \
	$(BUILD_DIR)/parsing/parse_colors_utils.o \
	$(BUILD_DIR)/parsing/parse_map.o \
	$(BUILD_DIR)/parsing/validate_map.o \
	$(BUILD_DIR)/parsing/validate_map_utils.o \
	$(BUILD_DIR)/game/game_init.o \
	$(BUILD_DIR)/game/player/player_init.o \
	$(BUILD_DIR)/game/raycasting/draw_walls.o \
	$(BUILD_DIR)/game/raycasting/draw_pixel.o \
	$(BUILD_DIR)/game/raycasting/raycasting.o \
	$(BUILD_DIR)/utils/error.o \
	$(BUILD_DIR)/utils/free.o \
	$(BUILD_DIR)/utils/utils.o \
	$(BUILD_DIR)/utils/data_init.o

BONUS_OBJS = $(BONUS_OBJS_BONUS) $(BONUS_OBJS_SRC)

GNL_OBJS = $(GNL_SRCS:library/gnl/%.c=$(BUILD_DIR)/gnl/%.o)

RESET       = \033[0m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m

all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) $(MLX_FLAGS) -o $@
	@echo "$(GREEN)✅ Build complete: $(NAME)$(RESET)"

bonus: $(BONUS_OBJS) $(GNL_OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Bonus build complete: $(NAME)$(RESET)"

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiled:$(RESET) $<"

$(BUILD_DIR)/bonus/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiled:$(RESET) $<"

$(BUILD_DIR)/gnl/%.o: library/gnl/%.c
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
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "$(YELLOW)🧹 Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(RED)🗑️  All cleaned up.$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
