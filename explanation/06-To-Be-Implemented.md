# Features To Be Implemented

This document outlines the key features that still need to be implemented to complete the minishell project.

## 1. Command Execution

The most critical missing component is the actual command execution. This involves:

### Core Execution Engine

```c
int ft_execute_command(t_minishell *minishell, t_cmd *cmd)
{
    // 1. Check if command is a builtin
    if (ft_is_builtin(cmd->cmd_name))
        return (ft_execute_builtin(minishell, cmd));
        
    // 2. For external commands
    pid_t pid = fork();
    if (pid == -1)
        return (ft_error("fork failed"), 1);
        
    if (pid == 0)
    {
        // Child process
        
        // 3. Set up redirections
        if (!ft_setup_redirections(cmd))
            exit(1);
            
        // 4. Find command in PATH
        char *cmd_path = ft_find_command(cmd->cmd_name, minishell);
        if (!cmd_path)
        {
            ft_error("command not found");
            exit(127);
        }
        
        // 5. Execute command
        execve(cmd_path, cmd->cmd_args, ft_env_to_array(minishell));
        
        // If execve returns, an error occurred
        ft_error("execve failed");
        exit(126);
    }
    else
    {
        // Parent process
        
        // 6. Wait for command to finish
        int status;
        waitpid(pid, &status, 0);
        
        // 7. Return exit status
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            return (WTERMSIG(status) + 128);
        return (1);
    }
}
```

### Command Path Resolution

```c
char *ft_find_command(char *cmd_name, t_minishell *minishell)
{
    // 1. Check if command has a slash (absolute or relative path)
    if (ft_strchr(cmd_name, '/'))
        return (ft_strdup(cmd_name));
        
    // 2. Get PATH environment variable
    t_envar *path_var = ft_find_envar(minishell, "PATH");
    if (!path_var)
        return (NULL);
        
    // 3. Split PATH into directories
    char **path_dirs = ft_split(path_var->value, ':');
    if (!path_dirs)
        return (NULL);
        
    // 4. Try each directory
    int i = 0;
    char *full_path;
    while (path_dirs[i])
    {
        // Construct full path
        full_path = ft_strjoin_three(path_dirs[i], "/", cmd_name);
        if (!full_path)
        {
            ft_free_table(path_dirs);
            return (NULL);
        }
        
        // Check if file exists and is executable
        if (access(full_path, X_OK) == 0)
        {
            ft_free_table(path_dirs);
            return (full_path);
        }
        
        free(full_path);
        i++;
    }
    
    ft_free_table(path_dirs);
    return (NULL);
}
```

### Builtin Execution

```c
int ft_execute_builtin(t_minishell *minishell, t_cmd *cmd)
{
    if (ft_strcmp(cmd->cmd_name, "echo") == 0)
        return (ft_echo(minishell, cmd->cmd_args));
    else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
        return (ft_cd(minishell, cmd->cmd_args));
    else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
        return (ft_pwd(minishell, cmd->cmd_args));
    else if (ft_strcmp(cmd->cmd_name, "export") == 0)
        return (ft_export(minishell, cmd->cmd_args));
    else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
        return (ft_unset(minishell, cmd->cmd_args));
    else if (ft_strcmp(cmd->cmd_name, "env") == 0)
        return (ft_env(minishell, cmd->cmd_args));
    else if (ft_strcmp(cmd->cmd_name, "exit") == 0)
        return (ft_exit(minishell, cmd->cmd_args));
    return (1);
}
```

## 2. Redirection Handling

Redirection handling needs to be fully implemented:

