# Builtins

## What are Builtins?

Builtins are commands that are implemented directly within the shell rather than being external executables. They have direct access to the shell's internal data structures and don't require creating a new process to run.

Minishell implements the following builtins:
1. `echo` - Display a line of text
2. `cd` - Change the current directory
3. `pwd` - Print the current working directory
4. `export` - Set environment variables
5. `unset` - Remove environment variables
6. `env` - Display all environment variables
7. `exit` - Exit the shell with an optional status code

## Implementation Overview

All builtin commands are implemented in the `srcs/builtins/` directory, with each command having its own source file. They follow a common function signature:

```c
int ft_builtin_name(t_minishell *minishell, char **args);
```

Where:
- `minishell` is a pointer to the shell's main structure
- `args` is an array of command arguments (including the command name)
- The return value is the exit status (0 for success, non-zero for failure)

## Builtin Implementations

### echo

The `echo` command displays its arguments to standard output.

**File**: `srcs/builtins/echo.c`

**Features**:
- Supports the `-n` option to suppress the trailing newline
- Handles multiple arguments

**Implementation**:

```c
int ft_echo(t_minishell *minishell, char **args)
{
    int i;
    int n_option;

    (void)minishell;
    i = 1;
    n_option = 0;
    
    if (args[i] && !ft_strncmp(args[i], "-n", 3))
    {
        n_option = 1;
        i++;
    }
    
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    
    if (!n_option)
        ft_putchar_fd('\n', 1);
        
    return (0);
}
```

### cd

The `cd` command changes the current working directory.

**File**: `srcs/builtins/cd.c`

**Features**:
- Changes to the home directory when called without arguments
- Supports relative and absolute paths
- Updates the PWD environment variable

**Implementation**:

```c
int ft_cd(t_minishell *minishell, char **args)
{
    char *path;

    if (!args[1])
    {
        path = ft_get_home_path(minishell);
        if (!path)
        {
            ft_putendl_fd("minishell: cd: HOME not set", 2);
            return (1);
        }
    }
    else
        path = args[1];
        
    if (chdir(path) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        return (1);
    }
    
    if (!ft_update_pwd(minishell))
        return (1);
        
    return (0);
}
```

### pwd

The `pwd` command prints the current working directory.

**File**: `srcs/builtins/pwd.c`

**Features**:
- Uses `getcwd()` to get the current directory
- Handles errors appropriately

**Implementation**:

```c
int ft_pwd(t_minishell *minishell, char **args)
{
    char cwd[PATH_MAX];

    (void)minishell;
    (void)args;
    
    if (!getcwd(cwd, PATH_MAX))
    {
        ft_putendl_fd("minishell: pwd: error retrieving current directory", 2);
        return (1);
    }
    
    ft_putendl_fd(cwd, 1);
    return (0);
}
```

### export

The `export` command sets or displays environment variables.

**File**: `srcs/builtins/export.c`

**Features**:
- Sets environment variables when given arguments
- Displays all variables in sorted order when called without arguments
- Supports variable assignments with and without equal signs

**Implementation**:

```c
int ft_export(t_minishell *minishell, char **args)
{
    int i;
    int status;

    status = 0;
    if (!args[1])
        return (ft_export_display(minishell));
        
    i = 1;
    while (args[i])
    {
        if (!ft_is_valid_identifier(args[i]))
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            status = 1;
        }
        else
            ft_export_var(minishell, args[i]);
        i++;
    }
    
    return (status);
}
```

### unset

The `unset` command removes environment variables.

**File**: `srcs/builtins/unset.c`

**Features**:
- Supports multiple variables to unset
- Handles invalid variable names

**Implementation**:

```c
int ft_unset(t_minishell *minishell, char **args)
{
    int i;
    int status;

    status = 0;
    i = 1;
    
    while (args[i])
    {
        if (!ft_is_valid_identifier(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            status = 1;
        }
        else
            ft_unset_var(minishell, args[i]);
        i++;
    }
    
    return (status);
}
```

### env

The `env` command displays all environment variables.

**File**: `srcs/builtins/env.c`

**Features**:
- Lists all environment variables
- Simple implementation that just iterates through the environment list

**Implementation**:

```c
int ft_env(t_minishell *minishell, char **args)
{
    t_envar *current;

    (void)args;
    current = minishell->env_list;
    
    while (current)
    {
        ft_putstr_fd(current->key, 1);
        ft_putchar_fd('=', 1);
        ft_putendl_fd(current->value, 1);
        current = current->next;
    }
    
    return (0);
}
```

### exit

The `exit` command exits the shell with an optional status code.

**File**: `srcs/builtins/exit.c`

**Features**:
- Exits the shell
- Supports an optional numeric status code
- Handles invalid status codes

**Implementation**:

```c
int ft_exit(t_minishell *minishell, char **args)
{
    long status;

    (void)minishell;
    
    if (!args[1])
        ft_clean_exit(0);
        
    if (!ft_is_numeric(args[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        ft_clean_exit(2);
    }
    
    status = ft_atoi(args[1]);
    
    if (args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        return (1);
    }
    
    ft_clean_exit(status % 256);
    return (0);
}
```

## Helper Functions

Several helper functions are used across multiple builtins:

### Environment Variable Handling

```c
// Find a variable by name
t_envar *ft_find_envar(t_minishell *minishell, char *key);

// Update an existing variable
void ft_update_envar(t_envar *var, char *new_value);

// Add a new variable
bool ft_add_envar(t_minishell *minishell, char *key, char *value);

// Remove a variable
void ft_remove_envar(t_minishell *minishell, char *key);
```

### Validation Functions

```c
// Check if a string is a valid identifier
int ft_is_valid_identifier(char *str);

// Check if a string is numeric
int ft_is_numeric(char *str);
```

## Current Status

All builtin commands are fully implemented and functional. The main limitation is that the execution engine that would route commands to these builtins has not been fully implemented yet. Currently, these functions can be called, but there's no mechanism to recognize a command as a builtin and execute it directly instead of via the normal command execution path. 