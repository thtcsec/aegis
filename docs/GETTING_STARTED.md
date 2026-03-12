# Getting Started with Aegis

## Prerequisites

- CMake 3.20+
- C++17 compiler (GCC 9+, Clang 10+, MSVC 2019+)
- LLVM 14+ development libraries

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Your First Aegis Program

Create `hello.aeg`:

```aegis
fn main() {
    print("Hello, Aegis!")
}
```

Run it:

```bash
aegis run hello.aeg
```

## Security Features Example

```aegis
fn vulnerable_login() {
    input user_input
    query = "SELECT * FROM users WHERE name = " + user_input
    execute query  // WARNING: tainted input in SQL query
}

fn secure_login() {
    input user_input
    query = sql("SELECT * FROM users WHERE name = ?", user_input)
    execute query  // OK: parameterized query
}
```

The compiler will warn you about the vulnerability in `vulnerable_login`.

## Next Steps

- Read [ARCHITECTURE.md](ARCHITECTURE.md) to understand the compiler
- Check [examples/](../examples/) for more code samples
- Explore the security analysis features
