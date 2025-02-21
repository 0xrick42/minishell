# Minishell Project Overview

## What is Minishell?
Minishell is a simple shell implementation that works like bash. Think of it as a program that:
1. Shows you a prompt
2. Reads your command (like `ls -l` or `echo "hello"`)
3. Understands what you want to do
4. Executes the command
5. Shows you the result
6. Repeats!

## How Does It Work? (The Big Picture)

### 1. Reading Your Command
When you type a command, the shell:
- Shows you the `minishell$` prompt
- Uses `readline()` to get your input
- Saves the command in history (so you can use up arrow later!)

### 2. Breaking Down the Command (Tokenization)
The shell breaks your command into small pieces called tokens. For example:
```bash
echo "hello world" | grep "o" > output.txt
```
Becomes tokens:
1. `echo` (a WORD token)
2. `"hello world"` (a WORD token)
3. `|` (a PIPE token)
4. `grep` (a WORD token)
5. `"o"` (a WORD token)
6. `>` (a GREAT token - for redirection)
7. `output.txt` (a WORD token)

### 3. Understanding the Command (Parsing)
The shell then organizes these tokens into a list of commands. Each command knows:
- What program to run (like `echo` or `grep`)
- What arguments to pass (like `"hello world"`)
- Where to send its output (to a pipe or a file)
- Where to get its input from (from a pipe or a file)

### 4. Setting Things Up (Preparation)
Before running the command, the shell:
- Creates pipes if needed (for commands like `cmd1 | cmd2`)
- Opens files if needed (for `>` output.txt or `<` input.txt)
- Sets up environment variables

### 5. Running the Command (Execution)
Finally, the shell:
- Creates new processes for each command
- Connects all the pipes and files
- Runs the programs
- Waits for them to finish
- Collects the results

## The Main Components

### 1. Input Processing (`srcs/main.c`)
- Gets your command using readline
- Manages command history
- Handles Ctrl+C and other signals

### 2. Tokenizer (`srcs/token/`)
Breaks your command into tokens:
```c
typedef struct s_token {
    int             token_id;       // A number for each token
    char            *token_name;    // The actual text
    t_token_type    token_type;     // What kind of token (WORD, PIPE, etc.)
    t_token_redir   token_redir;    // Is it a redirection?
    struct s_token  *next_token;    // Points to next token
} t_token;
```

### 3. Parser (`srcs/parse/`)
Organizes tokens into commands:
```c
typedef struct s_cmd {
    char            *cmd_name;      // Program to run
    char            **cmd_args;     // Arguments for the program
    struct s_cmd    *next_cmd;      // Next command (for pipes)
} t_cmd;
```

### 4. Environment Manager
Keeps track of environment variables:
```c
typedef struct s_envar {
    char            *key;           // Variable name
    char            *value;         // Variable value
    struct s_envar  *next;         // Next variable
} t_envar;
```

### 5. Shell State
Keeps track of everything:
```c
typedef struct s_minishell {
    t_token         *token_list;    // List of tokens
    t_envar         *env_list;      // List of environment variables
    t_cmd           *cmd_list;      // List of commands
    int             exit_status;    // Last command's result
} t_minishell;
```

## How Commands Flow Through the Shell

1. **You Type**: `echo "hello" | grep "o"`

2. **Tokenizer Makes**:
   ```
   [WORD("echo")] -> [WORD("hello")] -> [PIPE("|")] -> 
   [WORD("grep")] -> [WORD("o")]
   ```

3. **Parser Creates**:
   ```
   Command 1         Command 2
   [echo "hello"] -> [grep "o"]
   ```

4. **Executor**:
   - Creates a pipe
   - Runs `echo "hello"`
   - Connects its output to the pipe
   - Runs `grep "o"`
   - Connects its input to the pipe
   - Shows you the result

## Built-in Commands
Some commands are built into the shell:
- `cd`: Change directory
- `echo`: Print text
- `pwd`: Print current directory
- `export`: Set environment variables
- `unset`: Remove environment variables
- `env`: Show environment variables
- `exit`: Exit the shell

## Error Handling
The shell carefully checks for:
- Syntax errors (`ls ||| ls`)
- File errors (`cd nonexistent`)
- Permission errors (`./not_executable`)
- Memory errors (out of memory)

## Memory Management
The shell is careful about memory:
- Allocates memory when needed
- Frees memory when done
- Cleans up after errors
- Prevents memory leaks

## That's It!
Now you know how the shell works:
1. Read command
2. Break into tokens
3. Organize into commands
4. Run commands
5. Show results
6. Repeat! 