# Parsing Process

## Overview

The parsing component (`srcs/parse/`) is responsible for converting the token stream into meaningful command structures that can be executed by the shell. It performs syntax analysis and creates a structured representation of the command line input.

## Command Structure

### Command Node
```c
typedef struct s_cmd {
    char        *cmd_name;      // Name of the command
    char        **cmd_args;     // Array of command arguments
    int         input_fd;       // Input file descriptor
    int         output_fd;      // Output file descriptor
    int         pipe_read;      // Read end of pipe
    int         pipe_write;     // Write end of pipe
    struct s_cmd *next_cmd;     // Next command in pipeline
} t_cmd;
```

## Parsing Process

1. **Token Analysis**
   - Tokens are processed sequentially
   - Command structures are built based on token types
   - Syntax validation is performed

2. **Command Building**
   - First token in a command group becomes the command name
   - Subsequent tokens become arguments
   - Redirection operators are processed
   - Pipe operators create new command nodes

3. **Redirection Handling**
   - Input redirection (<)
   - Output redirection (>, >>)
   - Here-document (<<)
   - File descriptor validation

4. **Pipeline Construction**
   - Multiple commands are linked
   - Pipe file descriptors are set up
   - Command relationships are established

## Error Handling

The parser handles various error conditions:
- Invalid command syntax
- Missing command arguments
- Redirection errors
- Pipeline errors
- Memory allocation failures

## Key Components

### 1. Command List Management
```c
// Creates and manages the list of commands
int ft_cmd_struct(char *input, t_minishell *minishell);
```

### 2. Argument Processing
```c
// Processes and stores command arguments
int process_arguments(t_cmd *cmd, t_token *token);
```

### 3. Redirection Setup
```c
// Handles input/output redirections
int setup_redirections(t_cmd *cmd, t_token *token);
```

### 4. Pipeline Management
```c
// Sets up command pipelines
int setup_pipeline(t_cmd *cmd1, t_cmd *cmd2);
```

## Integration Points

The parser interacts with:
1. The tokenizer (receives token stream)
2. The execution module (provides command structures)
3. The expansion module (for variable and wildcard expansion)

## Example

For the input:
```bash
ls -l | grep "file" > output.txt
```

The parser creates:
1. First command node:
   - cmd_name: "ls"
   - cmd_args: ["ls", "-l"]
   - pipe_write: set to pipe's write end

2. Second command node:
   - cmd_name: "grep"
   - cmd_args: ["grep", "file"]
   - pipe_read: set to pipe's read end
   - output_fd: file descriptor for "output.txt"

## Memory Management

The parser implements careful memory management:
- Dynamic allocation for command structures
- Proper cleanup of command lists
- Handling of file descriptors
- Resource cleanup on error conditions

## Error Cases

The parser handles various error scenarios:
1. **Syntax Errors**
   - Missing command names
   - Invalid redirection syntax
   - Unclosed quotes

2. **Resource Errors**
   - File open failures
   - Pipe creation failures
   - Memory allocation failures

3. **Logic Errors**
   - Invalid command sequences
   - Pipeline misconfigurations
   - Redirection conflicts

## Performance Considerations

The parser is optimized for:
- Efficient memory usage
- Quick command structure creation
- Minimal copying of data
- Proper resource management 