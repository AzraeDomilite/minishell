NAME = minishell

LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
FT_SNPRINTF_DIR=$(LIBFT_DIR)/ft_snprintf
FT_SNPRINTF=$(FT_SNPRINTF_DIR)/libftsnprintf.a
SRC_DIR=code
INCL_DIR=head
OBJ_DIR=obj

SUB_DEBUG=00_debug
SUB_READ_CMD=01_read_cmd_and_tokens
SUB_HISTORY=02_history
SUB_PARSE_TREE=03_parse_tree
SUB_EXECUTE_TREE=04_execute_tree
SUB_EXECUTE_CMD=05_execute_cmd
SUB_BUITINS=06_builtins
SUB_EXIT_MINISHELL=07_exit_minishell
SUB_SHELL=08_shell

SUB_SUB_CD=00_ft_cd
SUB_SUB_PWD=01_ft_pwd
SUB_SUB_ENV=02_ft_env
SUB_SUB_EXPORT=03_ft_export
SUB_SUB_UNSET=04_ft_unset
SUB_SUB_ECHO=05_ft_echo
SUB_SUB_EXIT=06_ft_exit

SOURCES:=main.c \
$(SUB_DEBUG)/print_tree.c $(SUB_DEBUG)/print_tokens.c \
$(SUB_READ_CMD)/readline_fork.c $(SUB_READ_CMD)/read_signals.c $(SUB_READ_CMD)/minishell_loop.c \
$(SUB_READ_CMD)/read_lines.c $(SUB_READ_CMD)/check_cmd.c $(SUB_READ_CMD)/tokenize_cmd.c $(SUB_READ_CMD)/read_heredocs.c \
$(SUB_HISTORY)/history.c $(SUB_HISTORY)/history_utils.c $(SUB_HISTORY)/update_history_file.c \
$(SUB_PARSE_TREE)/parse_tree.c $(SUB_PARSE_TREE)/parse_modifiers.c $(SUB_PARSE_TREE)/parse_tree_tokens_helper.c $(SUB_PARSE_TREE)/reduce_tree.c \
$(SUB_EXECUTE_TREE)/execute_tree.c $(SUB_EXECUTE_TREE)/execute_pipe_chain.c $(SUB_EXECUTE_TREE)/pipe.c \
$(SUB_EXECUTE_CMD)/execute_cmd.c $(SUB_EXECUTE_CMD)/parse_env.c $(SUB_EXECUTE_CMD)/error_exec_handlers.c \
$(SUB_EXECUTE_CMD)/execute_utils.c $(SUB_EXECUTE_CMD)/execve_args_tab.c $(SUB_EXECUTE_CMD)/var_expansion.c \
$(SUB_EXECUTE_CMD)/modifiers.c $(SUB_EXECUTE_CMD)/var_expansion_args.c $(SUB_EXECUTE_CMD)/var_expansion_utils.c \
$(SUB_EXECUTE_CMD)/wildcards.c $(SUB_EXECUTE_CMD)/wildcards_utils.c $(SUB_EXECUTE_CMD)/wildcards_utils2.c \
$(SUB_EXECUTE_CMD)/process_mods.c \
$(SUB_BUITINS)/$(SUB_SUB_CD)/ft_cd.c \
$(SUB_BUITINS)/$(SUB_SUB_PWD)/ft_pwd.c \
$(SUB_BUITINS)/$(SUB_SUB_ENV)/ft_env.c \
$(SUB_BUITINS)/$(SUB_SUB_EXPORT)/ft_export.c $(SUB_BUITINS)/$(SUB_SUB_EXPORT)/export_utils.c \
$(SUB_BUITINS)/$(SUB_SUB_EXPORT)/var_management.c \
$(SUB_BUITINS)/$(SUB_SUB_UNSET)/ft_unset.c \
$(SUB_BUITINS)/$(SUB_SUB_ECHO)/ft_echo.c \
$(SUB_BUITINS)/$(SUB_SUB_EXIT)/ft_exit.c \
$(SUB_EXIT_MINISHELL)/free.c $(SUB_EXIT_MINISHELL)/free2.c \
$(SUB_EXIT_MINISHELL)/free3.c $(SUB_EXIT_MINISHELL)/free4.c \
$(SUB_SHELL)/shell.c $(SUB_SHELL)/shell_utils.c 

