# Tokenization Process

## Overview

The tokenization process is the first step in command processing, handled by the code in `srcs/token/`. This component is responsible for breaking down the user's input into meaningful tokens that can be processed by the parser.

## Token Types

The shell recognizes several types of tokens:
- Commands
- Arguments
- Operators (|, >, >>, <)
- Environment Variables
- Quotes (single and double)
- Special characters

## Implementation Details

### Token Structure
```c
typedef struct s_token {
    int         token_id;       // Unique identifier for the token
    char        *token_name;    // The actual content of the token
    int         token_type;     // Type of token (command, argument, operator)
    int         token_redir;    // Redirection type if applicable
    struct s_token *next_token; // Pointer to the next token in the list
} t_token;
```

### Tokenization Process

1. **Input Reading**
   - The shell reads input using readline
   - Input is stored and added to history

2. **Character Analysis**
   - Input is processed character by character
   - Special characters are identified
   - Quotes are handled specially to maintain string integrity

3. **Token Generation**
   - Tokens are created based on delimiters (spaces, operators)
   - Each token is assigned a type and ID
   - Tokens are linked in a linked list structure

4. **Special Handling**
   - Quotes (both single and double) are processed to maintain string integrity
   - Environment variables are identified for later expansion
   - Operators are properly separated and classified

## Error Handling

The tokenizer includes robust error handling for:
- Unclosed quotes
- Invalid operators
- Syntax errors
- Memory allocation failures

## Integration

The tokenizer works closely with:
1. The parser (`srcs/parse/`)
2. The expansion module (`srcs/expand/`)
3. The main shell loop

## Example

Input:
```bash
echo "Hello $USER" | grep "Hello"
```

Tokenized as:
1. `echo` (command token)
2. `"Hello $USER"` (argument token with pending expansion)
3. `|` (pipe operator token)
4. `grep` (command token)
5. `"Hello"` (argument token)

## Key Functions

1. **Token Creation**
   ```c
   // Creates a new token with the given parameters
   t_token *create_token(char *content, int type);
   ```

2. **Token List Management**
   ```c
   // Adds a token to the end of the token list
   void add_token(t_token **list, t_token *new_token);
   ```

3. **Token Classification**
   ```c
   // Determines the type of a token
   int classify_token(char *content);
   ```

4. **Quote Handling**
   ```c
   // Processes quoted strings
   char *handle_quotes(char *input, int *pos);
   ```

## Memory Management

The tokenizer implements careful memory management:
- Each token is dynamically allocated
- Token content is properly duplicated
- Memory is freed when tokens are no longer needed
- Cleanup functions handle both success and error cases 