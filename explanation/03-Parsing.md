# Parsing Process

## Overview
The parsing component (`srcs/parse/`) transforms the token stream into a linked list of commands representing the command structure. It validates syntax, handles command grouping, and prepares the command structure for execution.

## Command Structure

### Command Node
```c
typedef struct s_cmd {
    char            *cmd_name;      // Name of the command
    char            **cmd_args;     // Command arguments array
    struct s_cmd    *next_cmd;      // Next command in list
} t_cmd;
```

### Token Node
```c
typedef struct s_token {
    int             token_id;       // Token identifier
    char            *token_name;    // Token content
    t_token_type    token_type;     // Token classification
    t_token_redir   token_redir;    // Redirection flag
    struct s_token  *next_token;    // Next token in list
} t_token;
```

## Implementation Details

### 1. Command Building
```c
bool ft_cmd_struct(char *input, t_minishell *minishell);
```
- Constructs command nodes
- Handles argument collection
- Manages redirection setup
- Builds command list

### 2. Pipeline Processing
```c
bool ft_cmd_list(char *cmd_cell, t_minishell *minishell);
```
- Creates command nodes
- Links commands sequentially
- Validates pipe sequences
- Manages file descriptors

### 3. Token Processing
```c
bool ft_tokenization(t_minishell *minishell, char *input, int i);
```
- Processes input characters
- Creates token nodes
- Builds token list
- Validates token sequence

### 4. Argument Processing
```c
char **ft_split_cmd_args(char *cmd_cell);
```
- Collects command arguments
- Handles word expansion
- Manages memory allocation
- Validates argument format

## Parsing Steps

### 1. Initial Validation
- Token sequence validation
- Syntax checking
- Error detection
- Command boundary identification

### 2. Command Construction
- Command type determination
- Argument collection
- Redirection setup
- Pipeline creation

### 3. List Building
- Node creation
- List structure formation
- Command linking
- Error handling

### 4. Final Validation
- List structure verification
- Resource allocation check
- Command validity
- Redirection validation

## Error Handling

### 1. Syntax Errors
- Invalid command sequences
- Malformed pipelines
- Redirection errors
- Missing arguments

### 2. Resource Errors
- Memory allocation failures
- File descriptor limits
- Pipeline setup errors
- Cleanup on failure

## Memory Management

### 1. Structure Allocation
- Command node allocation
- Token node creation
- Argument array management
- List structure maintenance

### 2. Cleanup
```c
void ft_free_cmd_list(t_cmd *cmd_list);
void ft_free_token_list(t_minishell *minishell);
```
- List cleanup
- Resource deallocation
- File descriptor cleanup
- Error state handling

## Integration Points

### 1. Tokenizer Interface
- Token list processing
- Syntax validation
- Error propagation
- State management

### 2. Executor Interface
- Command list handoff
- Resource sharing
- Error communication
- State synchronization

## Examples

### 1. Simple Command
```bash
ls -l
```
Command List:
```
[CMD_NODE]
├── cmd_name: "ls"
└── cmd_args: ["ls", "-l"]
```

### 2. Pipeline
```bash
echo "hello" | grep "o"
```
Command List:
```
[CMD_NODE_1] -> [CMD_NODE_2]
├── cmd_name: "echo"     ├── cmd_name: "grep"
└── cmd_args: ["echo",   └── cmd_args: ["grep", 
              "hello"]              "o"]
```

### 3. Redirections
```bash
cat < input.txt > output.txt
```
Token List:
```
[WORD("cat")] -> [LESS("<")] -> [WORD("input.txt")] -> 
[GREAT(">")] -> [WORD("output.txt")]
```

### 4. Heredoc
```bash
cat << EOF
```
Token List:
```
[WORD("cat")] -> [LLESS("<<")] -> [WORD("EOF")]
```

## Performance Considerations

### 1. Memory Efficiency
- Minimal copying
- Efficient list traversal
- Smart resource allocation
- Prompt cleanup

### 2. Processing Speed
- Optimized list traversal
- Efficient node linking
- Smart validation checks
- Quick error detection

### 3. Resource Management
- File descriptor tracking
- Memory usage monitoring
- Pipeline optimization
- Error recovery 