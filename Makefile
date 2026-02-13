NAME := ft_ssl

CC := gcc
CFLAGS := -Wall -Wextra -Werror

SRC_DIR := src
INC_DIR := include
BUILD_DIR := .build

CPPFLAGS := -I$(INC_DIR) -MMD -MP

# SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
SRCS := src/main.c src/hash/hash_main.c src/hash/process_inputs.c src/hash/print_hash.c src/hash/parse_inputs.c src/hash/algorithms/md5.c src/tools/list/list.c 
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)
