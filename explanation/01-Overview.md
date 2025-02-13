# Minishell Project Overview

This document provides a comprehensive explanation of the minishell project, a simplified shell implementation that mimics basic functionalities of bash.

## Project Structure

The project is organized into several key components:

1. **Main Program** (`srcs/main.c`)
   - Entry point of the shell
   - Handles the main REPL (Read-Eval-Print Loop)
   - Initializes the shell environment
   - Manages command history

2. **Token Processing** (`srcs/token/`)
   - Lexical analysis of input
   - Token generation and classification
   - Handles different types of tokens (commands, arguments, operators)

3. **Parsing** (`srcs/parse/`)
   - Syntax analysis
   - Command structure generation
   - Error detection and handling

4. **Execution** (`srcs/exec/`)
   - Command execution logic
   - Process management
   - Pipeline handling

5. **Built-in Commands** (`srcs/builtins/`)
   - Implementation of shell built-in commands
   - Environment variable management

6. **Expansion** (`srcs/expand/`)
   - Variable expansion
   - Quote handling
   - Wildcard expansion

7. **Signal Handling** (`srcs/signal/`)
   - Custom signal handlers
   - Terminal control

8. **Utilities** (`srcs/utils/`)
   - Helper functions
   - Memory management
   - String manipulation

9. **Cleanup** (`srcs/clean/`)
   - Memory deallocation
   - Resource cleanup

## Core Components

### Command Line Interface
The shell provides an interactive command-line interface where users can:
- Enter commands
- Use command history
- Navigate using arrow keys
- Handle signals (Ctrl+C, Ctrl+D)

### Command Processing
1. **Lexical Analysis**
   - Breaks input into tokens
   - Identifies command boundaries
   - Handles quotes and special characters

2. **Parsing**
   - Creates command structures
   - Validates syntax
   - Prepares for execution

3. **Execution**
   - Executes built-in commands
   - Creates child processes
   - Manages pipelines
   - Handles redirections

### Features
- Environment variable management
- Built-in command implementation
- Pipeline support
- Signal handling
- Error management
- Memory leak prevention

## Implementation Details

Each component is designed to work independently while maintaining clear interfaces with other parts of the system. The project follows a modular approach, making it easier to maintain and extend functionality.

Further detailed documentation for each component can be found in their respective sections:
- [02-Tokenization.md](02-Tokenization.md)
- [03-Parsing.md](03-Parsing.md)
- [04-Execution.md](04-Execution.md)
- [05-Builtins.md](05-Builtins.md)
- [06-Expansion.md](06-Expansion.md) 