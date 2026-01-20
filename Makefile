NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes -I /opt/homebrew/opt/readline/includes

SRCS = 	core/parse/lexer/token_utils.c \
		core/parse/lexer/lexer.c \
		core/parse/lexer/quote_removal.c \
		core/parse/lexer/token_utils_1.c \
		core/parse/lexer/quotes.c \
		core/parse/lexer/lexer_utils.c \
		core/parse/lexer/tokenizer.c \
		core/parse/parser/parse_pipeline.c \
		core/parse/parser/parse_redir.c \
		core/parse/parser/parse_utils.c \
		core/parse/parser/parse_cmd.c \
		core/parse/parser/parser.c \
		core/parse/expander/expander.c \
		core/parse/expander/expand_utils_2.c \
		core/parse/expander/quote_utils.c \
		core/parse/expander/expand_utils_1.c \
		core/parse/expander/expand_var.c \
		core/parse/ast/ast.c \
		core/parse/syntax/error.c \
		core/parse/syntax/syntax_check.c \
		core/utils/char/char_case.c \
		core/utils/char/char_checks.c \
		core/utils/memory/memory_search.c \
		core/utils/memory/memory_build.c \
		core/utils/memory/memory_ops.c \
		core/utils/builtins/builtin_helper.c \
		core/utils/builtins/echo_helper.c \
		core/utils/builtins/export_helper.c \
		core/utils/builtins/pwd_helper.c \
		core/utils/builtins/cd_helper.c \
		core/utils/env/env_checks.c \
		core/utils/env/get_values.c \
		core/utils/env/env_updates.c \
		core/utils/list/lst_basic.c \
		core/utils/list/lst_manage.c \
		core/utils/fd_print/put_fd.c \
		core/utils/fd_print/put_stdout.c \
		core/utils/string/string_split.c \
		core/utils/string/string_basics.c \
		core/utils/string/string_searcher.c \
		core/utils/string/string_compare.c \
		core/utils/string/string_build.c \
		core/utils/string/string_updater.c \
		core/utils/error/error.c \
		core/utils/error/free.c \
		core/utils/convert/string_convert.c \
		core/main.c \
		core/execution/externals/pipe_helper.c \
		core/execution/externals/execute_helper.c \
		core/execution/externals/execute_cmd_helper.c \
		core/execution/externals/execute_cmd.c \
		core/execution/externals/path.c \
		core/execution/externals/execute_pipe.c \
		core/execution/heredoc/heredoc_utils.c \
		core/execution/heredoc/heredoc.c \
		core/execution/heredoc/heredoc_helper.c \
		core/execution/initialization/list_to_array.c \
		core/execution/initialization/initialize_env.c \
		core/execution/builtins/exit.c \
		core/execution/builtins/unset.c \
		core/execution/builtins/env.c \
		core/execution/builtins/pwd.c \
		core/execution/builtins/export.c \
		core/execution/builtins/cd.c \
		core/execution/builtins/echo.c \
		core/execution/execute/execute_error.c \
		core/execution/execute/redir_helper.c \
		core/execution/execute/execute_utils.c \
		core/execution/execute/execute.c \
		core/execution/execute/program.c \
		core/execution/execute/signal_extra.c \
		core/execution/execute/signal_helper.c

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
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --trace-children=no --suppressions=$(PWD)/readline.supp ./minishell

test: re
	@git clone https://github.com/LucasKuhn/minishell_tester
	@cd minishell_tester && (./tester || true) && cd ..
	@rm -rf minishell_tester

.PHONY: all re clean fclean val readline.supp
