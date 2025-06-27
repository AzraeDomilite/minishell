NAME=libft.a
OBJDIR=obj
PRINTF_DIR=printf

BASE_SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
ft_tolower.c ft_toupper.c \
ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
ft_putchar_fd.c ft_putstr_fd.c ft_strcpy.c ft_realloc.c
BASE_OBJECTS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(BASE_SOURCES)))

ADDITIONAL_SOURCES = ft_atol.c ft_htol.c ft_isspace.c ft_is_int_str.c ft_is_hex_str.c ft_cancel_newline_at_end.c \
set.c ft_strcmp.c ft_isblank.c ft_remove_brackets.c ft_ptr_substr.c ft_quotes.c ft_str_only_spaces.c \
ft_lstremove.c ft_lstsub.c ft_listfind.c ft_remove_quotes.c ft_strip.c ft_remove_last_backslash.c ft_strend.c debug.c
#ft_strstr_outside.c
ADDITIONAL_OBJECTS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(ADDITIONAL_SOURCES)))

GNL_SOURCES = get_next_line.c ft_stpcpy.c ft_join_list_to_str.c
GNL_OBJECTS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(GNL_SOURCES)))

PRINTF_SOURCES := ft_printf.c inner_length.c output_general.c output_general2.c \
output_hex_int_ptr.c output_str_char.c parse_format_str.c split_format_str.c free_spec.c
PRINTF_SOURCES := $(addprefix $(PRINTF_DIR)/, $(PRINTF_SOURCES))
PRINTF_OBJECTS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(PRINTF_SOURCES:$(PRINTF_DIR)/%.c=%.o)))

CC=gcc
CFLAGS=-Wextra -Werror -Wall
OBJECTS=$(BASE_OBJECTS) $(ADDITIONAL_OBJECTS) $(GNL_OBJECTS) $(PRINTF_OBJECTS)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJECTS)
	@ar rcs $@ $(OBJECTS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(PRINTF_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $< -I$(PRINTF_DIR) -I.

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(OBJDIR)
