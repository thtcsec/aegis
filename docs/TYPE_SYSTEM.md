# Aegis Type System v1

## Design Philosophy

Aegis uses a **hybrid type system**:
- **Explicit types** for clarity and security
- **Type inference** for convenience (with `let`)
- **Security-aware types** for taint tracking

## Primitive Types

### Basic Types

```aegis
int       // 64-bit signed integer
float     // 64-bit floating point
bool      // Boolean (true/false)
string    // UTF-8 string
byte      // 8-bit unsigned integer
```

### Examples

```aegis
// Explicit types
int port = 80
float pi = 3.14159
bool is_secure = true
string host = "localhost"
byte data = 0xFF

// Type inference with let
let port = 80           // inferred as int
let pi = 3.14           // inferred as float
let is_secure = true    // inferred as bool
let host = "localhost"  // inferred as string
```

## Composite Types

### Arrays

```aegis
// Syntax: array<T>
array<int> ports = [22, 80, 443]
array<string> hosts = ["localhost", "example.com"]

// Type inference
let ports = [22, 80, 443]  // inferred as array<int>
```

### Maps

```aegis
// Syntax: map<K, V>
map<string, int> port_map = {
    "ssh": 22,
    "http": 80,
    "https": 443
}

// Type inference
let port_map = {"ssh": 22, "http": 80}  // inferred as map<string, int>
```

### Structs (Future)

```aegis
struct User {
    int id
    string name
    string email
}

User user = User{
    id: 1,
    name: "admin",
    email: "admin@example.com"
}
```

## Security-Aware Types

### Tainted Types

Track untrusted data through the program:

```aegis
// Explicit tainted type
tainted<string> user_input = input()

// Compiler tracks taint
string query = "SELECT * FROM users WHERE id = " + user_input  // WARNING!
```

### Safe Types

Mark data as sanitized:

```aegis
tainted<string> user_input = input()
safe<string> clean_input = sanitize(user_input)

// Now safe to use
string query = "SELECT * FROM users WHERE id = " + clean_input  // OK
```

### Type Conversion

```aegis
// Tainted to Safe (requires sanitization)
tainted<string> dirty = input()
safe<string> clean = sanitize(dirty)

// Safe to Tainted (implicit, always allowed)
safe<string> clean = "hello"
tainted<string> dirty = clean  // OK
```

## Type Inference Rules

### When Inference Works

```aegis
let x = 10              // int
let y = 3.14            // float
let name = "aegis"      // string
let flag = true         // bool
let ports = [80, 443]   // array<int>
```

### When Explicit Types Required

```aegis
// Function parameters (always explicit)
fn connect(host: string, port: int) {
    // ...
}

// Function return types (always explicit)
fn get_port() -> int {
    return 80
}

// Ambiguous cases
int x = 0  // Could be int or float, must specify
```

## Type Checking Rules

### Strong Typing

No implicit conversions:

```aegis
int x = 10
string y = x  // ERROR: cannot convert int to string

// Must use explicit conversion
string y = to_string(x)  // OK
```

### Type Compatibility

```aegis
// Same types
int a = 10
int b = a  // OK

// Compatible types (taint tracking)
safe<string> clean = "hello"
tainted<string> dirty = clean  // OK (safe -> tainted)

tainted<string> dirty = input()
safe<string> clean = dirty  // ERROR: must sanitize first
```

## Variable Declaration Syntax

### Explicit Type Declaration

```aegis
// Pattern: TYPE IDENTIFIER = expression
int port = 80
string host = "localhost"
bool secure = true
array<int> ports = [22, 80, 443]
map<string, int> config = {"port": 80}
```

### Type Inference

```aegis
// Pattern: let IDENTIFIER = expression
let port = 80
let host = "localhost"
let secure = true
let ports = [22, 80, 443]
let config = {"port": 80}
```

### Mutable Variables

```aegis
// Explicit type
int mut counter = 0
counter = counter + 1

// Type inference
let mut counter = 0
counter = counter + 1
```

