# Part 5: Error Diagnostics (3 marks)

## Overview

This implementation provides comprehensive error diagnostics during parsing with informative messages to help identify and locate problems in the input.

## Features

### 1. Enhanced Error Reporting

- **Line Number Tracking**: Uses `%option yylineno` to track line numbers
- **Error Categorization**: Distinguishes between syntax and semantic errors
- **Error Counting**: Tracks total errors and warnings
- **Visual Formatting**: Uses box-drawing characters for clear error display

### 2. Error Types

#### Syntax Errors
Detected during parsing when input doesn't match grammar rules:
- Missing semicolons
- Unmatched parentheses or braces
- Invalid token sequences
- Malformed statements

#### Semantic Errors
Detected during semantic analysis:
- Negative grid dimensions
- Negative coordinates
- Division/modulo by zero
- Negative repeat counts
- Out-of-range values

#### Warnings
Non-fatal issues that don't stop parsing:
- Zero-dimension grids
- Zero-step movements
- Zero-iteration repeats

### 3. Error Recovery

Uses Bison's error recovery mechanism:
- `error` productions in grammar
- `yyerrok` to resume parsing
- Skips to synchronization points (semicolons, braces)
- Continues parsing to find multiple errors

## Implementation Details

### Key Functions

```c
void syntax_error(const char *msg, const char *token)
void semantic_error(const char *msg)
void warning_message(const char *msg)
```

### Bison Directives

```yacc
%define parse.error verbose  // Better error messages
%locations                   // Location tracking
%option yylineno            // Line number tracking in lexer
```

### Error Recovery Points

Grammar includes error productions at strategic locations:
- Statement lists
- Expression parsing
- Block structures
- Individual statement types

## Sample Output

### Semantic Error Example

```
╔════════════════════════════════════════════════════════════════╗
║                     SEMANTIC ERROR #1                         ║
╚════════════════════════════════════════════════════════════════╝

Location: Line 7
Error:    Grid dimensions must be non-negative

Found: grid(-10, 20)
Expected: Both dimensions >= 0
```

### Syntax Error Example

```
╔════════════════════════════════════════════════════════════════╗
║                      SYNTAX ERROR #2                          ║
╚════════════════════════════════════════════════════════════════╝

Location: Line 11
Error:    Invalid spawn statement
Token:    ';'

Possible causes:
  • Missing semicolon (;) at the end of statement
  • Unmatched parentheses () or braces {}
  • Invalid token or keyword
  • Missing required keyword or operator

Expected: spawn name at (x, y);
      or: spawn name as alias at (x, y);
```

### Warning Example

```
⚠ Warning #1 (Line 15): Movement with 0 steps has no effect
```

### Summary Output

```
╔════════════════════════════════════════════════════════════════╗
║                       PARSING SUMMARY                          ║
╚════════════════════════════════════════════════════════════════╝

✗ Parsing failed!
  • 7 error(s) detected
  • 2 warning(s) issued

Please fix the errors and try again.
```

## Building and Testing

### Compile:
```bash
cd Q5_Error_Diagnostics
bison -d golem.y
flex golem.l
gcc -o golem golem.tab.c lex.yy.c -lfl
```

### Test with Valid Input:
```bash
echo "grid(10, 10) {}" | ./golem
```

### Test with Errors:
```bash
./golem test_errors.golem
```

## Error Diagnostic Features

### 1. Contextual Information
- Exact line number where error occurred
- Token that caused the error
- Description of what went wrong

### 2. Helpful Suggestions
- Possible causes of the error
- Expected syntax format
- Common mistakes to avoid

### 3. Multiple Error Detection
- Doesn't stop at first error
- Reports multiple errors in one pass
- Helps fix all issues at once

### 4. Error Recovery
- Attempts to continue parsing after errors
- Synchronizes at statement boundaries
- Provides comprehensive error list

## Test Cases

The `test_errors.golem` file includes:

1. **Missing semicolon**
2. **Negative dimensions** (semantic error)
3. **Invalid spawn syntax** (missing keyword)
4. **Division by zero** (semantic error)
5. **Negative repeat count** (semantic error)

## Comparison with Basic Parser

| Feature | Basic Parser | Enhanced Diagnostics |
|---------|-------------|---------------------|
| Line numbers | ❌ | ✅ |
| Error categories | ❌ | ✅ (Syntax/Semantic/Warning) |
| Error recovery | ❌ | ✅ |
| Multiple errors | ❌ | ✅ |
| Suggestions | ❌ | ✅ |
| Visual formatting | ❌ | ✅ |
| Error counting | ❌ | ✅ |

## Files

- `golem.y`: Grammar with enhanced error handling
- `golem.l`: Lexer with line number tracking
- `test_errors.golem`: Test file with various errors
- `README.md`: This documentation

## Key Improvements

1. **User-Friendly**: Clear, formatted error messages
2. **Informative**: Provides context and suggestions
3. **Comprehensive**: Reports multiple errors, not just first one
4. **Professional**: Follows compiler error reporting best practices
5. **Recoverable**: Continues parsing after errors when possible
