# Command Execution

## What Happens When Commands Run?

The execution component (`srcs/exec/`) is responsible for actually running your commands. Think of it as the part that takes your command list and makes things happen!

## Main Parts

### 1. Command Runner
```c
int ft_execute_command(t_minishell *minishell, t_cmd *cmd);
```
This is the main function that:
- Figures out what kind of command to run
- Creates new processes when needed
- Handles any errors that happen
- Returns the result

### 2. Pipeline Handler
```c
int ft_execute_pipeline(t_minishell *minishell, t_cmd *cmd);
```
When you use pipes (like `cmd1 | cmd2`), this function:
- Creates the pipe
- Sets up both commands
- Connects them together
- Makes sure data flows correctly

### 3. Redirection Setup
```c
int ft_setup_redirections(t_cmd *cmd);
```
When you use `>`, `<`, `>>`, or `<<`, this function:
- Opens the right files
- Connects them to the command
- Handles any file errors
- Sets up heredocs (for `<<`)

### 4. Built-in Command Runner
```c
int ft_execute_builtin(t_minishell *minishell, t_cmd *cmd);
```
For built-in commands (like `cd` or `echo`), this:
- Recognizes the built-in command
- Runs it directly (no new process needed)
- Handles the command's arguments
- Returns the result

## How It All Works

### 1. Process Management
When running commands, the shell:
- Creates new processes (using `fork`)
- Sets up each process correctly
- Waits for commands to finish
- Collects their exit status

### 2. File Management
For files and pipes, it:
- Opens files safely
- Sets up pipe connections
- Makes sure files are readable/writable
- Cleans up when done

### 3. Environment Setup
Before running commands:
- Sets up environment variables
- Finds command locations (in PATH)
- Handles current directory
- Manages signals (like Ctrl+C)

### 4. Heredoc Handling
For `<<` heredocs:
- Creates a temporary file
- Reads input until delimiter
- Sets up the input properly
- Cleans up after use

## Step by Step Example

### Simple Command: `ls -l`
1. Shell creates new process
2. In new process:
   - Finds `ls` in PATH
   - Sets up arguments (`-l`)
   - Runs the command
3. Waits for finish
4. Shows result

### Pipeline: `echo hello | grep o`
1. Shell creates a pipe
2. Creates process for `echo`:
   - Connects its output to pipe
   - Runs `echo hello`
3. Creates process for `grep`:
   - Connects its input to pipe
   - Runs `grep o`
4. Waits for both
5. Shows result

### Redirection: `cat < input.txt > output.txt`
1. Shell opens `input.txt`
2. Opens `output.txt`
3. Creates process for `cat`:
   - Connects input to `input.txt`
   - Connects output to `output.txt`
4. Runs command
5. Cleans up files

## Error Handling

The shell watches for:
1. **Command Errors**
   - Command not found
   - Permission denied
   - Can't create process
   - Pipe errors

2. **Resource Errors**
   - Can't open files
   - Out of memory
   - Too many processes
   - System call fails

3. **Signal Handling**
   - Ctrl+C (interrupt)
   - Child process stops
   - Cleanup needed
   - State recovery

## Memory Care

The shell is careful with:
1. **Process Resources**
   - Tracks open files
   - Cleans up child processes
   - Manages pipes
   - Frees memory

2. **Command Cleanup**
```c
void ft_cleanup_command(t_cmd *cmd);
```
This function:
- Frees all memory
- Closes all files
- Stops all processes
- Handles errors

## Working Together

### 1. With Parser
- Gets command list
- Reports errors back
- Shares resources
- Manages state

### 2. With Built-ins
- Finds built-in commands
- Runs them directly
- Accesses environment
- Reports results

## Examples

### 1. Simple Command
```bash
ls -l
```
What happens:
1. Fork new process
2. Run command
3. Get result

### 2. Pipeline
```bash
echo "hello" | grep "o"
```
What happens:
1. Make pipe
2. Fork for echo
3. Fork for grep
4. Connect pipe
5. Run both
6. Get result

### 3. Redirections
```bash
cat < input.txt > output.txt
```
What happens:
1. Open files
2. Set up redirection
3. Fork process
4. Run command
5. Clean up files

### 4. Heredoc
```bash
cat << EOF
```
What happens:
1. Make temp file
2. Get input
3. Set up redirection
4. Run command
5. Clean up

## Making It Fast

### 1. Process Management
- Create processes efficiently
- Use pipes smartly
- Handle files quickly
- Clean up promptly

### 2. Resource Usage
- Watch file limits
- Manage memory well
- Track processes
- Optimize system calls

### 3. Error Recovery
- Clean up nicely
- Restore resources
- Keep state safe
- Report errors clearly

## Special Cases

### 1. Signal Handling
- Ctrl+C (SIGINT)
- Ctrl+\ (SIGQUIT)
- Process end (SIGTERM)
- Child signals

### 2. Exit Status
- Command completion
- Signal stops
- Error cases
- Status passing

### 3. Environment Changes
- Variable updates
- Directory changes
- Shell state
- Child inheritance 