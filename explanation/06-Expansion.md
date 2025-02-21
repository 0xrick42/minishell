# Making Commands More Powerful (Expansion)

## What is Expansion?
When you type a command, the shell does some magic before running it. This magic is called "expansion". It's like the shell's search-and-replace feature!

## Types of Magic (Expansions)

### 1. Environment Variables ($VAR)
```bash
# Examples:
echo $HOME           # Shows your home folder
echo $USER           # Shows your username
echo $PATH           # Shows where programs are
echo ${NAME}         # Same as $NAME but clearer
```

How it works:
1. Shell sees a $ sign
2. Gets the variable name after it
3. Looks up the value
4. Replaces $NAME with its value

Code:
```c
char *expand_variables(char *str, t_minishell *minishell)
{
    char *result = NULL;
    size_t i = 0;
    
    while (str[i]) {
        if (str[i] == '$' && is_valid_var_char(str[i + 1]))
            add_variable_value(&result, get_var_name(&str[i + 1]), minishell);
        else
            add_char(&result, str[i]);
        i++;
    }
    return result;
}
```

### 2. Home Directory (~)
```bash
# Examples:
cd ~               # Go to your home
ls ~/Documents     # List your Documents
echo ~rick         # Show rick's home
```

How it works:
1. Shell sees ~ at start of word
2. If alone or followed by /, uses your home
3. If followed by username, uses that user's home
4. Replaces ~ with the full path

Code:
```c
char *expand_tilde(char *str, t_minishell *minishell)
{
    if (str[0] != '~')
        return strdup(str);
        
    if (!str[1] || str[1] == '/')
        return get_home_dir(minishell);
        
    return get_user_home(&str[1]);
}
```

### 3. Special Variables
```bash
# Examples:
echo $?            # Last command's status (0 = success)
echo $$            # Current shell's process ID
echo $!            # Last background job's process ID
echo $0            # Name of the shell
```

How it works:
1. Shell sees special $ pattern
2. Recognizes special character
3. Gets the special value
4. Replaces it in command

Code:
```c
char *expand_special(char special_char, t_minishell *minishell)
{
    switch (special_char) {
        case '?':
            return ft_itoa(minishell->last_status);
        case '$':
            return ft_itoa(getpid());
        case '!':
            return ft_itoa(minishell->last_background_pid);
        case '0':
            return strdup(minishell->shell_name);
        default:
            return strdup("");
    }
}
```

## How Quotes Work

### 1. Double Quotes (")
```bash
# Examples:
echo "Hello $USER"  # Variables work: Hello rick
echo "Path: $PATH"  # Variables work
echo "~"           # ~ doesn't work: prints ~
```

How it works:
- Variables ($) still work
- ~ doesn't work
- Spaces are kept as-is

### 2. Single Quotes (')
```bash
# Examples:
echo 'Hello $USER'  # Prints exactly: Hello $USER
echo '$PATH'       # Prints exactly: $PATH
echo '~'          # Prints exactly: ~
```

How it works:
- Everything is kept exactly as typed
- No expansions happen at all
- Great for passwords/special characters

## Common Problems and Solutions

### 1. Variable Problems
```bash
# Problem: Variable not set
echo $NOTSET       # Prints nothing
echo ${NOTSET}     # Prints nothing

# Solution: Use default value
echo ${NOTSET:-default}  # Prints: default
```

### 2. Quote Problems
```bash
# Problem: Nested quotes
echo "He said "hello""  # Error!

# Solution: Use different quotes
echo "He said 'hello'"  # Works!
```

### 3. Space Problems
```bash
# Problem: Spaces in variables
FILE="my file.txt"
cat $FILE          # Error: tries to open "my" and "file.txt"

# Solution: Use quotes
cat "$FILE"        # Works: opens "my file.txt"
```

## Try It Yourself!

```bash
# 1. Environment variables
echo "Hello $USER"         # Your username
echo "Home: $HOME"        # Your home folder
echo "Shell: $SHELL"      # Your shell program

# 2. Special characters
echo "Last result: $?"    # 0 if previous worked
echo "Shell PID: $$"      # Shell's process number

# 3. Quotes
echo "Double $HOME"       # Expands $HOME
echo 'Single $HOME'      # Prints $HOME as-is
```

## Behind the Scenes

The expansion happens in this order:
1. Read the command
2. Find special characters ($, ~, quotes)
3. Do the right expansion
4. Remove quotes
5. Pass to command

For example:
```bash
echo "Hello $USER!"
```
1. Find ": start remembering spaces
2. Find $USER: get username (rick)
3. Find ": stop remembering spaces
4. Result: echo Hello rick!

## Code Structure

```c
// Main expansion function
char *expand_command(char *input, t_minishell *minishell)
{
    char *result = strdup(input);
    
    // 1. Handle quotes
    result = handle_quotes(result);
    if (!result)
        return NULL;
        
    // 2. Expand variables
    result = expand_variables(result, minishell);
    if (!result)
        return NULL;
        
    // 3. Handle tilde
    result = expand_tilde(result, minishell);
    if (!result)
        return NULL;
        
    return result;
}
``` 