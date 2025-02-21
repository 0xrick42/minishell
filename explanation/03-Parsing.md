# Understanding Commands (Parsing)

## What is Parsing?
After breaking the command into tokens, the shell needs to understand what to do with them. This is called parsing. It's like taking the words of a sentence and figuring out the meaning.

## What the Parser Creates

### Command Structure
Each command is stored in this structure:
```c
typedef struct s_cmd {
    char            *cmd_name;      // The program to run (like "ls" or "echo")
    char            **cmd_args;     // All arguments including the program name
    struct s_cmd    *next_cmd;      // Next command (for pipes)
} t_cmd;
```

For example, `ls -l` becomes:
```c
cmd_name = "ls"
cmd_args = ["ls", "-l", NULL]
next_cmd = NULL
```

## How Parsing Works (Step by Step)

### Step 1: Initial Check
```c
bool ft_parsing(t_minishell *minishell, char *input)
```
1. Checks for unclosed quotes: `echo "hello`
2. Checks for unsupported characters: `ls ; cat`
3. Makes sure the input isn't empty

### Step 2: Building Commands
```c
bool ft_cmd_struct(char *input, t_minishell *minishell)
```
1. Takes the token list
2. Groups tokens into commands
3. Handles pipes and redirections
4. Creates command nodes

### Step 3: Processing Arguments
```c
char **ft_split_cmd_args(char *cmd_cell)
```
1. Collects all arguments for a command
2. Handles quotes properly
3. Creates NULL-terminated array
4. Manages memory carefully

### Step 4: Connecting Commands
```c
bool ft_cmd_list(char *cmd_cell, t_minishell *minishell)
```
1. Links commands together for pipes
2. Sets up input/output connections
3. Validates the command structure
4. Prepares for execution

## Examples with Step-by-Step Breakdown

### 1. Simple Command
```bash
ls -l
```
Parser steps:
1. Create new command node
2. Set cmd_name to "ls"
3. Create cmd_args array: ["ls", "-l", NULL]
4. Set next_cmd to NULL

Result:
```
Command Node
├── cmd_name: "ls"
├── cmd_args: ["ls", "-l", NULL]
└── next_cmd: NULL
```

### 2. Pipeline
```bash
echo hello | grep o
```
Parser steps:
1. Create first command node (echo)
   - cmd_name: "echo"
   - cmd_args: ["echo", "hello", NULL]
2. Create second command node (grep)
   - cmd_name: "grep"
   - cmd_args: ["grep", "o", NULL]
3. Link them together:
   - echo node's next_cmd → grep node

Result:
```
Command 1           Command 2
[echo hello] -----> [grep o]
```

### 3. Command with Redirections
```bash
cat < input.txt > output.txt
```
Parser steps:
1. Create command node
   - cmd_name: "cat"
   - cmd_args: ["cat", NULL]
2. Note input redirection from "input.txt"
3. Note output redirection to "output.txt"

Result:
```
Command Node
├── cmd_name: "cat"
├── cmd_args: ["cat", NULL]
└── next_cmd: NULL
(Redirections handled during execution)
```

## Error Checking

The parser watches for these problems:

### 1. Syntax Errors
- Empty commands: `ls |`
- Multiple pipes: `ls ||| cat`
- Wrong redirection order: `> file cat`
- Missing filenames: `cat >`

### 2. Memory Problems
- Can't allocate new nodes
- Can't copy strings
- Can't create argument arrays

### 3. Command Problems
- Invalid command names
- Too many arguments
- Bad redirection combinations

## Memory Management

The parser is careful with memory:

### 1. Creating Things
```c
// Make a new command
bool ft_create_cmd(t_minishell *minishell, char **cmd_args)
{
    // Allocates memory for command
    // Copies all strings
    // Links into command list
    // Handles any errors
}
```

### 2. Cleaning Up
```c
// Clean up commands
void ft_free_cmd_list(t_cmd *cmd_list)
{
    // Frees all command nodes
    // Frees all argument arrays
    // Frees all strings
    // Sets everything to NULL
}
```

## What's Next?

After parsing:
1. The executor gets the command list
2. It sets up any pipes needed
3. It handles any redirections
4. It runs each command in order

## Common Questions

### Q: What happens to quotes?
A: Quotes are kept during parsing but removed before execution:
```bash
echo "hello world"  →  cmd_args: ["echo", "hello world", NULL]
```

### Q: How are pipes handled?
A: Each command in a pipe becomes its own node, linked together:
```bash
cmd1 | cmd2 | cmd3  →  [cmd1] -> [cmd2] -> [cmd3]
```

### Q: What about redirections?
A: Redirections are noted during parsing and set up during execution:
```bash
cat < file  →  Command knows to read from "file" instead of keyboard
``` 