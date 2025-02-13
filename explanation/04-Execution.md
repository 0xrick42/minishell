# Command Execution Process

## Overview

The execution component (`srcs/exec/`) is responsible for executing commands and managing processes in the shell. It handles both built-in commands and external programs, manages pipelines, and handles redirections.

## Execution Components

### 1. Command Execution Structure
```c
typedef struct s_exec {
    pid_t       pid;            // Process ID
    int         status;         // Exit status
    int         pipe_fd[2];     // Pipe file descriptors
    char        *path;          // Command path
    char        **env;          // Environment variables
} t_exec;
```

## Execution Process

1. **Command Type Determination**
   - Check if command is built-in
   - Resolve command path for external programs
   - Validate command existence

2. **Process Creation**
   - Fork new processes for external commands
   - Set up process groups
   - Handle job control

3. **Redirection Setup**
   - Configure input/output redirections
   - Set up pipe connections
   - Handle file descriptors

4. **Command Execution**
   - Execute built-in commands directly
   - Use execve for external commands
   - Handle execution errors

5. **Process Management**
   - Track child processes
   - Handle process termination
   - Collect exit status

## Built-in Commands

The shell implements several built-in commands:
1. `cd` - Change directory
2. `echo` - Display text
3. `pwd` - Print working directory
4. `export` - Set environment variables
5. `unset` - Remove environment variables
6. `env` - Display environment
7. `exit` - Exit the shell

## Pipeline Execution

1. **Pipeline Setup**
   - Create pipes between commands
   - Set up process groups
   - Configure redirections

2. **Process Creation**
   - Fork processes for each command
   - Connect pipes between processes
   - Handle pipe errors

3. **Execution Flow**
   - Execute commands in sequence
   - Manage data flow through pipes
   - Handle pipeline failures

## Error Handling

The execution module handles various errors:
- Command not found
- Permission denied
- Fork failures
- Pipe errors
- Execution failures

## Key Functions

### 1. Command Execution
```c
// Execute a single command
int execute_command(t_cmd *cmd, t_minishell *minishell);
```

### 2. Pipeline Management
```c
// Handle pipeline execution
int execute_pipeline(t_cmd *cmd_list, t_minishell *minishell);
```

### 3. Built-in Command Handling
```c
// Execute built-in commands
int execute_builtin(t_cmd *cmd, t_minishell *minishell);
```

### 4. Process Management
```c
// Manage child processes
int wait_for_processes(t_exec *exec);
```

## Integration

The execution module interacts with:
1. Parser (receives command structures)
2. Built-in commands module
3. Environment management
4. Signal handling

## Example

For the command:
```bash
ls -l | grep "file" > output.txt
```

Execution flow:
1. Create pipe
2. Fork first process (ls)
   - Set up pipe write end
   - Execute ls command
3. Fork second process (grep)
   - Set up pipe read end
   - Set up output redirection
   - Execute grep command
4. Wait for both processes
5. Clean up resources

## Process Management

1. **Process Creation**
   - Fork new processes
   - Set process groups
   - Handle parent/child relationships

2. **Process Monitoring**
   - Track active processes
   - Handle process termination
   - Collect exit status

3. **Resource Management**
   - Close unused file descriptors
   - Clean up pipe resources
   - Handle process cleanup

## Signal Handling

The execution module handles:
- SIGINT (Ctrl+C)
- SIGQUIT (Ctrl+\)
- SIGTERM
- Custom signal handlers

## Performance Optimization

The execution module is optimized for:
- Minimal process creation
- Efficient pipe usage
- Quick command resolution
- Resource cleanup
- Memory management

## Error Recovery

The module implements robust error recovery:
1. **Process Failures**
   - Handle fork failures
   - Manage execution errors
   - Clean up on failures

2. **Resource Cleanup**
   - Close file descriptors
   - Remove temporary files
   - Clean up child processes

3. **State Recovery**
   - Restore shell state
   - Handle interrupted commands
   - Maintain shell stability 