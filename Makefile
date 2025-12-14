NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I headers -I /opt/homebrew/opt/readline/includes

SRCS = core/main.c \
	   core/utils/error/free.c \
	   core/utils/error/error.c \
	   core/executions/builtin/cd.c \
	   core/utils/env/env_checks.c \
	   core/utils/built/cd_helper.c \
	   core/executions/builtin/env.c \
	   core/executions/builtin/pwd.c \
	   core/utils/env/env_updates.c \
	   core/utils/built/pwd_helper.c \
	   core/executions/builtin/export.c \
	   core/utils/string/list_helper.c \
	   core/utils/built/export_helper.c \
	   core/utils/string/string_basics.c \
	   core/utils/string/string_updater.c \
	   core/utils/string/string_searcher.c \
	   core/executions/initialization/list_to_array.c \
	   core/executions/initialization/initialize_env.c
OBJ_DIR = .obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
READLINE_FLAGS = -L /opt/homebrew/opt/readline/lib -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(READLINE_FLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

val: re
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --suppressions=$(PWD)/readline.supp ./minishell

test: re
	@git clone https://github.com/LucasKuhn/minishell_tester
	@cd minishell_tester && (./tester || true) && cd ..
	@rm -rf minishell_tester

.PHONY: all re clean fclean val readline.supp