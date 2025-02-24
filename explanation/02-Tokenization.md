# Tokenization

## What is Tokenization?

Tokenization is the process of breaking the command input into individual "tokens" (words, operators, etc.) that can be processed by the shell. This is the first step in processing a command line.

For example, the command `echo "hello world" > output.txt` is broken into the following tokens:
- `echo` (command)
- `"hello world"` (quoted argument)
- `>` (redirection operator)
- `output.txt` (filename)

## Token Types in Minishell

The minishell recognizes these token types:

```c
typedef enum e_token_type
{
    WORD,   // Commands, arguments, filenames
    GREAT,  // Output redirection (>)
    GGREAT, // Append output redirection (>>)
    LESS,   // Input redirection (<)
    LLESS,  // Here document (<<)
    PIPE,   // Command pipeline (|)
} t_token_type;
```

Additionally, tokens can be marked as redirection operators:

```c
typedef enum e_token_redir
{
    NONE,   // Not a redirection
    REDIR,  // Is a redirection operator
} t_token_redir;
```

## Tokenization Process

### Main Tokenization Function

The main tokenizer function is `ft_tokenization()` in `srcs/token/token_ops2.c`:

```c
bool ft_tokenization(t_minishell *minishell, char *input, int i)
{
    while (input[i])
    {
        if (ft_space(input[i]))
            i++;
        else if (input[i] == '|')
        {
            if (!ft_handle_pipe_token(minishell, input, &i))
                return (false);
        }
        else if (input[i] == '>')
        {
            if (!ft_handle_great_token(minishell, input, &i))
                return (false);
        }
        else if (input[i] == '<')
        {
            if (!ft_handle_less_token(minishell, input, &i))
                return (false);
        }
        else if (!ft_word(minishell, input, &i))
            return (false);
    }
    return (true);
}
```

This function:
1. Iterates through each character of the input
2. Skips spaces
3. Identifies special characters (|, >, <) and handles them accordingly
4. Creates WORD tokens for everything else

### Handling Special Characters

#### Pipe Token (|)

When a pipe is encountered, `ft_handle_pipe_token()` creates a PIPE token:

```c
bool ft_create_pipe_token(t_minishell *minishell)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (false);
    new_token->token_name = ft_strdup("|");
    if (!new_token->token_name)
        return (free(new_token), false);
    new_token->token_type = PIPE;
    new_token->token_redir = NONE;
    new_token->next_token = NULL;
    ft_append_token(minishell, new_token);
    return (true);
}
```

#### Redirection Tokens (>, >>, <, <<)

For redirection operators, functions like `ft_create_output_token()` create the appropriate token:

```c
bool ft_create_output_token(t_minishell *minishell)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (false);
    new_token->token_name = ft_strdup(">");
    if (!new_token->token_name)
        return (free(new_token), false);
    new_token->token_type = GREAT;
    new_token->token_redir = REDIR;
    new_token->next_token = NULL;
    ft_append_token(minishell, new_token);
    return (true);
}
```

### Word Token Creation

For normal words (commands, arguments, filenames), `ft_create_word_token()` creates a WORD token:

```c
bool ft_create_word_token(t_minishell *minishell, char *input)
{
    t_token *new_token;
    int     len;

    len = ft_wordlen(input);
    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (false);
    new_token->token_id = ft_last_token_id(minishell) + 1;
    new_token->token_name = ft_substr(input, 0, len);
    new_token->token_type = WORD;
    new_token->token_redir = NONE;
    new_token->next_token = NULL;
    ft_append_token(minishell, new_token);
    return (true);
}
```

### Handling Quotes

The tokenizer preserves quotes during the tokenization stage:
- Single quotes ('): Treat everything inside as literal text
- Double quotes ("): Allow variable expansion inside, but treat as one token

The `ft_wordlen()` function calculates the length of a word, respecting quotes:

```c
int ft_wordlen(char *input)
{
    int i;
    int in_quote;
    char quote_type;

    i = 0;
    in_quote = 0;
    quote_type = 0;
    while (input[i] && (!ft_notword(input[i]) || in_quote))
    {
        if ((input[i] == '\'' || input[i] == '\"') && !in_quote)
        {
            in_quote = 1;
            quote_type = input[i];
        }
        else if (in_quote && input[i] == quote_type)
        {
            in_quote = 0;
            quote_type = 0;
        }
        i++;
    }
    return (i);
}
```

## Syntax Validation

After tokenization, syntax validation is performed:

```c
bool ft_token_order(t_minishell *minishell)
{
    if (!ft_check_pipe(minishell))
        return (false);
    if (!ft_check_redir(minishell))
        return (false);
    return (true);
}
```

This checks for common syntax errors like:
- Pipe at the beginning/end of a command
- Redirection without a filename
- Multiple consecutive operators

Examples of validations:

```c
bool ft_check_pipe(t_minishell *minishell)
{
    t_token *current;

    current = minishell->token_list;
    while (current)
    {
        if (current->token_type == PIPE)
        {
            if (current->token_id == 0 && !current->next_token)
                return (ft_token_error(current->token_name), false);
            else if (current->token_id == 0 || !current->next_token)
                return (ft_token_error(current->token_name), false);
            else if (current->next_token->token_type == PIPE)
                return (ft_token_error(current->token_name), false);
            else if (current->next_token->token_redir == REDIR)
                return (ft_token_error(current->token_name), false);
        }
        current = current->next_token;
    }
    return (true);
}
```

## Examples

### Simple Command

Input: `ls -l`

Tokens:
1. WORD("ls")
2. WORD("-l")

### Command with Redirection

Input: `echo hello > output.txt`

Tokens:
1. WORD("echo")
2. WORD("hello")
3. GREAT(">") - marked as REDIR
4. WORD("output.txt")

### Complex Command

Input: `cat file.txt | grep "error" > output.txt`

Tokens:
1. WORD("cat")
2. WORD("file.txt")
3. PIPE("|")
4. WORD("grep")
5. WORD("error") - quotes will be processed later
6. GREAT(">") - marked as REDIR
7. WORD("output.txt")

## Current Status and Limitations

The tokenization is fully implemented and handles:
- Basic command syntax
- Pipes and redirections
- Quotes (single and double)
- Basic syntax validation

However, there are some limitations:
- No handling of escape characters (\)
- Limited error reporting for syntax errors 