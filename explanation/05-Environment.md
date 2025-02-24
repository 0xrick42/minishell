# Environment Variables

## What are Environment Variables?

Environment variables are dynamic values that can affect the behavior of processes running on a computer. In a shell, they store information like the user's home directory (`HOME`), the current working directory (`PWD`), the search path for executables (`PATH`), and many other system settings.

## Environment Variable Storage

In minishell, environment variables are stored in a linked list of `t_envar` structures:

```c
typedef struct s_envar
{
    char           *key;      // Variable name
    char           *value;    // Variable value
    struct s_envar *next;     // Next variable in list
} t_envar;
```

This structure allows for easy:
- Addition of new variables
- Removal of existing variables
- Modification of variable values
- Lookup of variable values by name

## Environment Variables Initialization

When the shell starts, it initializes its environment variables from the `envp` array passed to the main function:

```c
bool ft_envar_list(char **envp, t_minishell *minishell)
{
    int i;
    char *key;
    char *value;

    i = 0;
    while (envp[i])
    {
        key = ft_get_key(envp[i], '=');
        if (!key)
            return (false);
        value = ft_get_value(envp[i], ft_strlen(key) + 1);
        if (!value)
        {
            free(key);
            return (false);
        }
        if (!ft_add_envar(minishell, key, value))
        {
            free(key);
            free(value);
            return (false);
        }
        free(key);
        free(value);
        i++;
    }
    return (true);
}
```

This function:
1. Iterates through the `envp` array
2. Extracts the key and value from each entry
3. Adds them to the shell's environment variable list

## Environment Variable Operations

### Adding Variables

New variables are added with the `ft_add_envar` function:

```c
bool ft_add_envar(t_minishell *minishell, char *key, char *value)
{
    t_envar *new_var;
    t_envar *current;

    new_var = malloc(sizeof(t_envar));
    if (!new_var)
        return (false);
    new_var->key = ft_strdup(key);
    if (!new_var->key)
        return (free(new_var), false);
    new_var->value = ft_strdup(value);
    if (!new_var->value)
        return (free(new_var->key), free(new_var), false);
    new_var->next = NULL;

    if (!minishell->env_list)
    {
        minishell->env_list = new_var;
        return (true);
    }
    current = minishell->env_list;
    while (current->next)
        current = current->next;
    current->next = new_var;
    return (true);
}
```

### Finding Variables

Variables are looked up by name:

```c
t_envar *ft_find_envar(t_minishell *minishell, char *key)
{
    t_envar *current;

    current = minishell->env_list;
    while (current)
    {
        if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}
```

### Updating Variables

Existing variables can be updated:

```c
void ft_update_envar(t_envar *var, char *new_value)
{
    free(var->value);
    var->value = ft_strdup(new_value);
}
```

### Removing Variables

Variables can be removed from the environment:

```c
void ft_remove_envar(t_minishell *minishell, char *key)
{
    t_envar *current;
    t_envar *prev;

    if (!minishell->env_list)
        return;

    current = minishell->env_list;
    if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
    {
        minishell->env_list = current->next;
        free(current->key);
        free(current->value);
        free(current);
        return;
    }

    prev = current;
    current = current->next;
    while (current)
    {
        if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
        {
            prev->next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
```

## Variable Expansion

Variable expansion is the process of replacing variable references (like `$HOME`) with their values. This is a key part of shell functionality.

### Basic Variable Expansion

The minishell has implemented basic variable expansion in the `srcs/expand/` directory:

```c
char *ft_expand_var(char *str, t_minishell *minishell)
{
    char *result;
    char *var_name;
    char *var_value;
    int i;
    int j;

    // Allocate result string buffer
    result = malloc(ft_strlen(str) * 2);
    if (!result)
        return (NULL);

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '$' && ft_isalpha(str[i + 1]))
        {
            // Extract variable name
            var_name = ft_extract_var_name(str + i + 1);
            if (!var_name)
                return (free(result), NULL);

            // Get variable value
            var_value = ft_get_env_value(minishell, var_name);
            
            // Copy value to result
            if (var_value)
            {
                ft_strlcpy(result + j, var_value, ft_strlen(var_value) + 1);
                j += ft_strlen(var_value);
            }
            
            // Skip the variable name
            i += ft_strlen(var_name) + 1;
            free(var_name);
        }
        else
        {
            // Copy regular character
            result[j++] = str[i++];
        }
    }
    
    result[j] = '\0';
    return (result);
}
```

### Special Variable Handling

The implementation also handles special variables:

1. `$?` - The exit status of the most recent command
2. `$$` - The process ID of the shell
3. Variables in quotes (expanding in double quotes but not in single quotes)

## Current Status and Limitations

The environment variable handling is implemented and functional:
- Basic environment initialization
- Variable lookup, addition, update, removal
- Simple variable expansion

However, there are some limitations:
- No support for complex variable expansions (like `${var:-default}`)
- Limited handling of special cases
- No support for local shell variables (separate from environment variables)

The next steps would be to enhance variable expansion with more advanced features and better handling of edge cases. 