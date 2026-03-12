# Aegis Language Syntax Specification

## Design Philosophy

Aegis syntax is designed to be:
- **Familiar**: C-style with modern improvements
- **Explicit**: Security-critical operations are clear
- **Minimal**: No unnecessary complexity
- **Safe by default**: Dangerous operations require explicit syntax

## Keywords

### Core Keywords
```
fn          // Function declaration
let         // Variable declaration (immutable by default)
mut         // Mutable variable
if          // Conditional
else        // Alternative branch
while       // Loop
for         // Iteration
return      // Return from function
break       // Break loop
continue    // Continue loop
```

### Type Keywords
```
int         // 64-bit signed integer
float       // 64-bit floating point
bool        // Boolean type
string      // UTF-8 string
byte        // 8-bit unsigned integer
array       // Array type (generic)
map         // Map type (generic)
tainted     // Tainted data type
safe        // Safe/sanitized data type
```

### Security Keywords
```
input       // Mark data as tainted (user input)
sql         // Parameterized SQL query
command     // Safe command execution
sanitize    // Sanitize tainted data
capability  // Declare capability requirement
sandbox     // Sandbox execution
```

### Cybersecurity DSL Keywords
```
scan        // Port/vulnerability scanning
sniff       // Network packet capture
exploit     // Exploit execution
fuzz        // Fuzzing operations
```

## Basic Syntax

### Variables

```aegis
// Explicit types
int port = 80
string host = "localhost"
bool secure = true
float pi = 3.14
byte data = 0xFF

// Type inference with let
let port = 80           // inferred as int
let host = "localhost"  // inferred as string
let secure = true       // inferred as bool

// Mutable variables
int mut counter = 0
counter = counter + 1

// Mutable with inference
let mut counter = 0
counter = counter + 1

// Collections
array<int> ports = [22, 80, 443]
map<string, int> config = {"port": 80}

// Security types
tainted<string> user_input = input()
safe<string> clean_data = sanitize(user_input)
```

### Functions

```aegis
fn function_name(param1: type1, param2: type2) -> return_type {
    // function body
    return value
}

// No return type
fn print_message(msg: string) {
    print(msg)
}

// Main entry point
fn main() {
    print("Hello, Aegis!")
}
```

### Control Flow

```aegis
// If statement
if condition {
    // code
} else if other_condition {
    // code
} else {
    // code
}

// While loop
while condition {
    // code
}

// For loop
for item in collection {
    // code
}

// Range
for i in range(0, 10) {
    // code
}
```

### Comments

```aegis
// Single line comment

/*
   Multi-line
   comment
*/
```

## Security Syntax

### Tainted Input

```aegis
// Mark input as tainted
let user_input = input()

// Compiler tracks taint through program
let query = "SELECT * FROM users WHERE id = " + user_input  // WARNING!
```

### Safe SQL

```aegis
// Parameterized query (safe)
let query = sql("SELECT * FROM users WHERE id = ?", user_id)
let result = db.execute(query)

// Named parameters
let query = sql(
    "SELECT * FROM users WHERE id = :id AND name = :name",
    {id: user_id, name: user_name}
)
```

### Safe Command Execution

```aegis
// Array-based command (safe)
let cmd = command("ping", ["-c", "4", target])
let result = execute(cmd)

// String concatenation (WARNING!)
let cmd = "ping " + target  // Compiler warning
```

### Sanitization

```aegis
let user_input = input()
let safe_input = sanitize(user_input, "alphanumeric")
let query = "SELECT * FROM users WHERE name = " + safe_input  // OK
```

## Cybersecurity DSL Syntax

### Port Scanning

```aegis
// Single port
scan "192.168.1.1" port 80

// Port range
scan "192.168.1.1" ports 1..1024

// Multiple targets
scan ["192.168.1.1", "192.168.1.2"] port 80

// With options
scan "192.168.1.1" port 80 {
    timeout: 5s
    protocol: tcp
}
```

### Network Sniffing

```aegis
// Basic sniffing
sniff "eth0"

// With filter
sniff "eth0" filter "tcp port 80"

// With callback
sniff "eth0" filter "tcp" {
    on_packet(packet) {
        print(packet.src + " -> " + packet.dst)
    }
}
```

### Exploitation

```aegis
// Load exploit module
exploit "buffer_overflow" {
    target: "192.168.1.100"
    port: 9999
    payload: shellcode
}
```

### Fuzzing

```aegis
// Fuzz a function
fuzz test_parser {
    input: random_string(1..1000)
    iterations: 10000
    detect_crashes: true
}
```

## Capability System

