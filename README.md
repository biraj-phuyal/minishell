# Minishell

A small Unix shell written in C as part of the 42 curriculum. The project recreates the core behavior of an interactive shell: reading commands, parsing shell syntax, expanding environment variables, executing builtins and external programs, handling pipes/redirections, and preserving expected signal behavior.

The focus of this implementation is not just command execution, but building the shell as a structured system with separate lexer, parser, expander, AST, execution, environment, and utility layers.

## Features

- Interactive prompt using GNU Readline
- Command history
- Lexing and parsing for shell operators:
  - pipes: `|`
  - input redirection: `<`
  - output redirection: `>`
  - append redirection: `>>`
  - heredocs: `<<`
- Quote handling for single and double quotes
- Environment variable expansion, including `$?`
- Builtin commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- External command execution through `PATH` lookup
- Multi-command pipelines
- Redirection setup and file descriptor restoration
- Heredoc processing with expansion rules
- Signal handling for interactive mode, child processes, and heredocs
- Environment stored and updated through an internal linked list

## Architecture

```text
core/
|-- main.c
|-- parse/
|   |-- lexer/      # Tokenizes raw input into words and operators
|   |-- syntax/     # Validates pipe and redirection syntax
|   |-- expander/   # Expands variables while respecting quote state
|   |-- parser/     # Builds command and pipeline structures
|   `-- ast/        # AST node creation and cleanup
|-- execution/
|   |-- builtins/   # Shell builtin implementations
|   |-- externals/  # PATH lookup, fork/exec, and pipeline execution
|   |-- heredoc/    # Heredoc input collection and expansion
|   |-- initialization/
|   `-- execute/    # Redirections, signals, and execution dispatch
`-- utils/          # String, memory, env, list, and output helpers
```

The shell follows a staged flow:

```text
readline input
    -> lexer
    -> syntax validation
    -> expansion
    -> parser / AST
    -> executor
    -> status propagation
```

This separation keeps parsing decisions independent from process execution, which makes the code easier to reason about and test.

## Build

**Linux users: please switch branches before compiling.**
```bash
git checkout for-linux
```

This project is built with `make`.
```bash
make
```

Run the shell:

```bash
./minishell
```

Clean generated objects and binary:

```bash
make fclean
```

Rebuild from scratch:

```bash
make re
```

## Readline Dependency

The Makefile is currently configured for Homebrew's Readline installation:

```make
-I /opt/homebrew/opt/readline/includes
-L /opt/homebrew/opt/readline/lib -lreadline -lncurses
```

If your Readline installation is elsewhere, update `INCLUDES` and `READLINE_FLAGS` in the `Makefile`.

## Validation

The repository includes a Valgrind target:

```bash
make val
```

There is also a tester target that builds the project, clones a public minishell tester, runs it, and removes it afterward:

```bash
make test
```

## Example Usage

```bash
minishell: echo "hello $USER"
hello biraj

minishell: export PROJECT=minishell
minishell: echo $PROJECT
minishell

minishell: cat << EOF | grep shell > result.txt
> minishell
> bash
> EOF
```

## Technical Highlights

- Uses an AST to represent simple commands and pipelines before execution.
- Preserves shell-like behavior for builtins that must affect parent process state, such as `cd`, `export`, `unset`, and `exit`.
- Tracks heredoc quote state to decide whether heredoc lines should be expanded.
- Converts the internal environment linked list into `envp` arrays when executing external programs.
- Handles common process lifecycle details: pipes, forks, `dup2`, descriptor cleanup, child status collection, and signal modes.
- Maintains strict compilation with `-Wall -Wextra -Werror`.

## Project Context

Minishell is a systems programming project from 42. It exercises low-level Unix concepts including process creation, file descriptors, signals, terminal input, parsing, memory management, and environment handling.
