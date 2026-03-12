# Aegis Architecture

## Compiler Pipeline

```
Aegis source (.aeg)
    ↓
Lexer (tokenization)
    ↓
Parser (syntax analysis)
    ↓
AST (abstract syntax tree)
    ↓
Semantic analysis (type checking, symbol resolution)
    ↓
Security analysis (taint tracking, vulnerability detection)
    ↓
LLVM IR generation
    ↓
LLVM optimization passes
    ↓
Machine code
```

## Security Analysis Engine

### Taint Analysis

Tracks data flow from untrusted sources:

1. **Taint Sources**: `input()`, `read()`, `recv()`, `getenv()`
2. **Taint Propagation**: Through assignments, operations, function calls
3. **Taint Sinks**: SQL queries, system commands, file paths

### Vulnerability Detection

- SQL Injection
- Command Injection
- Path Traversal
- XSS
- Buffer Overflow
- Use-After-Free

## Module Structure

### Compiler
- `lexer/`: Tokenization
- `parser/`: Syntax analysis
- `ast/`: AST representation
- `semantic/`: Type checking, symbol tables
- `security/`: Taint analysis, vulnerability detection
- `codegen/`: LLVM IR generation

### Runtime
- `memory/`: Memory management
- `sandbox/`: Sandboxing primitives
- `capability/`: Capability-based security

### Standard Library
- `net/`: Network primitives
- `crypto/`: Cryptographic functions
- `db/`: Database interfaces
- `exploit/`: Exploit automation tools
