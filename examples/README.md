# Aegis Examples

This directory contains example programs demonstrating Aegis features.

## Basic Examples

- `hello.aeg` - Hello World program
- `taint_example.aeg` - Taint analysis demonstration

## Security Examples

- `secure_db.aeg` - Safe database operations with parameterized queries
- `network_scan.aeg` - Port scanning with network primitives

## Running Examples

```bash
# Run an example
aegis run examples/hello.aeg

# Check security
aegis check examples/secure_db.aeg

# Build executable
aegis build examples/network_scan.aeg -o scanner
```

## Learning Path

1. Start with `hello.aeg` to understand basic syntax
2. Study `taint_example.aeg` to see security warnings
3. Explore `secure_db.aeg` for SQL injection prevention
4. Try `network_scan.aeg` for network programming

## Contributing Examples

Feel free to contribute more examples! See [CONTRIBUTING.md](../CONTRIBUTING.md).
