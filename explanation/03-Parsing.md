# Parsing

## What is Parsing?

Parsing is the process of taking the tokens produced by tokenization and organizing them into a structured command representation. After parsing, the shell has a clear understanding of:

- What commands to run
- What arguments to pass to each command
- How commands are connected (pipes)
- What redirections to set up

## Command Structure

The result of parsing is a linked list of command structures:

```c
typedef struct s_cmd
{
    char           *cmd_name;    // Name of the command to run
    char           **cmd_args;   // Array of command arguments
    struct s_cmd   *next_cmd;    // Next command in a pipeline
} t_cmd;
```

Each command node represents one command in the input, with its arguments. Multiple commands can be linked together to form a pipeline.

## Parsing Process

The parsing process in minishell involves these main steps:

1. **Tokenization** (covered in the previous section)
2. **Command structure creation**
3. **Argument processing**
4. **Pipeline setup**

### Main Parsing Function

The main parsing process starts with `ft_parsing()` in `srcs/parse/parsing.c`:

```c
bool ft_parsing(t_minishell *minishell, char *input)
{
    if (ft_not_handling(input))
        return (false);
    if (ft_unclosed_quotes(input))
        return (ft_error("unclosed quotes"), false);
    if (ft_only_spaces(input))
        return (false);
    if (!ft_tokenization(minishell, input, 0))
        return (false);
    if (!ft_token_order(minishell))
        return (false);
    return (true);
}
```

This function performs initial validation:
1. Checks for unsupported syntax
2. Checks for unclosed quotes
3. Skips inputs with only spaces
4. Performs tokenization
5. Validates token order

### Command Structure Creation

After tokenization, `ft_cmd_struct()` creates the command structure:

```c
bool ft_cmd_struct(char *input, t_minishell *minishell)
{
    char **cmd_cells;

    cmd_cells = ft_split_quotes(input, '|');
    if (!cmd_cells)
        return (false);
    if (!ft_create_cmd_list(minishell, cmd_cells))
    {
        ft_free_table(cmd_cells);
        return (false);
    }
    ft_free_table(cmd_cells);
    return (true);
}
```

This function:
1. Splits the input by pipe characters (|)
2. Creates a command node for each pipe-separated section
3. Frees temporary resources

### Command List Creation

The `ft_create_cmd_list()` function processes each pipe-separated command:

```c
bool ft_create_cmd_list(t_minishell *minishell, char **cmd_cells)
{
    int i;

    i = 0;
    while (cmd_cells[i])
    {
        if (!ft_cmd_list(cmd_cells[i], minishell))
        {
            ft_free_cmd_list(minishell->cmd_list);
            minishell->cmd_list = NULL;
            return (false);
        }
        i++;
    }
    return (true);
}
```

### Individual Command Processing

For each command section, `ft_cmd_list()` processes the arguments:

```c
bool ft_cmd_list(char *cmd_cell, t_minishell *minishell)
{
    char **cmd_args;

    cmd_args = ft_split_cmd_args(cmd_cell);
    if (!cmd_args)
        return (false);
    if (!ft_create_cmd(minishell, cmd_args))
    {
        ft_free_table(cmd_args);
        return (false);
    }
    return (true);
}
```

This function:
1. Splits the command into arguments
2. Creates a command node with those arguments

### Creating a Command Node

The `ft_create_cmd()` function creates a new command node:

```c
static bool ft_create_cmd(t_minishell *minishell, char **cmd_args)
{
    t_cmd *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return (false);
    ft_init_cmd(new_cmd);
    new_cmd->cmd_name = ft_strdup(cmd_args[0]);
    new_cmd->cmd_args = cmd_args;
    return (ft_add_cmd(minishell, new_cmd));
}
```

This function:
1. Allocates a new command structure
2. Sets the command name to the first argument
3. Stores all arguments in the structure
4. Adds the command to the command list

### Special Handling for Quotes

The `ft_split_quotes()` function is used to split the input while respecting quotes:

```c
char **ft_split_quotes(char const *s, char c)
{
    int     words;
    char    **split;

    if (!s)
        return (NULL);
    words = ft_count_words(s, c);
    split = malloc(sizeof(char *) * (words + 1));
    if (!split)
        return (NULL);
    if (!ft_fill_split(split, s, c, words))
    {
        ft_free_split(split, words);
        return (NULL);
    }
    return (split);
}
```

This ensures that quoted sections like `"hello world"` are treated as a single argument, even if they contain the delimiter character.

## Redirections in the Parser

Currently, the parser recognizes redirection tokens, but does not fully process them in the command structure. The tokenizer marks tokens like `>`, `>>`, `<`, and `<<` as redirection operators, but the execution engine needs to be implemented to actually process these redirections.

## Examples

### Simple Command

Input: `ls -l`

Parsing result:
- Command 1:
  - cmd_name: "ls"
  - cmd_args: ["ls", "-l", NULL]
  - next_cmd: NULL

### Pipeline

Input: `cat file.txt | grep "error"`

Parsing result:
- Command 1:
  - cmd_name: "cat"
  - cmd_args: ["cat", "file.txt", NULL]
  - next_cmd: pointer to Command 2
- Command 2:
  - cmd_name: "grep"
  - cmd_args: ["grep", "error", NULL]
  - next_cmd: NULL

### Command with Redirection

Input: `echo hello > output.txt`

Parsing result:
- Command 1:
  - cmd_name: "echo"
  - cmd_args: ["echo", "hello", ">", "output.txt", NULL]
  - next_cmd: NULL

Note: The redirection is currently included as part of the arguments. The execution engine will need to recognize and process these special arguments.

## Current Status and Limitations

The parser is implemented to:
- Create a command structure for each command
- Handle command arguments
- Set up command pipelines

However, there are limitations:
- Redirections are recognized as tokens but not fully processed
- No special handling for environment variable expansion in the parsing stage
- Limited error checking for invalid commands

The next step would be to implement the execution engine that can:
1. Recognize and process redirections in the command arguments
2. Set up pipes between commands
3. Execute the commands with proper file descriptors 