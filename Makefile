NAME=ft_ssl

CC=gcc
CFLAGS=-Wall -Werror -Wextra -g -MMD

SRC_DIR=src
BUILD=.build
INCLUDE=-Iinclude -I$(LIBFT_DIR)/include

SRC=$(shell find $(SRC_DIR) -name '*.c')
OBJ=$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
DEP=$(OBJ:%.o=%.d)

LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a

LIBS=-L$(LIBFT_DIR) -lft

all: create_dir $(NAME)

create_dir: | $(BUILD)

$(BUILD):
	@mkdir -p $(BUILD)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@if [ -d $(BUILD) ]; then rm -rf $(BUILD) && printf "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m\n"; fi
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@if [ -f $(NAME) ]; then rm -rf $(NAME) && printf "\033[1;31m\tDeleted: $(NAME)\033[0m\n"; fi
	@make --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEP)

.PHONY=all clean fclean re create_dir