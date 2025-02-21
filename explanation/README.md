# Welcome to Our Shell!

## What is This?
This is a simple shell program, like bash or zsh, but made from scratch! It can run commands, handle pipes, work with files, and manage environment variables.

## How Does It Work?

### The Big Picture
When you type a command, our shell:
1. Reads what you typed
2. Figures out what you want
3. Does it!

For example:
```bash
ls -l | grep .txt > output.txt
```
1. Reads: `ls -l | grep .txt > output.txt`
2. Understands:
   - Run `ls -l`
   - Send its output to `grep .txt`
   - Save grep's output to `output.txt`
3. Does it all in order!

### Main Parts

#### 1. Reading Commands (`main.c`)
- Gets your input (using readline)
- Remembers command history
- Handles Ctrl+C, Ctrl+D

#### 2. Understanding Words (`srcs/token/`)
Breaks your command into pieces:
```bash
echo "hello world" > output.txt
```
Becomes:
- Word: echo
- Word: "hello world"
- Redirect: >
- Word: output.txt

#### 3. Understanding Commands (`srcs/parse/`)
Takes the pieces and figures out:
- What command to run
- What arguments it needs
- Where to send output
- What files to use

#### 4. Making Commands Powerful (`srcs/expand/`)
Handles special features:
```bash
echo "Hello $USER"     # Uses your username
cd ~                  # Goes to your home
echo $PATH            # Shows program locations
```

#### 5. Running Commands (`srcs/exec/`)
- Runs the programs you ask for
- Connects pipes
- Handles files
- Creates new processes

#### 6. Built-in Commands (`srcs/builtins/`)
Special commands that are part of the shell:
- `cd`: Change directory
- `echo`: Print text
- `pwd`: Show current directory
- `export`: Set variables
- `unset`: Remove variables
- `env`: Show variables
- `exit`: Quit the shell

## How Commands Are Stored

### Command Structure
```c
struct s_cmd {
    char *cmd_name;         // Program to run
    char **cmd_args;        // Arguments for program
    struct s_cmd *next_cmd; // Next command (for pipes)
};
```

Example:
```bash
ls -l | grep .txt
```
Becomes:
```
Command 1:           Command 2:
cmd_name: "ls"       cmd_name: "grep"
cmd_args:            cmd_args:
  [0]: "ls"           [0]: ".txt"
  [1]: "-l"           [1]: NULL
  [2]: NULL           [2]: NULL
next_cmd: ------>    next_cmd: NULL
```

### Environment Variables
```c
struct s_envar {
    char *key;             // Variable name
    char *value;           // Variable value
    struct s_envar *next;  // Next variable
};
```

Example:
```
HOME=/home/user
↓
PATH=/usr/bin
↓
USER=rick
↓
NULL
```

## How It All Works Together

1. **Getting Input**
   ```bash
   $ ls -l | grep .txt > output.txt
   ```

2. **Breaking into Words**
   ```
   [ls] [-l] [|] [grep] [.txt] [>] [output.txt]
   ```

3. **Understanding Structure**
   ```
   Command: ls -l
   | (pipe to)
   Command: grep .txt
   > (output to file)
   File: output.txt
   ```

4. **Running Everything**
   - Start ls -l
   - Connect its output to grep
   - Start grep .txt
   - Send grep's output to output.txt
   - Wait for both to finish

## Want to Learn More?

Check out these detailed guides:
- [01-Overview.md](01-Overview.md): The big picture
- [02-Tokenization.md](02-Tokenization.md): Breaking commands into pieces
- [03-Parsing.md](03-Parsing.md): Understanding command structure
- [04-Execution.md](04-Execution.md): Running commands
- [05-Builtins.md](05-Builtins.md): Special shell commands
- [06-Expansion.md](06-Expansion.md): Making commands powerful

## Common Problems and Solutions

### 1. Command Not Found
- Check if command exists
- Check if it's in PATH
- Try using full path

### 2. Permission Denied
- Check file permissions
- Try with sudo (if you have it)
- Check directory permissions

### 3. Pipe/Redirection Problems
- Check file permissions
- Make sure directories exist
- Check disk space

### 4. Variable Problems
- Check variable exists: `env`
- Check spelling (case sensitive)
- Use quotes if spaces: "$VAR" 