## Grammar Rules

### Variable Declaration

```
var_decl
    : TYPE IDENTIFIER
    | TYPE IDENTIFIER '=' expression
    | TYPE 'mut' IDENTIFIER '=' expression
    | 'let' IDENTIFIER '=' expression
    | 'let' 'mut' IDENTIFIER '=' expression
    ;

TYPE
    : 'int'
    | 'float'
    | 'bool'
    | 'string'
    | 'byte'
    | 'array' '<' TYPE '>'
    | 'map' '<' TYPE ',' TYPE '>'
    | 'tainted' '<' TYPE '>'
    | 'safe' '<' TYPE '>'
    ;
```

## Complete Examples

### Example 1: Basic Types

```aegis
fn main() {
    int port = 80
    string host = "localhost"
    bool secure = false
    
    let addr = host + ":" + to_string(port)
    print(addr)
}
```

### Example 2: Collections

```aegis
fn scan_ports(target: string) {
    array<int> common_ports = [21, 22, 80, 443, 3306]
    
    for port in common_ports {
        scan target port port
    }
}

fn main() {
    scan_ports("192.168.1.1")
}
```

### Example 3: Security Types

```aegis
fn login(username: string, password: string) -> bool {
    // User input is tainted
    tainted<string> user_input = input()
    
    // Must use parameterized query
    let query = sql(
        "SELECT * FROM users WHERE username = ?",
        user_input
    )
    
    let result = db.execute(query)
    return result.count() > 0
}
```

### Example 4: Type Inference

```aegis
fn calculate() {
    // Explicit types
    int a = 10
    int b = 20
    int sum = a + b
    
    // Type inference
    let x = 10
    let y = 20
    let total = x + y
    
    print(to_string(sum))
    print(to_string(total))
}
```

### Example 5: Maps

```aegis
fn main() {
    map<string, int> port_config = {
        "ssh": 22,
        "http": 80,
        "https": 443,
        "mysql": 3306
    }
    
    let ssh_port = port_config["ssh"]
    print("SSH port: " + to_string(ssh_port))
}
```

## Type System Features

### Supported in v1

- Primitive types (int, float, bool, string, byte)
- Arrays with type parameters
- Maps with key/value types
- Type inference with `let`
- Explicit type annotations
- Tainted/Safe types for security
- Strong typing (no implicit conversions)

### Future (v2+)

- Structs and enums
- Generics for functions
- Traits/interfaces
- Union types
- Optional types (`option<T>`)
- Result types (`result<T, E>`)
- Type aliases

## Type Conversion Functions

```aegis
// String conversions
to_string(x: int) -> string
to_string(x: float) -> string
to_string(x: bool) -> string

// Numeric conversions
to_int(x: string) -> int
to_float(x: string) -> float

// Array conversions
to_array(x: string) -> array<byte>
```

## Best Practices

### 1. Use Explicit Types for Public APIs

```aegis
// Good: Clear function signature
fn connect(host: string, port: int) -> bool {
    // ...
}

// Bad: Unclear what types are expected
fn connect(host, port) {
    // ...
}
```

### 2. Use Type Inference for Local Variables

```aegis
fn process_data() {
    // Good: Obvious from context
    let count = 0
    let name = "test"
    
    // Unnecessary verbosity
    int count = 0
    string name = "test"
}
```

### 3. Always Annotate Security-Critical Types

```aegis
// Good: Explicit taint tracking
tainted<string> user_input = input()

// Bad: Unclear if tainted
let user_input = input()
```

## Type System Summary

```
Aegis Type System = Simple + Secure + Practical

Simple:
  - Only 5 primitive types
  - Generic arrays and maps
  - Type inference where helpful

Secure:
  - Tainted/Safe types
  - Strong typing
  - No implicit conversions

Practical:
  - Explicit when needed
  - Inferred when obvious
  - Security-aware by default
```

---

**Design Goal**: Keep it simple, make it secure, avoid complexity.