```c
bool ft_setup_redirections(t_cmd *cmd)
{
    int i = 0;
    
    while (cmd->cmd_args[i])
    {
        // Check for output redirection (>)
        if (ft_strcmp(cmd->cmd_args[i], ">") == 0)
        {
            if (!cmd->cmd_args[i + 1])
                return (ft_error("syntax error near unexpected token `newline'"), false);
                
            int fd = open(cmd->cmd_args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return (ft_error("cannot open file"), false);
                
            dup2(fd, STDOUT_FILENO);
            close(fd);
            
            // Remove redirection from arguments
            ft_remove_args(cmd, i, 2);
            continue;
        }
        
        // Check for append redirection (>>)
        if (ft_strcmp(cmd->cmd_args[i], ">>") == 0)
        {
            if (!cmd->cmd_args[i + 1])
                return (ft_error("syntax error near unexpected token `newline'"), false);
                
            int fd = open(cmd->cmd_args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (ft_error("cannot open file"), false);
                
            dup2(fd, STDOUT_FILENO);
            close(fd);
            
            // Remove redirection from arguments
            ft_remove_args(cmd, i, 2);
            continue;
        }
        
        // Check for input redirection (<)
        if (ft_strcmp(cmd->cmd_args[i], "<") == 0)
        {
            if (!cmd->cmd_args[i + 1])
                return (ft_error("syntax error near unexpected token `newline'"), false);
                
            int fd = open(cmd->cmd_args[i + 1], O_RDONLY);
            if (fd == -1)
                return (ft_error("no such file or directory"), false);
                
            dup2(fd, STDIN_FILENO);
            close(fd);
            
            // Remove redirection from arguments
            ft_remove_args(cmd, i, 2);
            continue;
        }
        
        // Check for heredoc (<<)
        if (ft_strcmp(cmd->cmd_args[i], "<<") == 0)
        {
            if (!cmd->cmd_args[i + 1])
                return (ft_error("syntax error near unexpected token `newline'"), false);
                
            // Handle heredoc (discussed in the next section)
            if (!ft_setup_heredoc(cmd->cmd_args[i + 1]))
                return (false);
                
            // Remove redirection from arguments
            ft_remove_args(cmd, i, 2);
            continue;
        }
        
        i++;
    }
    
    return (true);
}
```

## 3. Heredoc Implementation

The heredoc feature (<<) needs to be implemented:

```c
bool ft_setup_heredoc(char *delimiter)
{
    // 1. Create a temporary file
    char template[] = "/tmp/minishell_heredoc_XXXXXX";
    int fd = mkstemp(template);
    if (fd == -1)
        return (ft_error("cannot create temporary file"), false);
    
    // 2. Read input until delimiter is found
    char *line;
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        
        // Write line to temporary file
        ft_putendl_fd(line, fd);
        free(line);
    }
    
    // 3. Reopen file for reading
    close(fd);
    fd = open(template, O_RDONLY);
    if (fd == -1)
        return (ft_error("cannot open temporary file"), false);
    
    // 4. Set up redirection
    dup2(fd, STDIN_FILENO);
    close(fd);
    
    // 5. Clean up (unlink temporary file)
    unlink(template);
    
    return (true);
}
```

## 4. Pipe Implementation

Pipe handling needs to be implemented to connect commands:

```c
int ft_execute_pipeline(t_minishell *minishell)
{
    t_cmd *current = minishell->cmd_list;
    int prev_pipe[2] = {-1, -1};
    int curr_pipe[2];
    pid_t pid;
    int status = 0;
    
    while (current)
    {
        // Create pipe for all but the last command
        if (current->next_cmd)
        {
            if (pipe(curr_pipe) == -1)
                return (ft_error("pipe failed"), 1);
        }
        
        pid = fork();
        if (pid == -1)
            return (ft_error("fork failed"), 1);
        
        if (pid == 0)
        {
            // Child process
            
            // Set up input from previous pipe (if not first command)
            if (prev_pipe[0] != -1)
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            
            // Set up output to current pipe (if not last command)
            if (current->next_cmd)
            {
                close(curr_pipe[0]);
                dup2(curr_pipe[1], STDOUT_FILENO);
                close(curr_pipe[1]);
            }
            
            // Execute command
            exit(ft_execute_command(minishell, current));
        }
        
        // Parent process
        
        // Close previous pipe (if not first command)
        if (prev_pipe[0] != -1)
        {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
        
        // Save current pipe for next iteration
        if (current->next_cmd)
        {
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
        }
        
        current = current->next_cmd;
    }
    
    // Close any remaining pipe
    if (prev_pipe[0] != -1)
    {
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    
    // Wait for all children to finish
    while (waitpid(-1, &status, 0) > 0)
        ;
    
    // Return exit status of last command
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        return (WTERMSIG(status) + 128);
    return (1);
}
```

## 5. Signal Handling

Signal handling needs to be implemented:

```c
void ft_setup_signals(void)
{
    // Set up SIGINT (Ctrl+C) handler
    signal(SIGINT, ft_handle_sigint);
    
    // Ignore SIGQUIT (Ctrl+\)
    signal(SIGQUIT, SIG_IGN);
}

void ft_handle_sigint(int sig)
{
    (void)sig;
    
    // Print a new prompt on a new line
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
```

## 6. Integration with Main Shell Loop

Finally, the execution engine needs to be integrated with the main shell loop:

```c
int main(int ac, char **av, char **envp)
{
    t_minishell *minishell;
    char *input;
    
    // Initialize shell data
    minishell = malloc(sizeof(t_minishell));
    minishell->token_list = NULL;
    minishell->env_list = NULL;
    minishell->cmd_list = NULL;
    minishell->exit_status = 0;
    
    // Create environment variable list
    ft_envar_list(envp, minishell);
    
    // Set up signal handlers
    ft_setup_signals();
    
    // Main shell loop
    while (1)
    {
        // Display prompt and read input
        input = readline("minishell$ ");
        if (!input)
            break;  // Ctrl+D (EOF) exits the shell
            
        // Add to history
        add_history(input);
        
        // Process input (tokenize)
        if (!ft_parsing(minishell, input))
        {
            ft_free_token_list(minishell);
            free(input);
            continue;
        }
        
        // Create command structures
        ft_free_token_list(minishell);
        if (!ft_cmd_struct(input, minishell))
        {
            // Handle error
            free(input);
            continue;
        }
        
        // Execute commands
        minishell->exit_status = ft_execute_pipeline(minishell);
        
        // Clean up
        ft_free_cmd_list(minishell->cmd_list);
        minishell->cmd_list = NULL;
        free(input);
    }
    
    // Clean up and exit
    rl_clear_history();
    // Free all allocated memory
    return (minishell->exit_status);
}
```

## Implementation Priority

Here's a suggested order of implementation:

1. **Command Execution for Single Commands**
   - Basic execution with execve
   - Path resolution
   - Builtin execution

2. **Redirection Handling**
   - Input/output redirection
   - Append redirection

3. **Pipe Implementation**
   - Connecting commands with pipes

4. **Heredoc Implementation**
   - Processing heredocs

5. **Signal Handling**
   - Handling Ctrl+C, Ctrl+D, Ctrl+\

By implementing these features, you will have a fully functional minishell that meets all the project requirements. 