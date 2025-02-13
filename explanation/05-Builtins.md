# Built-in Commands Implementation

## Overview

The built-in commands component (`srcs/builtins/`) implements shell commands that are executed directly by the shell rather than creating a new process. These commands are essential for shell operation and environment management.

## Built-in Commands List

### 1. cd (Change Directory)
```c
int ft_cd(t_cmd *cmd, t_minishell *minishell);
```
- Changes the current working directory
- Handles relative and absolute paths
- Supports `~` for home directory
- Updates PWD and OLDPWD environment variables

### 2. echo
```c
int ft_echo(t_cmd *cmd);
```
- Displays text to standard output
- Handles `-n` flag to suppress newline
- Processes escape sequences
- Handles quoted strings

### 3. pwd (Print Working Directory)
```c
int ft_pwd(void);
```
- Prints current working directory
- Uses getcwd() system call
- Handles symbolic links
- Returns appropriate error codes

### 4. export
```c
int ft_export(t_cmd *cmd, t_minishell *minishell);
```
- Sets environment variables
- Validates variable names
- Handles value assignments
- Maintains environment list

### 5. unset
```c
int ft_unset(t_cmd *cmd, t_minishell *minishell);
```
- Removes environment variables
- Validates variable names
- Updates environment list
- Handles multiple arguments

### 6. env
```c
int ft_env(t_minishell *minishell);
```
- Displays environment variables
- Shows variable assignments
- Handles formatting
- Sorts output alphabetically

### 7. exit
```c
int ft_exit(t_cmd *cmd, t_minishell *minishell);
```
- Terminates the shell
- Handles exit status
- Cleans up resources
- Supports numeric arguments

## Environment Variable Management

### Structure
```c
typedef struct s_envar {
    char            *key;           // Variable name
    char            *value;         // Variable value
    struct s_envar  *next;         // Next environment variable
} t_envar;
```

### Key Functions

1. **Environment List Management**
```c
// Add new environment variable
int add_env_var(t_minishell *minishell, char *key, char *value);

// Find environment variable
t_envar *find_env_var(t_minishell *minishell, char *key);

// Remove environment variable
int remove_env_var(t_minishell *minishell, char *key);
```

2. **Variable Processing**
```c
// Parse variable assignment
int parse_env_var(char *str, char **key, char **value);

// Validate variable name
int validate_var_name(char *name);
```

## Implementation Details

### 1. cd Command
- Handles special paths (., .., ~)
- Updates PWD and OLDPWD
- Handles directory access errors
- Supports relative/absolute paths

### 2. echo Command
- Processes command arguments
- Handles escape sequences
- Manages output formatting
- Supports -n flag

### 3. pwd Command
- Gets current directory path
- Handles symbolic links
- Manages error conditions
- Returns appropriate status

### 4. export Command
- Validates variable names
- Handles value assignments
- Updates environment list
- Maintains sorting order

### 5. unset Command
- Removes variables
- Validates input
- Updates environment
- Handles multiple arguments

### 6. env Command
- Lists environment variables
- Formats output
- Handles display options
- Maintains order

### 7. exit Command
- Processes exit status
- Cleans up resources
- Handles arguments
- Returns proper status

## Error Handling

Each built-in command implements proper error handling:
1. **Input Validation**
   - Check argument count
   - Validate parameter format
   - Handle invalid input

2. **Resource Management**
   - Memory allocation checks
   - File descriptor management
   - Environment list integrity

3. **Status Codes**
   - Proper exit status
   - Error reporting
   - Status propagation

## Integration

Built-in commands integrate with:
1. Main shell execution
2. Environment management
3. Directory handling
4. Process management

## Examples

### cd Command Usage
```bash
cd /path/to/dir    # Absolute path
cd ..              # Parent directory
cd ~              # Home directory
cd -              # Previous directory
```

### export Command Usage
```bash
export VAR=value   # Set variable
export VAR        # Export existing variable
export            # List exported variables
```

### echo Command Usage
```bash
echo Hello World   # Basic output
echo -n "Test"    # No newline
echo $VAR         # Variable expansion
```

## Performance Considerations

Built-in commands are optimized for:
- Quick execution
- Minimal memory usage
- Efficient environment access
- Resource management

## Security Measures

The implementation includes:
- Path validation
- Permission checking
- Environment safety
- Input sanitization 