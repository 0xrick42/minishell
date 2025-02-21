# Shell's Own Commands (Builtins)

## What are Builtins?
Builtins are commands that are part of the shell itself. Unlike regular commands (like `ls` or `grep`), these don't create new processes - they run directly in the shell. Think of them as the shell's special abilities!

## Our Builtin Commands

### 1. `cd` - Change Directory
```bash
# Examples:
cd Documents           # Go to Documents folder
cd ..                 # Go up one folder
cd ~                  # Go to home folder
cd /home/user/Desktop # Go to specific folder
```

How it works:
1. Gets the new directory path
2. Checks if the directory exists and is accessible
3. Changes to that directory
4. Updates PWD (current directory) and OLDPWD (previous directory)

Code:
```c
int ft_cd(t_cmd *cmd, t_minishell *minishell)
{
    // cmd->cmd_args[0] is "cd"
    // cmd->cmd_args[1] is the directory to go to
    if (!cmd->cmd_args[1])
        return handle_cd_home(minishell);  // cd with no args goes home
    return change_directory(cmd->cmd_args[1], minishell);
}
```

### 2. `echo` - Print Text
```bash
# Examples:
echo hello world      # Prints: hello world
echo -n hello        # Prints: hello (no newline)
echo "quotes work"   # Prints: quotes work
```

How it works:
1. Checks for -n option (no newline at end)
2. Prints each argument with a space between
3. Adds newline at end (unless -n was used)

Code:
```c
int ft_echo(t_cmd *cmd)
{
    bool add_newline = true;
    int i = 1;

    if (cmd->cmd_args[1] && strcmp(cmd->cmd_args[1], "-n") == 0) {
        add_newline = false;
        i = 2;
    }
    
    while (cmd->cmd_args[i]) {
        printf("%s", cmd->cmd_args[i]);
        if (cmd->cmd_args[i + 1])
            printf(" ");
        i++;
    }
    
    if (add_newline)
        printf("\n");
    return 0;
}
```

### 3. `pwd` - Print Working Directory
```bash
# Example:
pwd                  # Prints: /home/user/Documents
```

How it works:
1. Gets current directory path
2. Prints it
3. Adds a newline

Code:
```c
int ft_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return 0;
    }
    return 1;
}
```

### 4. `export` - Set Environment Variables
```bash
# Examples:
export PATH=/usr/bin   # Set PATH
export NAME=Rick      # Set NAME
export               # Show all variables
```

How it works:
1. If no arguments: shows all variables
2. With arguments: sets each variable
3. Validates variable names (must start with letter/underscore)
4. Updates or adds to environment list

Code:
```c
int ft_export(t_cmd *cmd, t_minishell *minishell)
{
    // No args? Show all variables
    if (!cmd->cmd_args[1])
        return show_all_variables(minishell);

    // Process each argument
    for (int i = 1; cmd->cmd_args[i]; i++) {
        char *key, *value;
        if (parse_variable(cmd->cmd_args[i], &key, &value) == 0)
            set_environment_variable(minishell, key, value);
    }
    return 0;
}
```

### 5. `unset` - Remove Environment Variables
```bash
# Examples:
unset NAME          # Remove NAME variable
unset VAR1 VAR2    # Remove multiple variables
```

How it works:
1. Takes variable names as arguments
2. Checks if each exists
3. Removes them from environment list

Code:
```c
int ft_unset(t_cmd *cmd, t_minishell *minishell)
{
    for (int i = 1; cmd->cmd_args[i]; i++)
        remove_environment_variable(minishell, cmd->cmd_args[i]);
    return 0;
}
```

### 6. `env` - Show Environment Variables
```bash
# Example:
env                 # Shows all variables like:
                   # PATH=/usr/bin
                   # HOME=/home/user
```

How it works:
1. Gets environment list
2. Prints each variable and its value
3. One per line, in KEY=VALUE format

Code:
```c
int ft_env(t_minishell *minishell)
{
    t_envar *current = minishell->env_list;
    
    while (current) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return 0;
}
```

### 7. `exit` - Quit the Shell
```bash
# Examples:
exit               # Quit with last command's status
exit 42           # Quit with status 42
```

How it works:
1. Optional number argument sets exit status
2. Cleans up all shell resources
3. Exits the program

Code:
```c
int ft_exit(t_cmd *cmd, t_minishell *minishell)
{
    int status = minishell->last_status;
    
    if (cmd->cmd_args[1])
        status = ft_atoi(cmd->cmd_args[1]);
        
    cleanup_shell(minishell);
    exit(status);
}
```

## How Environment Variables Work

Environment variables are stored in a linked list:
```c
struct s_envar {
    char *key;           // Variable name (like "PATH")
    char *value;         // Variable value (like "/usr/bin")
    struct s_envar *next;// Next variable in list
};
```

Example list:
```
[HOME=/home/user] -> [PATH=/usr/bin] -> [USER=rick] -> NULL
```

## Common Problems and Solutions

### 1. cd Problems
- "No such file or directory": Check if folder exists
- "Permission denied": Check folder permissions
- Can't go back: OLDPWD not set, use absolute path

### 2. export Problems
- "Not a valid identifier": Variable name must start with letter/underscore
- Value not set: Make sure to use KEY=VALUE format
- Changes not visible: Export sets for current shell only

### 3. env/unset Problems
- Variable not found: Check spelling, case sensitive
- Can't remove variable: Some variables are read-only
- Changes temporary: Environment resets on new shell

## Testing Your Understanding

Try these commands:
```bash
# 1. Directory navigation
pwd                 # Where are you?
cd Documents        # Go to Documents
pwd                # Did it work?

# 2. Environment variables
export TEST=hello   # Set a variable
env | grep TEST     # Is it there?
echo $TEST         # Can you see it?
unset TEST         # Remove it
env | grep TEST     # Is it gone?

# 3. Echo practice
echo "Hello World"  # Basic echo
echo -n "No newline"; echo " here it is"  # See the difference?
``` 