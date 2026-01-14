# Pipex Architecture and Code Overview

This project implements the mandatory Pipex subject: emulate

```
< infile cmd1 | cmd2 > outfile
```

with proper piping, process setup, PATH lookup, and shell-like argument parsing.

## Layout

- `src/main.c`: entry point, process creation, pipe setup, exit status handling.
- `src/parse.c`: command-line tokenization with quotes and backslash escapes.
- `src/path.c`: resolve executable paths using `PATH` (with a safe default).
- `src/utils.c`: helpers for errors, freeing splits, and `execve` invocation.
- `include/pipex.h`: shared prototypes and includes.
- `Makefile`: build rules and libft integration.

## Data Flow

1) The parent process creates a pipe.
2) First child redirects `infile` to `STDIN` and pipe write end to `STDOUT`, then execs `cmd1`.
3) Second child redirects pipe read end to `STDIN` and `outfile` to `STDOUT`, then execs `cmd2`.
4) Parent closes pipe fds and waits; program returns cmd2’s exit status when available.

## Core Components

### `main.c`

- Validates `argc == 5`.
- Calls `pipe()` and `fork()` twice.
- Each child handles its own `dup2()` and then `exec_cmd()`.
- Parent waits for both children and returns the exit code of cmd2 when it exits normally.

### `parse.c`

Implements a lightweight shell-style tokenizer:

- Splits on spaces and tabs.
- Supports single and double quotes to keep spaces inside a token.
- Supports backslash escapes outside quotes and inside double quotes.
- Strips quotes from the resulting arguments (matching shell behavior for exec).

This allows commands like:

```
sed "s/And/But/"
awk "{count++} END {printf \"count: %i\", count}"
```

### `path.c`

- If the command contains `/`, it is treated as a path.
- Otherwise, `PATH` is searched for an executable.
- When `envp` is missing or `PATH` is unset, a default path is used:
  `/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin`.
- Distinguishes “not found” vs “permission denied” to set exit code 127 vs 126.

### `utils.c`

- `error_exit()` prints `pipex: <msg>: <errno>` and exits.
- `free_split()` frees argv-like arrays.
- `exec_cmd()` parses args, resolves the executable, and calls `execve()`.
  It mirrors shell exit conventions:
  - 127 for command not found
  - 126 for permission denied

## Build

- The Makefile builds `pipex` and links against `../libft/libft.a`.
- Rebuild `libft` in the parent directory if needed.

## Usage

```
./pipex infile "cmd1 args" "cmd2 args" outfile
```

Example:

```
./pipex infile.txt 'sed "s/And/But/"' 'grep But' outfile.txt
```