SOURCES:=$(addprefix $(SRC_DIR)/, $(SOURCES))
OBJECTS=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES=-I$(LIBFT_DIR) -I$(FT_SNPRINTF_DIR)/include
LIBRARIES=-lreadline

CC=gcc
CFLAGS=-Wextra -Werror -Wall -g3 #-fsanitize=address

all: $(NAME)
	@echo "\033[32mBuild complete: $(NAME)\033[0m"

$(NAME): $(OBJ_DIR) $(OBJECTS) $(LIBFT) $(FT_SNPRINTF)
	@echo "\033[33mLinking $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBFT) $(FT_SNPRINTF) $(LIBRARIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) -I$(INCL_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(SUB_DEBUG)
	@mkdir -p $(OBJ_DIR)/$(SUB_READ_CMD)
	@mkdir -p $(OBJ_DIR)/$(SUB_HISTORY)
	@mkdir -p $(OBJ_DIR)/$(SUB_PARSE_TREE)
	@mkdir -p $(OBJ_DIR)/$(SUB_EXECUTE_TREE)
	@mkdir -p $(OBJ_DIR)/$(SUB_EXECUTE_CMD)
	@mkdir -p $(OBJ_DIR)/$(SUB_BUITINS)/$(SUB_SUB_CD)
	@mkdir -p $(OBJ_DIR)/$(SUB_BUITINS)/$(SUB_SUB_PWD)
	@mkdir -p $(OBJ_DIR)/$(SUB_BUITINS)/$(SUB_SUB_ENV)
	@mkdir -p $(OBJ_DIR)/$(SUB_BUITINS)/$(SUB_SUB_EXPORT)
	@mkdir -p $(OBJ_DIR)/$(SUB_BUITINS)/$(SUB_SUB_UNSET)
	@mkdir -p $(OBJ_DIR)/$(SUB_BUITINS)/$(SUB_SUB_ECHO)
	@mkdir -p $(OBJ_DIR)/$(SUB_BUITINS)/$(SUB_SUB_EXIT)
	@mkdir -p $(OBJ_DIR)/$(SUB_EXIT_MINISHELL)

$(LIBFT):
	@echo "\033[33mBuilding libft library...\033[0m"
	@make --no-print-directory -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)" CC="$(CC)"

$(FT_SNPRINTF):
	@echo "\033[33mBuilding ft_snprintf library...\033[0m"
	@make --no-print-directory -C $(FT_SNPRINTF_DIR) CFLAGS="$(CFLAGS)" CC="$(CC)"

valgrind:
	@echo "\033[33mRunning valgrind...\033[0m"
	@valgrind --leak-check=full --log-file=valgrind.log --show-leak-kinds=all --track-fds=all --default-suppressions=yes --suppressions=doc/valgrind.supp ./$(NAME)

doc:
	@echo "\033[33mGenerating documentation...\033[0m"
	@doxygen doc/Doxyfile

unused_functions:
	cflow -x code/*.c code/*/*.c code/*/*/*.c | awk -f test/find_unused_functions.awk

unused_functions_libft:
	cflow -x libft/*.c libft/printf/*.c code/*.c code/*/*.c code/*/*/*.c | awk -f test/find_unused_functions.awk


clean: clean_obj_dir
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@make --no-print-directory clean -C $(FT_SNPRINTF_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean_obj_dir
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	@make --no-print-directory fclean -C $(FT_SNPRINTF_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@rm -f debug.log
	@rm -f valgrind.log

clean_obj_dir: $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)/*
	@rmdir $(OBJ_DIR)

tester:
	@rm -rf ./minishell_tester/outfiles
	@rm -rf ./minishell_tester/mini_outfiles
	@rm -rf ./minishell_tester/bash_outfiles
	@cd minishell_tester && ./tester 2>/dev/null >&1 > tester_output

norm:
	@norminette code head
re: fclean all

.PHONY: clean fclean re all doc