# Variables
NAME = libftsnprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Files
SRCS = $(SRC_DIR)/ft_snprintf_core.c \
       $(SRC_DIR)/ft_snprintf_format_info.c \
       $(SRC_DIR)/ft_snprintf_format_parsing.c \
       $(SRC_DIR)/ft_snprintf_numeric_setup.c \
       $(SRC_DIR)/ft_snprintf_numeric_format.c \
	   $(SRC_DIR)/ft_snprtinf_string_precision.c \
       $(SRC_DIR)/ft_snprintf_padding.c \
	   $(SRC_DIR)/ft_snprtinf_process_non_format_chars.c \
	   $(SRC_DIR)/ft_snprintf_parse_field_width.c \
	   $(SRC_DIR)/ft_snprintf_parse_precision.c \
	   $(SRC_DIR)/ft_snprintf_format_numeric_arg.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/ft_utoa.c \
       $(SRC_DIR)/ft_itoa.c \
       $(SRC_DIR)/ft_itoa_base.c \
       $(SRC_DIR)/ft_buffer_utils.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS = $(INC_DIR)/ft_snprintf.h

# Test program
TEST_SRC = $(SRC_DIR)/main.c
TEST_OBJ = $(OBJ_DIR)/main.o
TEST_NAME = test_snprintf

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)

re: fclean all

$(TEST_OBJ): $(TEST_SRC) $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(TEST_NAME): $(TEST_OBJ) $(NAME)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ) -L. -l:$(NAME)

test: $(TEST_NAME)
	./$(TEST_NAME)


.PHONY: all clean fclean re test
.SILENT: