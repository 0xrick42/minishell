# Command Execution

## Overview
The execution component (`srcs/exec/`) is responsible for executing the command tree produced by the parser. It handles process creation, redirection setup, pipeline management, builtin execution, and error handling.

## Core Components

### 1. Command Executor
```c
int ft_execute_command(t_minishell *minishell, t_cmd *cmd);
```
- Main execution entry point
- Command type routing
- Process management
- Error handling

### 2. Pipeline Executor
```c
int ft_execute_pipeline(t_minishell *minishell, t_cmd *cmd);
```
- Pipeline setup
- Process creation
- File descriptor management
- Synchronization

### 3. Redirection Handler
```c
int ft_setup_redirections(t_cmd *cmd);
```
- File descriptor setup
- Heredoc processing
- File operations
- Error handling

### 4. Builtin Executor
```c
int ft_execute_builtin(t_minishell *minishell, t_cmd *cmd);
```
- Builtin command detection
- Direct execution
- Environment management
- Return value handling

## Implementation Details

### 1. Process Management
- Fork handling
- Child process setup
- Parent process coordination
- Exit status collection

### 2. File Descriptor Management
- Standard I/O redirection
- Pipeline setup
- File operations
- Descriptor cleanup

### 3. Environment Management
- Variable expansion
- Path resolution
- Working directory
- Signal handling

### 4. Heredoc Processing
```c
int ft_process_heredoc(t_redir *redir);
```
- Delimiter handling
- Content collection
- Signal management
- Temporary file creation

## Execution Flow

### 1. Command Analysis
- Command type determination
- Builtin detection
- Path resolution
- Permission checking

### 2. Resource Setup
- Process creation
- File descriptor setup
- Environment preparation
- Signal configuration

### 3. Command Execution
- Process spawning
- Redirection application
- Pipeline coordination
- Error handling

### 4. Cleanup and Status
- Resource deallocation
- Exit status collection
- Error propagation
- State restoration

## Error Handling

### 1. Execution Errors
- Command not found
- Permission denied
- Fork failures
- Pipe errors

### 2. Resource Errors
- File descriptor limits
- Memory allocation
- Process limits
- System call failures

### 3. Signal Handling
- Interrupt handling
- Child process termination
- Pipeline cleanup
- State restoration

## Memory Management

### 1. Process Resources
- File descriptor tracking
- Child process cleanup
- Pipeline management
- Memory deallocation

### 2. Command Cleanup
```c
void ft_cleanup_command(t_cmd *cmd);
```
- Resource deallocation
- File descriptor closure
- Process termination
- Error state handling

## Integration Points

### 1. Parser Interface
- Command tree processing
- Error propagation
- Resource sharing
- State management

### 2. Builtin Interface
- Command detection
- Direct execution
- Environment access
- Status reporting

## Examples

### 1. Simple Command
```bash
ls -l
```
Execution:
1. Fork process
2. Execute command
3. Collect status

### 2. Pipeline
```bash
echo "hello" | grep "o"
```
Execution:
1. Create pipe
2. Fork for echo
3. Fork for grep
4. Connect pipe
5. Execute commands
6. Collect status

### 3. Redirections
```bash
cat < input.txt > output.txt
```
Execution:
1. Open files
2. Setup redirections
3. Fork process
4. Execute command
5. Restore descriptors

### 4. Heredoc
```bash
cat << EOF
```
Execution:
1. Create temp file
2. Collect content
3. Setup redirection
4. Execute command
5. Cleanup temp file

## Performance Considerations

### 1. Process Management
- Minimal forking
- Efficient pipe usage
- Smart descriptor handling
- Quick cleanup

### 2. Resource Usage
- File descriptor limits
- Memory consumption
- Process table usage
- System call optimization

### 3. Error Recovery
- Graceful cleanup
- Resource restoration
- State preservation
- Error propagation

## Special Cases

### 1. Signal Handling
- SIGINT (Ctrl+C)
- SIGQUIT (Ctrl+\)
- SIGTERM
- Child process signals

### 2. Exit Status
- Command completion
- Signal termination
- Error conditions
- Status propagation

### 3. Environment Updates
- Variable changes
- Directory changes
- Shell state
- Child inheritance 