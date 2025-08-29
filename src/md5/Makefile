NAME=md5

CC=gcc
CFLAGS=-Wall -Wextra -g -MMD

SRC_DIR=src
BUILD=.build
INCLUDE=-Iinclude

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
DEP=$(OBJ:%.o=%.d)

LIBS=$(addprefix -l, crypto)

all: create_dir $(NAME)

create_dir: | $(BUILD)

$(BUILD):
	@mkdir -p $(BUILD)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@if [ -d $(BUILD) ]; then rm -rf $(BUILD) && printf "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m\n"; fi

fclean:
	@make --no-print-directory clean
	@if [ -f $(NAME) ]; then rm -rf $(NAME) && printf "\033[1;31m\tDeleted: $(NAME)\033[0m\n"; fi

re:
	@make --no-print-directory fclean
	@make --no-print-directory all

-include $(DEP)

.PHONY=all clean fclean re create_dir