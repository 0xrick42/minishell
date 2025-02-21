# Parsing Process

## Overview
The parsing component (`srcs/parse/`) transforms the token stream into an Abstract Syntax Tree (AST) representing the command structure. It validates syntax, handles command grouping, and prepares the command structure for execution.

## Command Structure

### Command Node
```c
typedef struct s_cmd {
    t_cmd_type      cmd_type;       // Command type (SIMPLE, PIPE, etc.)
    char            **args;         // Command arguments array
    t_redir         *redirects;     // Redirection list
    struct s_cmd    *left;          // Left command (for pipes)
    struct s_cmd    *right;         // Right command (for pipes)
} t_cmd;
```

### Redirection Node
```c
typedef struct s_redir {
    t_redir_type    type;           // Redirection type
    char            *file;          // Target file/heredoc delimiter
    int             fd;             // File descriptor
    struct s_redir  *next;          // Next redirection
} t_redir;
```

## Implementation Details

### 1. Command Building
```c
t_cmd *ft_build_command(t_minishell *minishell, t_token *token);
```
- Constructs command nodes
- Handles argument collection
- Manages redirection setup
- Builds pipeline structures

### 2. Pipeline Processing
```c
t_cmd *ft_build_pipeline(t_minishell *minishell, t_token *start, t_token *end);
```
- Creates pipeline nodes
- Links commands
- Validates pipe sequences
- Manages file descriptors

### 3. Redirection Handling
```c
bool ft_add_redirection(t_cmd *cmd, t_token *token);
```
- Processes redirection tokens
- Sets up file descriptors
- Handles heredoc setup
- Validates file operations

### 4. Argument Processing
```c
char **ft_collect_args(t_token *start, t_token *end);
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

### 3. AST Building
- Node creation
- Tree structure formation
- Command linking
- Error handling

### 4. Final Validation
- Tree structure verification
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
- Redirection node creation
- Argument array management
- Tree structure maintenance

### 2. Cleanup
```c
void ft_free_command(t_cmd *cmd);
```
- Recursive tree cleanup
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
- Command tree handoff
- Resource sharing
- Error communication
- State synchronization

## Examples

### 1. Simple Command
```bash
ls -l
```
AST:
```
CMD_SIMPLE
├── args: ["ls", "-l"]
└── redirects: NULL
```

### 2. Pipeline
```bash
echo "hello" | grep "o"
```
AST:
```
CMD_PIPE
├── left: CMD_SIMPLE
│   └── args: ["echo", "hello"]
└── right: CMD_SIMPLE
    └── args: ["grep", "o"]
```

### 3. Redirections
```bash
cat < input.txt > output.txt
```
AST:
```
CMD_SIMPLE
├── args: ["cat"]
└── redirects:
    ├── REDIR_IN ("input.txt")
    └── REDIR_OUT ("output.txt")
```

### 4. Heredoc
```bash
cat << EOF
```
AST:
```
CMD_SIMPLE
├── args: ["cat"]
└── redirects:
    └── REDIR_HEREDOC ("EOF")
```

## Performance Considerations

### 1. Memory Efficiency
- Minimal copying
- Efficient tree structure
- Smart resource allocation
- Prompt cleanup

### 2. Processing Speed
- Optimized tree traversal
- Efficient node linking
- Smart validation checks
- Quick error detection

### 3. Resource Management
- File descriptor tracking
- Memory usage monitoring
- Pipeline optimization
- Error recovery 