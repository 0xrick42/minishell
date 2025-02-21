# Tokenization Process

## Overview
The tokenization component (`srcs/token/`) implements lexical analysis, converting raw input into a stream of meaningful tokens. This is the first step in command processing and sets the foundation for parsing and execution.

## Token Types

### Core Token Types
```c
typedef enum e_token_type {
    WORD,       // Commands, arguments, filenames
    GREAT,      // > output redirection
    GGREAT,     // >> append redirection
    LESS,       // < input redirection
    LLESS,      // << heredoc
    PIPE,       // | pipeline
} t_token_type;
```

### Token Structure
```c
typedef struct s_token {
    int             token_id;       // Unique identifier
    char            *token_name;    // Token content
    t_token_type    token_type;     // Token classification
    t_token_redir   token_redir;    // Redirection flag
    struct s_token  *next_token;    // Next token in list
} t_token;
```

## Implementation Details

### 1. Token Creation
- **Word Tokens**
  ```c
  bool ft_create_word_token(t_minishell *minishell, char *input);
  ```
  - Handles command names and arguments
  - Processes quoted strings
  - Manages word boundaries

- **Operator Tokens**
  ```c
  bool ft_create_pipe_token(t_minishell *minishell);
  bool ft_create_output_token(t_minishell *minishell);
  bool ft_create_append_token(t_minishell *minishell);
  bool ft_create_input_token(t_minishell *minishell);
  bool ft_create_hdoc_token(t_minishell *minishell);
  ```
  - Creates specific token types
  - Sets appropriate flags
  - Manages operator recognition

### 2. Token Processing
- Character-by-character analysis
- Quote handling
- Operator recognition
- Word boundary detection
- Error checking

### 3. Quote Handling
- Single quote preservation
- Double quote processing
- Escape sequence handling
- Quote matching validation

### 4. Error Detection
- Syntax validation
- Quote matching
- Invalid operator sequences
- Memory allocation failures

## Key Functions

### 1. Tokenization Control
```c
bool ft_tokenization(t_minishell *minishell, char *input, int i);
```
- Main tokenization loop
- Token type determination
- Error handling
- List management

### 2. Token Operations
```c
bool ft_pipe(t_minishell *minishell, int *i);
bool ft_great(t_minishell *minishell, int *i);
bool ft_ggreat(t_minishell *minishell, int *i);
bool ft_less(t_minishell *minishell, int *i);
bool ft_lless(t_minishell *minishell, int *i);
bool ft_word(t_minishell *minishell, char *input, int *i);
```
- Specific token handling
- Position tracking
- Error checking
- Memory management

### 3. Token Validation
```c
bool ft_token_order(t_minishell *minishell);
bool ft_check_pipe(t_minishell *minishell);
bool ft_check_redir(t_minishell *minishell);
```
- Syntax validation
- Token sequence checking
- Error reporting

## Memory Management

### 1. Allocation
- Token structure allocation
- Content duplication
- List management
- Error handling

### 2. Deallocation
```c
void ft_free_token_list(t_minishell *minishell);
```
- Complete list cleanup
- Memory leak prevention
- Error state handling

## Error Handling

### 1. Syntax Errors
- Invalid token sequences
- Unclosed quotes
- Invalid operators
- Missing arguments

### 2. Memory Errors
- Allocation failures
- Cleanup on error
- Resource management
- Error propagation

## Integration Points

### 1. Parser Interface
- Token list handoff
- Error communication
- Syntax validation
- State management

### 2. Expansion Interface
- Quote preservation
- Variable marking
- Word boundary marking
- Special character handling

## Examples

### 1. Basic Command
```bash
ls -l
```
Tokens:
1. WORD("ls")
2. WORD("-l")

### 2. Pipeline
```bash
echo "hello" | grep "o"
```
Tokens:
1. WORD("echo")
2. WORD("hello")
3. PIPE("|")
4. WORD("grep")
5. WORD("o")

### 3. Redirections
```bash
cat < input.txt > output.txt
```
Tokens:
1. WORD("cat")
2. LESS("<")
3. WORD("input.txt")
4. GREAT(">")
5. WORD("output.txt")

### 4. Heredoc
```bash
cat << EOF
```
Tokens:
1. WORD("cat")
2. LLESS("<<")
3. WORD("EOF") 