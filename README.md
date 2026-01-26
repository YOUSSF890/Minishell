*This project has been created as part of the 42 curriculum by ylagzoul.*

# Minishell

As beautiful as a shell

## Description

Minishell is a core project of the 42 curriculum where the goal is to build a simple Unix shell, similar to Bash.

The program displays a prompt, reads user input, parses commands, and executes them while handling processes, file descriptors, signals, and environment variables.

Through this project, I learned:

* How a shell works internally
* Process creation and management (fork, exec, wait)
* File descriptors, pipes, and redirections
* Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
* Environment variables and built-in commands

This project is a major step in understanding Unix systems and low-level programming in C.

---

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate the executable:

```bash
minishell
```

### Cleaning

Remove object files:

```bash
make clean
```

Remove object files and the executable:

```bash
make fclean
```

Recompile everything:

```bash
make re
```

### Execution

Run the shell with:

```bash
./minishell
```

---

## Features

### Mandatory Features

* Interactive prompt
* Command history (readline)
* Execute binaries using PATH or absolute/relative paths
* Built-in commands:

  * echo (-n)
  * cd
  * pwd
  * export
  * unset
  * env
  * exit
* Input and output redirections: <, >, <<, >>
* Pipes (|)
* Environment variable expansion ($VAR)
* Exit status expansion ($?)
* Signal handling:

  * Ctrl-C: new prompt
  * Ctrl-D: exit shell
  * Ctrl-\: ignored

### Bonus Features (if implemented)

* Logical operators: && and || with parentheses
* Wildcards (*) for the current directory

---

## Technical Choices

* Written entirely in C
* Uses a single global variable only for signal handling
* Parsing is separated from execution logic
* Strict memory management (no leaks in user code)
* Behavior aligned with Bash when required

---

## Resources

Documentation and references used:

* Bash manual
* Linux man pages (fork, execve, pipe, dup2, signal)
* GNU Readline documentation
* 42 intranet resources
---

## Author

Login: ylagzoul
School: 1337 (42 Network)
