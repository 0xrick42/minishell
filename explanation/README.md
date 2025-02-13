# Minishell Project Explanation

## Project Overview
This project is a simplified shell implementation that handles command execution, pipes, redirections, environment variables, and built-in commands.

## Code Structure and Flow

### 1. Input Processing and Readline
- **Main Loop (`main.c`)**
  - Uses readline to get user input
  - Handles basic input validation
  - Manages command history

### 2. Lexical Analysis (Tokenization)
- **Quote Handling (`ft_split_quotes.c` and utils)**
  - `ft_split_quotes`: Splits input while respecting quotes
  - `ft_get_quoted_word`: Extracts quoted content
  - `ft_get_normal_word`: Handles non-quoted content

- **Token Creation (`create_tokens.c` and utils)**
  - `ft_tokenization`: Main tokenization function
  - Creates different token types:
    - WORD (command names and arguments)
    - GREAT (>), GGREAT (>>)
    - LESS (<), LLESS (<<)
    - PIPE (|)

### 3. Parsing and Command Structure
- **Command List Creation (`cmd_list.c` and utils)**
  - `ft_cmd_struct`: Creates command structure from input
  - `ft_cmd_list`: Builds list of commands
  - `ft_create_cmd`: Creates individual command nodes

### 4. Environment Variable Handling
- **Environment Management (`envar.c`)**
  - `ft_envar_list`: Creates environment variable list
  - `ft_add_envar`: Adds new environment variables
  - `ft_get_env_value`: Retrieves environment variable values

### 5. Expansion
- **Variable Expansion (`expand.c` and utils)**
  - `ft_expand`: Main expansion function
  - `ft_expand_dollars`: Handles $ expansions
  - `ft_expand_var`: Expands individual variables

### 6. Built-in Commands
Implementation of shell built-in commands:
- `echo`: Display messages
- `cd`: Change directory
- `pwd`: Print working directory
- `export`: Set environment variables
- `unset`: Remove environment variables
- `env`: Display environment
- `exit`: Exit the shell

## Data Structures

### 1. Command Structure (`t_cmd`)
```c
typedef struct s_cmd
{
    char            *cmd_name;     // Command name
    char            **cmd_args;    // Command arguments
    struct s_cmd    *next_cmd;     // Next command in pipeline
} t_cmd;
```

### 2. Token Structure (`t_token`)
```c
typedef struct s_token
{
    int             token_id;      // Token identifier
    char            *token_name;   // Token content
    t_token_type    token_type;    // Token type (WORD, PIPE, etc.)
    t_token_redir   token_redir;   // Redirection type
    struct s_token  *next_token;   // Next token in list
} t_token;
```

### 3. Environment Variable Structure (`t_envar`)
```c
typedef struct s_envar
{
    char            *key;          // Variable name
    char            *value;        // Variable value
    struct s_envar  *next;        // Next environment variable
} t_envar;
```

## Function Call Flow

1. **Input Processing**
   ```
   main() → readline() → input validation
   ```

2. **Tokenization**
   ```
   ft_parsing() → ft_tokenization() → token creation functions
   ```

3. **Command Structure Creation**
   ```
   ft_cmd_struct() → ft_cmd_list() → ft_create_cmd()
   ```

4. **Expansion**
   ```
   ft_expand() → ft_expand_dollars() → ft_expand_var()
   ```

5. **Execution**
   ```
   execute_commands() → handle_redirections() → execute_single_command()
   ```

## Memory Management
- Each structure has its corresponding free function
- Memory is freed in reverse order of allocation
- Error handling includes proper cleanup

## Error Handling
- Return values indicate success/failure
- Error messages are descriptive
- Memory is properly freed on errors

## Future Improvements
1. Signal handling implementation
2. More robust error handling
3. Additional built-in commands
4. Enhanced command history
5. Job control features 