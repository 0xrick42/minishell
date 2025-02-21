# Minishell Project Documentation

## Project Overview
This project implements a shell that handles command execution, pipes, redirections, environment variables, and built-in commands. It follows a modular design with clear separation of concerns.

## Code Structure

### 1. Input Processing (`main.c`)
- Uses readline for input handling
- Command history management
- Basic input validation
- Signal handling setup

### 2. Lexical Analysis (`srcs/token/`)
- **Token Creation**
  - Handles different token types (WORD, PIPE, GREAT, GGREAT, LESS, LLESS)
  - Quote-aware tokenization
  - Proper memory management
  - Error handling

- **Token Types**
  ```c
  typedef enum e_token_type {
      WORD,      // Commands, arguments, filenames
      GREAT,     // > redirection
      GGREAT,    // >> redirection
      LESS,      // < redirection
      LLESS,     // << heredoc
      PIPE       // | pipeline
  } t_token_type;
  ```

### 3. Parsing (`srcs/parse/`)
- Command structure creation
- Syntax validation
- Error detection
- Pipeline setup

### 4. Expansion (`srcs/expand/`)
- Environment variable expansion
- Quote handling
- Special parameter handling ($?, $$)
- Word splitting

### 5. Execution (`srcs/exec/`)
- Command execution
- Pipeline management
- Redirection handling
- Heredoc processing
- Process management

### 6. Built-in Commands (`srcs/builtins/`)
- cd: Directory navigation
- echo: Text output
- pwd: Current directory
- export: Environment variable management
- unset: Variable removal
- env: Environment display
- exit: Shell termination

## Key Data Structures

### Command Structure
```c
typedef struct s_cmd {
    char            *cmd_name;
    char            **cmd_args;
    struct s_cmd    *next_cmd;
} t_cmd;
```

### Token Structure
```c
typedef struct s_token {
    int             token_id;
    char            *token_name;
    t_token_type    token_type;
    t_token_redir   token_redir;
    struct s_token  *next_token;
} t_token;
```

### Environment Variable Structure
```c
typedef struct s_envar {
    char            *key;
    char            *value;
    struct s_envar  *next;
} t_envar;
```

## Processing Flow

1. **Input Processing**
   ```
   readline() → input validation → history management
   ```

2. **Tokenization**
   ```
   input → lexical analysis → token list creation
   ```

3. **Parsing**
   ```
   token list → syntax validation → command structure creation
   ```

4. **Expansion**
   ```
   command args → variable expansion → quote removal
   ```

5. **Execution**
   ```
   command structure → redirection setup → process management
   ```

## Error Handling
- Comprehensive error checking
- Memory leak prevention
- Proper cleanup on failures
- Descriptive error messages

## Memory Management
- Systematic allocation tracking
- Proper deallocation
- Resource cleanup
- Error recovery

## Features
- Command execution
- Pipeline support
- Redirection handling
- Environment management
- Signal handling
- History management

For detailed documentation on each component, see:
- [01-Overview.md](01-Overview.md)
- [02-Tokenization.md](02-Tokenization.md)
- [03-Parsing.md](03-Parsing.md)
- [04-Execution.md](04-Execution.md)
- [05-Builtins.md](05-Builtins.md)
- [06-Expansion.md](06-Expansion.md) 