```aegis
// Declare required capabilities
capability network
capability filesystem(read="/tmp", write="/tmp/output")

fn main() {
    // Can use network (capability declared)
    let response = http.get("https://example.com")
    
    // Can read from /tmp
    let data = read("/tmp/data.txt")
    
    // ERROR: no write capability for /etc
    write("/etc/config", data)
}
```

## Module System

```aegis
// Import module
import std.net
import std.crypto
import std.db

// Use module
let hash = crypto.sha256("data")
let socket = net.connect("example.com", 80)
```

## Type System

```aegis
// Basic types
let x: int = 42
let name: string = "aegis"
let flag: bool = true

// Arrays
let numbers: [int] = [1, 2, 3, 4, 5]
let names: [string] = ["alice", "bob"]

// Structs (future)
struct User {
    id: int
    name: string
    email: string
}
```

## Operators

### Arithmetic
```
+   // Addition
-   // Subtraction
*   // Multiplication
/   // Division
%   // Modulo
```

### Comparison
```
==  // Equal
!=  // Not equal
<   // Less than
>   // Greater than
<=  // Less than or equal
>=  // Greater than or equal
```

### Logical
```
&&  // Logical AND
||  // Logical OR
!   // Logical NOT
```

### Assignment
```
=   // Assignment
+=  // Add and assign
-=  // Subtract and assign
*=  // Multiply and assign
/=  // Divide and assign
```

## String Operations

```aegis
// Concatenation
let full_name = first_name + " " + last_name

// Interpolation (future)
let message = "Hello, ${name}!"

// Length
let len = length(str)
```

## Error Handling (Future)

```aegis
// Result type
fn divide(a: int, b: int) -> Result<int, string> {
    if b == 0 {
        return error("Division by zero")
    }
    return ok(a / b)
}

// Pattern matching
let result = divide(10, 2)
match result {
    ok(value) => print(value)
    error(msg) => print("Error: " + msg)
}
```

## Complete Example

```aegis
// Secure web authentication
import std.db
import std.crypto

capability network
capability database

fn authenticate(username: string, password: string) -> bool {
    // Hash password
    let password_hash = crypto.sha256(password)
    
    // Safe parameterized query
    let query = sql(
        "SELECT * FROM users WHERE username = ? AND password_hash = ?",
        username,
        password_hash
    )
    
    let result = db.execute(query)
    
    if result.count() > 0 {
        return true
    }
    
    return false
}

fn main() {
    // Get user input (marked as tainted)
    let username = input()
    let password = input()
    
    // Authenticate
    if authenticate(username, password) {
        print("Login successful!")
    } else {
        print("Login failed!")
    }
}
```

## Syntax Rules

1. **Statements end with newline** (no semicolons required)
2. **Blocks use braces** `{ }`
3. **Indentation is recommended** but not enforced
4. **Variables are immutable by default** (use `mut` for mutable)
5. **Type inference** where possible
6. **Explicit types** for function parameters and return values

## Reserved for Future

- `async` / `await` - Asynchronous operations
- `struct` / `enum` - Custom types
- `trait` / `impl` - Interfaces and implementations
- `match` - Pattern matching
- `unsafe` - Unsafe operations block

## Anti-Patterns (Compiler Warnings)

```aegis
// Bad: String concatenation in SQL
let query = "SELECT * FROM users WHERE id = " + user_id

// Good: Parameterized query
let query = sql("SELECT * FROM users WHERE id = ?", user_id)

// Bad: Command string concatenation
let cmd = "ping " + target

// Good: Array-based command
let cmd = command("ping", [target])

// Bad: Unvalidated file path
let file = open(user_path)

// Good: Validated path
let safe_path = validate_path(user_path, "/var/www/uploads")
let file = open(safe_path)
```

## Grammar Summary (EBNF-like)

```
program         = { function_decl | import_stmt }
function_decl   = "fn" identifier "(" params ")" [ "->" type ] block
params          = [ param { "," param } ]
param           = identifier ":" type
block           = "{" { statement } "}"
statement       = var_decl | assignment | if_stmt | while_stmt | 
                  for_stmt | return_stmt | expr_stmt | scan_stmt | sniff_stmt
var_decl        = "let" [ "mut" ] identifier [ ":" type ] "=" expression
if_stmt         = "if" expression block [ "else" ( if_stmt | block ) ]
while_stmt      = "while" expression block
for_stmt        = "for" identifier "in" expression block
return_stmt     = "return" [ expression ]
scan_stmt       = "scan" string "port" ( integer | range )
sniff_stmt      = "sniff" string [ "filter" string ]
expression      = literal | identifier | binary_op | call | sql_expr | command_expr
sql_expr        = "sql" "(" string "," expression { "," expression } ")"
command_expr    = "command" "(" string "," array ")"
```

---

**Note**: This syntax is designed for Phase 1-3. Advanced features will be added in later phases based on community feedback.
