# Pipex — Code Overview & Workflow (Defense Prep)

This document summarizes how the project works, how each stage flows, and how edge cases are handled. It’s designed for quick defense preparation.

## High‑Level Goal
Reproduce the shell behavior of:

```
< infile cmd1 | cmd2 > outfile
```

The program creates a pipe, forks two children, wires file descriptors with `dup2`, resolves command paths, and executes the commands.

## Program Flow (main.c)

1. **Argument check**
   - Expects 5 args: `./pipex infile "cmd1" "cmd2" outfile`.
   - Prints usage to `stderr` if count is wrong.

2. **Create pipe**
   - `pipe(pipefd)` provides `pipefd[0]` (read) and `pipefd[1]` (write).

3. **First fork (child_in)**
   - Opens `infile` for reading.
   - Redirects:
     - `infile` → `STDIN_FILENO`
     - `pipefd[1]` → `STDOUT_FILENO`
   - Closes unused fds.
   - Calls `exec_cmd(argv[2], envp)`.

4. **Second fork (child_out)**
   - Opens `outfile` with `O_CREAT | O_WRONLY | O_TRUNC`.
   - Redirects:
     - `pipefd[0]` → `STDIN_FILENO`
     - `outfile` → `STDOUT_FILENO`
   - Closes unused fds.
   - Calls `exec_cmd(argv[3], envp)`.

5. **Parent**
   - Closes both pipe ends.
   - Waits for both children; returns the **exit status of cmd2**.

## Command Execution (utils.c)

### `exec_cmd(cmd_str, envp)`
- Splits `cmd_str` into `args` via `split_cmd`.
- Resolves executable path using `get_cmd_path`.
- Runs `execve(path, args, envp)`.
- On failure, prints errors and exits with:
  - **126** if permission denied
  - **127** if command not found

### Error Handling
- `cmd_not_found` prints:
  - `pipex: <cmd>: command not found` for missing commands.
  - Uses `perror` for permission errors.
- `error_exit` prints `pipex: <msg>: <perror>` and exits with provided code.

## PATH Resolution (path.c)

### `get_cmd_path(cmd, envp, &perm_denied)`
- If `cmd` contains `/`, it is treated as a direct path:
  - Checks `F_OK` and `X_OK`.
- Otherwise:
  - Reads `PATH` from `envp` (or uses a default fallback).
  - Splits PATH by `:`.
  - Tries each directory + `/cmd` until found and executable.
  - Tracks permission denied via `perm_denied`.

## Argument Splitting (parse.c + split_cmd_core.c)

### Goal
Split a command string into argv‑style tokens, while respecting quotes.

Example:
```
"grep \"hello world\"" → ["grep", "hello world"]
```

### Key Helpers
- `skip_spaces`: move over whitespace.
- `token_end`: find the end of the next token, respecting quotes.
- `token_len`: compute length of a token without counting the quote chars.
- `copy_token`: copy token text into a new buffer, stripping quotes.

### `split_cmd`
- Counts tokens first.
- Allocates the `char **` array.
- Builds each token with proper quoting rules.

## Memory / Resource Management
- All allocated token arrays are freed via `free_split` on errors.
- File descriptors are closed in both children and parent after `dup2`.
- `execve` replaces process image; errors are handled before exit.

## Exit Codes Summary
- **1** for general system errors (open/pipe/fork/dup2).
- **126** permission denied for command execution.
- **127** command not found / exec failure.
- Program returns the exit status of **cmd2**.

## Common Defense Questions (Quick Answers)
- **Why fork twice?** To run cmd1 and cmd2 concurrently, connected by a pipe.
- **Why return cmd2 status?** Shell behavior: pipeline exit status is usually that of the last command.
- **What happens if PATH is missing?** A default PATH is used.
- **How do quotes work?** Quotes are removed, and spaces inside quotes are preserved in the same token.
- **Why `dup2` then close?** After `dup2`, the original fd is no longer needed.

## Files to Know
- `src/main.c` — core pipeline setup
- `src/utils.c` — exec, errors, free helpers
- `src/path.c` — PATH resolution
- `src/parse.c` — `split_cmd` entry
- `src/parse_helpers.c`, `src/split_cmd_core.c` — token parsing helpers

