# Shell Overview

## Shell Architecture

The minishell project implements a basic command-line interpreter with a structure similar to bash but with simplified functionality. The shell follows this general workflow:

1. **Display prompt and read input**
2. **Process the input**:
   - Tokenize (break into individual components)
   - Parse tokens into command structures
   - Expand environment variables
3. **Execute the commands**
4. **Wait for command completion**
5. **Return to step 1**

## Core Data Structures

### `t_minishell` - Main Shell Structure

```c
typedef struct s_minishell
{
    t_token         *token_list;   // List of tokens from current command
    t_envar         *env_list;     // List of environment variables
    t_cmd           *cmd_list;     // List of commands to execute
    int             exit_status;   // Status of the last executed command
} t_minishell;
```

This is the central structure that holds all shell state. It contains:
- The list of tokens after lexical analysis
- The environment variable list
- The command list after parsing
- The exit status of the last command

### `t_token` - Token Structure

```c
typedef struct s_token
{
    int             token_id;       // Unique identifier
    char            *token_name;    // Actual text content
    t_token_type    token_type;     // Type (WORD, PIPE, GREAT, etc.)
    t_token_redir   token_redir;    // Is it a redirection?
    struct s_token  *next_token;    // Next token in list
} t_token;
```

Tokens represent the individual "words" and operators in the command, such as:
- Command names and arguments
- Pipes (|)
- Redirection operators (>, >>, <, <<)

### `t_cmd` - Command Structure

```c
typedef struct s_cmd
{
    char           *cmd_name;       // Name of the command
    char           **cmd_args;      // Array of arguments
    struct s_cmd   *next_cmd;       // Next command in pipeline
} t_cmd;
```

This structure represents a single command with its arguments. Multiple commands can be linked together to form a pipeline.

### `t_envar` - Environment Variable Structure

```c
typedef struct s_envar
{
    char           *key;           // Variable name
    char           *value;         // Variable value
    struct s_envar *next;          // Next variable in list
} t_envar;
```

This structure stores environment variables as key-value pairs.

## Main Shell Loop

The shell's main loop is implemented in `main.c`. Here's the simplified flow:

```c
int main(int ac, char **av, char **envp)
{
    t_minishell *minishell;
    char *input;
    
    // Initialize shell data
    minishell = malloc(sizeof(t_minishell));
    minishell->token_list = NULL;
    minishell->env_list = NULL;
    minishell->cmd_list = NULL;
    
    // Create environment variable list
    ft_envar_list(envp, minishell);
    
    // Main shell loop
    while (1)
    {
        // Display prompt and read input
        input = readline("minishell$ ");
        if (!input)
            continue;
            
        // Add to history
        add_history(input);
        
        // Process input (tokenize)
        if (!ft_parsing(minishell, input))
        {
            ft_free_token_list(minishell);
            free(input);
            continue;
        }
        
        // Create command structures
        ft_free_token_list(minishell);
        if (!ft_cmd_struct(input, minishell))
        {
            // Handle error
            free(input);
            continue;
        }
        
        // Execute commands (not fully implemented yet)
        
        // Clean up
        free(input);
    }
    
    // Clean up and exit
    rl_clear_history();
    return (0);
}
```

## Current Implementation Status

### Implemented:
- Basic shell loop
- Input reading with readline
- Command history
- Tokenization
- Command structure creation
- Environment variables handling
- Memory management

### Not Yet Implemented:
- Actual command execution
- Redirection handling
- Pipe implementation
- Signal handling

## Memory Management

The shell implements careful memory management:

1. **Allocation**: Each component (tokens, commands, etc.) is dynamically allocated
2. **Cleanup**: Each list has a corresponding cleanup function to free memory:
   - `ft_free_token_list` for tokens
   - `ft_free_cmd_list` for commands

## Next Steps

The next major component to implement is the execution engine, which will:
1. Execute commands using fork() and execve()
2. Implement redirection with file descriptors
3. Implement pipes
4. Handle signals properly 