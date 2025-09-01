NAME=libft.a

AR=ar
ARFLAGS=rcs

CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -MMD

SRC_DIR=src
BUILD=.build
INCLUDE=-Iinclude

SRC=$(shell find $(SRC_DIR) -name '*.c')
OBJ=$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
DEP=$(OBJ:%.o=%.d)

all: create_dir $(NAME)

create_dir: | $(BUILD)

$(BUILD):
	@mkdir -p $(BUILD)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@if [ -d $(BUILD) ]; then rm -rf $(BUILD) && printf "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m\n"; fi

fclean: clean
	@if [ -f $(NAME) ]; then rm -rf $(NAME) && printf "\033[1;31m\tDeleted: $(NAME)\033[0m\n"; fi

re: fclean all

-include $(DEP)

.PHONY=all clean fclean re create_dir