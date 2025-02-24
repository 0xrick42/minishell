# Minishell Project Documentation

## Project Overview

Minishell is a simplified shell implementation similar to bash. This project involves creating a command-line interpreter that can handle command execution, pipes, redirections, environment variables, and more.

## Current Implementation Status

### ✅ Implemented Features

1. **Basic Shell Structure**
   - Command prompt with readline integration
   - Command history using add_history
   - Main shell loop

2. **Tokenization**
   - Lexical analysis for parsing input into tokens
   - Support for different token types:
     - WORD (commands, arguments, filenames)
     - PIPE (|)
     - GREAT (>)
     - GGREAT (>>)
     - LESS (<)
     - LLESS (<<)
   - Handling of quotes in tokens
   - Syntax validation for proper token order

3. **Parsing**
   - Parsing tokens into command structures
   - Command list creation
   - Handling special characters and quotes

4. **Environment Variables**
   - Storage and management of environment variables
   - Environment variable list creation from envp

5. **Builtins**
   - `echo` - Echo arguments to standard output with -n option support
   - `cd` - Change directory with support for relative and absolute paths
   - `pwd` - Print working directory
   - `export` - Set environment variables
   - `unset` - Unset environment variables
   - `env` - Display environment variables
   - `exit` - Exit the shell with optional status code

6. **Variable Expansion**
   - Basic expansion of environment variables
   - Handling of $ syntax

### ❌ Missing Features

1. **Command Execution**
   - No implementation of execve for running external commands
   - No PATH variable resolution for finding executables
   - No fork() implementation for creating child processes

2. **Redirection Handling**
   - While tokens for redirections are recognized, there's no implementation of:
     - File descriptor manipulation (dup2)
     - File opening/closing for redirections
     - Actual I/O redirection logic

3. **Pipe Implementation**
   - While pipe tokens are recognized, there's no implementation of:
     - Pipe creation (pipe())
     - Process creation for piped commands
     - Connecting commands with pipes

4. **Signal Handling**
   - No implementation for:
     - Ctrl+C (SIGINT)
     - Ctrl+D (EOF)
     - Ctrl+\ (SIGQUIT)

5. **Heredoc Implementation**
   - While heredoc tokens (<<) are recognized, there's no implementation of:
     - Reading heredoc content
     - Setting up heredoc as input

## Documentation Structure

This documentation is organized into the following sections:

1. [**Shell Overview**](01-Shell-Overview.md) - General structure and workflow
2. [**Tokenization**](02-Tokenization.md) - Breaking input into tokens
3. [**Parsing**](03-Parsing.md) - Creating command structures
4. [**Builtins**](04-Builtins.md) - Built-in command implementation
5. [**Environment**](05-Environment.md) - Environment variable handling
6. [**To Be Implemented**](06-To-Be-Implemented.md) - Detailed guide for remaining features

## Project Structure

- `srcs/` - Source code directory
  - `main.c` - Main shell loop
  - `builtins/` - Built-in command implementations
  - `token/` - Tokenization logic
  - `parse/` - Command parsing
  - `expand/` - Variable expansion
  - `exec/` - Command execution (partially implemented)
  - `signal/` - Signal handling (not implemented)
  - `clean/` - Memory cleanup functions
  - `utils/` - Utility functions

- `includes/` - Header files
  - `minishell.h` - Main header with structures and prototypes
  - `define.h` - Constants and enumerations
  - `builtins.h` - Built-in command prototypes
  - `expand.h` - Expansion related prototypes

- `libft/` - Custom library with utility functions 