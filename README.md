*This project has been created as part of the 42 curriculum by esaleh.*

# Pipex

## Description
Pipex reproduces basic shell pipeline behavior for two commands:

```
< infile cmd1 | cmd2 > outfile
```

It creates a pipe, forks two children, wires file descriptors with `dup2`, resolves command paths from `PATH`, and executes each command with `execve`. The program exits with the status of the second command, matching typical shell behavior.

## Instructions

### Build
```
make
```

### Run
```
./pipex infile "cmd1" "cmd2" outfile
```

### Clean
```
make clean
make fclean
make re
```

## Resources
- `man pipe`, `man fork`, `man dup2`, `man execve`, `man waitpid`
- GNU Bash manual: pipelines and redirections
- 42 Pipex subject PDF (project specification)

### AI usage (consulting)
- Used AI for brief explanations of POSIX behaviors (pipes, forks, `dup2`, `execve`).
- Used AI to sanity-check edge cases and error codes (e.g., 126/127) against shell behavior.
- Used AI to refine README wording and organization.
