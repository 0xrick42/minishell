# Breaking Down Commands (Tokenization)

## What is Tokenization?
Tokenization is like breaking a sentence into words. For example, when you type:
```bash
echo "hello world" > output.txt
```
The shell needs to break this into pieces (tokens) to understand:
1. The command (`echo`)
2. The argument (`"hello world"`)
3. The redirection (`>`)
4. The file name (`output.txt`)

## How Does It Work?

### Step 1: Reading Characters
The shell reads your command character by character:
```c
bool ft_tokenization(t_minishell *minishell, char *input, int i)
```
This function:
1. Looks at each character
2. Decides what kind of token it's part of
3. Creates the right type of token
4. Moves to the next character

### Step 2: Identifying Token Types
The shell recognizes these types of tokens:
```c
typedef enum e_token_type {
    WORD,       // Commands, arguments, filenames (like "echo", "hello")
    GREAT,      // > (output to file)
    GGREAT,     // >> (append to file)
    LESS,       // < (input from file)
    LLESS,      // << (heredoc)
    PIPE        // | (pipe between commands)
} t_token_type;
```

### Step 3: Creating Tokens
Each token is stored in this structure:
```c
typedef struct s_token {
    int             token_id;       // Number to identify the token
    char            *token_name;    // The actual text ("echo", ">", etc.)
    t_token_type    token_type;     // What kind of token it is (from enum above)
    t_token_redir   token_redir;    // Is it a redirection? (NONE or REDIR)
    struct s_token  *next_token;    // Points to the next token in the list
} t_token;
```

### Step 4: Special Cases

#### Handling Quotes
When the shell sees quotes, it:
1. Recognizes the quote type (`'` or `"`)
2. Includes everything inside as one token
3. Checks for matching end quote
4. Removes the quotes when needed

Example:
```bash
echo "hello world"
```
Becomes:
- Token 1: `WORD("echo")`
- Token 2: `WORD("hello world")` (quotes preserved for now)

#### Handling Spaces
- Spaces separate tokens (unless in quotes)
- Multiple spaces are ignored
- Tabs and newlines count as spaces

#### Handling Operators
When the shell sees `>`, `<`, `|`, it:
1. Creates a special operator token
2. Sets the right type (GREAT, LESS, PIPE)
3. Marks redirections as REDIR

## The Functions That Do The Work

### 1. Creating Different Types of Tokens
```c
// For words (commands, arguments, filenames)
bool ft_create_word_token(t_minishell *minishell, char *input);

// For operators
bool ft_create_pipe_token(t_minishell *minishell);
bool ft_create_output_token(t_minishell *minishell);
bool ft_create_append_token(t_minishell *minishell);
bool ft_create_input_token(t_minishell *minishell);
bool ft_create_hdoc_token(t_minishell *minishell);
```

### 2. Processing Different Parts
```c
// Handle pipe character
bool ft_pipe(t_minishell *minishell, int *i);

// Handle > and >>
bool ft_great(t_minishell *minishell, int *i);
bool ft_ggreat(t_minishell *minishell, int *i);

// Handle < and <<
bool ft_less(t_minishell *minishell, int *i);
bool ft_lless(t_minishell *minishell, int *i);

// Handle words
bool ft_word(t_minishell *minishell, char *input, int *i);
```

### 3. Checking Everything is Correct
```c
// Make sure tokens are in the right order
bool ft_token_order(t_minishell *minishell);

// Check pipe usage is correct
bool ft_check_pipe(t_minishell *minishell);

// Check redirections are correct
bool ft_check_redir(t_minishell *minishell);
```

## Examples with Step-by-Step Breakdown

### 1. Simple Command
```bash
ls -l
```
Steps:
1. Read 'l': Start WORD token → "ls"
2. Read 's': Continue WORD token
3. Read space: End "ls" token
4. Read '-': Start WORD token → "-l"
5. Read 'l': Continue WORD token
6. End of input: End "-l" token

Result:
```
[WORD("ls")] -> [WORD("-l")]
```

### 2. Command with Redirection
```bash
echo hello > output.txt
```
Steps:
1. Read 'e': Start WORD token → "echo"
2. Read space: End "echo" token
3. Read 'h': Start WORD token → "hello"
4. Read space: End "hello" token
5. Read '>': Create GREAT token
6. Read space: End '>' token
7. Read 'o': Start WORD token → "output.txt"
8. End of input: End "output.txt" token

Result:
```
[WORD("echo")] -> [WORD("hello")] -> [GREAT(">")] -> [WORD("output.txt")]
```

### 3. Pipeline with Quotes
```bash
echo "hello world" | grep "o"
```
Steps:
1. Read 'e': Start WORD token → "echo"
2. Read space: End "echo" token
3. Read '"': Start quoted WORD token
4. Read until matching '"': Create "hello world" token
5. Read space: End quoted token
6. Read '|': Create PIPE token
7. Read space: End PIPE token
8. Read 'g': Start WORD token → "grep"
9. Read space: End "grep" token
10. Read '"': Start quoted WORD token
11. Read 'o': Continue quoted token
12. Read '"': End "o" token

Result:
```
[WORD("echo")] -> [WORD("hello world")] -> [PIPE("|")] -> 
[WORD("grep")] -> [WORD("o")]
```

## Error Checking

The shell checks for these errors:
1. **Quote Errors**
   - Unclosed quotes: `echo "hello`
   - Mismatched quotes: `echo "hello'`

2. **Operator Errors**
   - Multiple pipes: `ls |||| cat`
   - Missing file names: `echo > `
   - Wrong order: `> ls`

3. **Memory Errors**
   - Out of memory
   - Failed allocations

## Memory Management

The shell is careful with memory:
1. **Creating Tokens**
   - Allocates exact space needed
   - Copies strings carefully
   - Links tokens together

2. **Cleaning Up**
   ```c
   void ft_free_token_list(t_minishell *minishell);
   ```
   - Frees each token
   - Frees token contents
   - Sets pointers to NULL

## What's Next?

After tokenization:
1. The parser gets the token list
2. It checks the syntax is correct
3. It creates the command list
4. The executor runs the commands 