# Variable and Word Expansion

## Overview

The expansion component (`srcs/expand/`) handles various types of expansions in the shell, including environment variables, wildcards, and special parameters. This process transforms the raw input into its final form before execution.

## Types of Expansion

### 1. Environment Variable Expansion
- Expands `$VAR` and `${VAR}` syntax
- Handles special variables ($?, $0, etc.)
- Processes quoted strings
- Manages undefined variables

### 2. Tilde Expansion
- Expands `~` to home directory
- Handles `~user` expansion
- Processes in specific contexts
- Maintains path integrity

### 3. Word Splitting
- Splits expanded results
- Handles IFS (Internal Field Separator)
- Preserves quoted strings
- Manages special cases

## Implementation Details

### Expansion Structure
```c
typedef struct s_expand {
    char    *input;         // Input string
    char    *result;       // Expanded result
    int     in_quotes;     // Quote state
    int     in_dquotes;    // Double quote state
    size_t  pos;           // Current position
} t_expand;
```

## Expansion Process

1. **Variable Recognition**
   - Identify variable markers ($)
   - Parse variable names
   - Handle special cases
   - Process braces ${...}

2. **Quote Processing**
   - Handle single quotes (no expansion)
   - Process double quotes (limited expansion)
   - Manage escape characters
   - Preserve quote integrity

3. **Value Substitution**
   - Look up variable values
   - Handle undefined variables
   - Process special parameters
   - Manage expansion results

## Key Functions

### 1. Variable Expansion
```c
// Main expansion function
char *expand_variables(char *input, t_minishell *minishell);

// Process single variable
char *expand_single_var(char *var_name, t_minishell *minishell);
```

### 2. Quote Handling
```c
// Process quoted strings
char *handle_quotes(char *input, size_t *pos);

// Handle escape sequences
char *process_escapes(char *input, size_t *pos);
```

### 3. Word Processing
```c
// Split words after expansion
char **split_words(char *expanded);

// Handle field separation
char **field_splitting(char *input);
```

## Special Cases

### 1. Special Parameters
- `$?` - Last command status
- `$0` - Shell name
- `$$` - Shell PID
- `$!` - Last background PID

### 2. Brace Expansion
- `${VAR}`
- `${VAR:-default}`
- `${VAR:=default}`
- `${VAR:?error}`

### 3. Quote Handling
- Single quotes (no expansion)
- Double quotes (variable expansion)
- Escaped characters
- Nested quotes

## Error Handling

1. **Variable Errors**
   - Undefined variables
   - Invalid names
   - Syntax errors
   - Recursion limits

2. **Quote Errors**
   - Unclosed quotes
   - Invalid escapes
   - Nested quote issues
   - Syntax problems

3. **Memory Management**
   - Allocation failures
   - Buffer management
   - Memory leaks
   - Resource cleanup

## Integration

The expansion module interacts with:
1. Parser
2. Environment management
3. Command execution
4. Error handling

## Examples

### Variable Expansion
```bash
echo $HOME           # Basic expansion
echo ${PATH}         # Braced expansion
echo "$USER"        # Quoted expansion
echo '${HOME}'      # No expansion (single quotes)
```

### Special Cases
```bash
echo $?             # Exit status
echo "~"           # Tilde in quotes
echo $VAR-suffix   # Variable with suffix
echo "${VAR:-default}"  # Default value
```

## Performance Optimization

The expansion module is optimized for:
1. **Memory Usage**
   - Efficient string handling
   - Minimal copying
   - Buffer reuse
   - Dynamic allocation

2. **Processing Speed**
   - Quick lookups
   - Efficient parsing
   - Minimal recursion
   - Cached results

3. **Resource Management**
   - Smart buffer sizing
   - Memory pooling
   - Resource reuse
   - Cleanup optimization

## Security Considerations

1. **Input Validation**
   - Sanitize variable names
   - Check path expansions
   - Validate substitutions
   - Handle overflow

2. **Environment Safety**
   - Protect sensitive variables
   - Validate expansions
   - Handle special cases
   - Prevent injection

3. **Error Prevention**
   - Bounds checking
   - Null handling
   - Quote validation
   - Syntax verification

## Testing Scenarios

1. **Basic Cases**
   ```bash
   echo $HOME
   echo ${PATH}
   echo "$USER"
   ```

2. **Complex Cases**
   ```bash
   echo ${VAR:-default}
   echo "$VAR"suffix
   echo '${HOME}'
   ```

3. **Error Cases**
   ```bash
   echo ${undefined}
   echo "${"
   echo "'unclosed
   ```

## Implementation Notes

1. **Parsing Strategy**
   - Character-by-character processing
   - State machine approach
   - Context awareness
   - Error recovery

2. **Memory Management**
   - Dynamic allocation
   - Buffer management
   - Cleanup routines
   - Resource tracking

3. **Integration Points**
   - Parser coordination
   - Environment access
   - Error propagation
   - State management 