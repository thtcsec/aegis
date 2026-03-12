# Aegis Security Features

## Overview

Aegis is designed with security as a first-class concern. The compiler performs static analysis to detect common vulnerabilities before your code runs.

## Taint Analysis

### What is Taint Analysis?

Taint analysis tracks data from untrusted sources (user input, network data, files) through your program to ensure it's properly sanitized before use in sensitive operations.

### Taint Sources

Data from these sources is automatically marked as "tainted":

- `input()` - User input
- `read()` - File reads
- `recv()` - Network receives
- `getenv()` - Environment variables
- `http.get()` - HTTP responses

### Taint Sinks

These operations trigger warnings if used with tainted data:

- SQL queries (without parameterization)
- System commands
- File path operations
- Code evaluation

### Example

```aegis
fn vulnerable() {
    input user_data  // Tainted
    query = "SELECT * FROM users WHERE id = " + user_data  // WARNING!
    execute query
}

fn secure() {
    input user_data  // Tainted
    query = sql("SELECT * FROM users WHERE id = ?", user_data)  // OK
    execute query
}
```

## SQL Injection Prevention

### Detection Rules

1. String concatenation with tainted input in SQL
2. Non-parameterized queries with user input
3. Dynamic SQL construction

### Safe Patterns

```aegis
// Parameterized query
query = sql("SELECT * FROM users WHERE id = ?", user_id)

// Named parameters
query = sql("SELECT * FROM users WHERE id = :id", {id: user_id})

// ✗ String concatenation
query = "SELECT * FROM users WHERE id = " + user_id

// ✗ String interpolation
query = "SELECT * FROM users WHERE id = ${user_id}"
```

## Command Injection Prevention

### Detection Rules

1. Shell command execution with tainted input
2. Unescaped user input in system calls

### Safe Patterns

```aegis
// Array-based command
cmd = command("ping", ["-c", "4", target])

// Sanitized input
safe_target = sanitize_hostname(target)
cmd = command("ping", [safe_target])

// ✗ String concatenation
cmd = "ping " + target
```

## Path Traversal Prevention

### Detection Rules

1. File operations with unsanitized paths
2. Directory traversal patterns (../)

### Safe Patterns

```aegis
// Validated path
safe_path = validate_path(user_path, "/var/www/uploads")
file = open(safe_path)

// ✗ Direct user input
file = open(user_path)
```

## Memory Safety

### Automatic Checks

- Bounds checking on array access
- Null pointer detection
- Use-after-free detection
- Double-free detection

### Example

```aegis
fn safe_array_access() {
    arr = [1, 2, 3, 4, 5]
    
    // Compiler checks bounds
    value = arr[10]  // ERROR: index out of bounds
}
```

## Capability-Based Security

### Principle

Code must explicitly declare required capabilities:

```aegis
capability network
capability filesystem(read="/tmp")

fn main() {
    // OK: network capability declared
    response = http.get("https://example.com")
    
    // OK: filesystem read capability for /tmp
    data = read("/tmp/data.txt")
    
    // ERROR: no write capability
    write("/tmp/output.txt", data)
}
```

## Sandboxing

### Runtime Isolation

```aegis
sandbox {
    max_memory: 100MB
    max_cpu: 50%
    network: false
    filesystem: read_only
}

fn untrusted_code() {
    // Runs in sandbox with restrictions
}
```

## Security Levels

### Level 1: Warnings

Non-critical issues that should be reviewed:

- Potential SQL injection
- Possible command injection
- Suspicious patterns

### Level 2: Errors

Critical security issues that prevent compilation:

- Confirmed SQL injection
- Buffer overflow
- Use-after-free

### Configuration

```toml
# aegis.toml
[security]
level = "strict"  # strict, normal, permissive
fail_on_warning = true
```

## Best Practices

1. Always use parameterized queries
2. Validate and sanitize all user input
3. Use capability declarations
4. Enable strict security mode
5. Run security checks before deployment

```bash
aegis check --strict main.aeg
```

## Security Audit

Generate security report:

```bash
aegis audit main.aeg --output report.html
```

Report includes:
- Taint flow diagrams
- Vulnerability locations
- Severity ratings
- Remediation suggestions
