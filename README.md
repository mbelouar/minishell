# minishell

A small Unix shell written in C, modeled on **bash**. Built as part of the 42 / 1337 common core.

minishell reads a command line, splits it into tokens, expands variables, then runs the commands. Commands can be connected with pipes and redirections, and it handles signals the same way an interactive bash does.

```
friw-kriw@ echo "Hello $USER" | tr a-z A-Z > out.txt
friw-kriw@ cat << EOF | wc -l
> line one
> line two
> EOF
       2
friw-kriw@ echo $?
0
```

## Features

- Interactive prompt with history (GNU Readline)
- Run programs found through `PATH`, or by relative or absolute path
- Pipes: `cmd1 | cmd2 | cmd3`
- Redirections:
  - `<` input
  - `>` output (truncate)
  - `>>` output (append)
  - `<<` here-document with a delimiter
- Single quotes `'...'` (no expansion) and double quotes `"..."` (expands `$`)
- Environment variable expansion: `$VAR` and `$?` (last exit status)
- Signals like bash:
  - `Ctrl-C` shows a new prompt
  - `Ctrl-D` exits the shell
  - `Ctrl-\` does nothing at the prompt
- Built-in commands:

| Built-in | Behavior |
|---|---|
| `echo` | Prints its arguments, supports `-n` |
| `cd` | Changes directory (relative or absolute path) |
| `pwd` | Prints the current directory |
| `export` | Sets environment variables, or lists them with no arguments |
| `unset` | Removes environment variables |
| `env` | Prints the environment |
| `exit` | Exits the shell with an optional status code |

## How it works

```
input line ──▶ tokenizer ──▶ analyzer ──▶ expander ──▶ executor
               (srcs/parser)  (srcs/analylizer)  (srcs/expand)  (srcs/execution)
```

1. **Tokenizer** splits the line into a linked list of tokens, each with a type: command, built-in, pipe, `<`, `>`, `>>` or `<<`. It respects quotes while splitting.
2. **Analyzer** checks the syntax, for example unclosed quotes, a pipe with nothing after it, a redirection with no file, or unsupported `;` and `&`.
3. **Expander** replaces `$VAR` and `$?` and removes the quotes.
4. **Executor** creates the pipes, forks one child per command, sets up the redirections and here-docs, runs built-ins in the parent when there's no pipe, waits for the children, and stores the exit status.

```
.
├── main.c            # Prompt loop
├── minishell.h
├── libft/            # Our own C standard library functions
└── srcs/
    ├── parser/       # Tokenizer and readline wrapper
    ├── analylizer/   # Syntax checks
    ├── expand/       # Variable expansion and quote removal
    ├── builtins/     # echo, cd, pwd, export, unset, env, exit
    └── execution/    # Pipes, redirections, here-docs, signals, errors
```

## Build and run

### Requirements

- macOS or Linux
- `cc` and `make`
- GNU Readline. On macOS, install it with `brew install readline`.

The Makefile expects Readline under the 1337 cluster path `/goinfre/mbelouar/homebrew/opt/readline`. On your own machine, change that path in the `Makefile` to the output of `brew --prefix readline`. On Linux, install `libreadline-dev` and remove the `-L`/`-I` flags.

```bash
git clone https://github.com/mbelouar/minishell.git
cd minishell
make
./minishell
```

| Command | Description |
|---|---|
| `make` | Build `libft` and `minishell` |
| `make clean` | Remove object files |
| `make fclean` | Also remove the binary |
| `make re` | Rebuild from scratch |

