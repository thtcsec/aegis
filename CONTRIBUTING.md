# Contributing to Aegis

Thank you for your interest in contributing to Aegis!

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/your-username/aegis.git`
3. Create a branch: `git checkout -b feature/your-feature`
4. Make your changes
5. Run tests: `cmake --build build --target test`
6. Commit: `git commit -m "Add your feature"`
7. Push: `git push origin feature/your-feature`
8. Create a Pull Request

## Development Setup

### Prerequisites

- CMake 3.20+
- C++17 compiler
- LLVM 14+ development libraries
- Git

### Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running Tests

```bash
cd build
ctest
```

## Code Style

- Use C++17 features
- Follow the existing code style
- Add comments for complex logic
- Write tests for new features

### Naming Conventions

- Classes: `PascalCase`
- Functions: `camelCase`
- Variables: `snake_case`
- Constants: `UPPER_SNAKE_CASE`

## Project Structure

```
aegis-foundation/
├─ compiler/       # Compiler implementation
├─ runtime/        # Runtime system
├─ std/           # Standard library
├─ cli/           # CLI tools
├─ tests/         # Test suite
├─ docs/          # Documentation
└─ examples/      # Example programs
```

## Areas to Contribute

### Compiler

- Lexer improvements
- Parser enhancements
- AST optimizations
- Type system features

### Security Analysis

- New vulnerability detectors
- Taint analysis improvements
- Security rule definitions
- False positive reduction

### Standard Library

- Network protocols
- Cryptographic algorithms
- Database drivers
- Exploit tools

### Documentation

- Tutorials
- API documentation
- Security guides
- Example programs

### Testing

- Unit tests
- Integration tests
- Security test cases
- Fuzzing

## Reporting Issues

Use GitHub Issues to report:

- Bugs
- Security vulnerabilities (use private disclosure)
- Feature requests
- Documentation improvements

### Bug Report Template

```
**Description**
Clear description of the bug

**Steps to Reproduce**
1. Step 1
2. Step 2
3. ...

**Expected Behavior**
What should happen

**Actual Behavior**
What actually happens

**Environment**
- OS: 
- Compiler version:
- LLVM version:
```

## Security Vulnerabilities

If you discover a security vulnerability, please report it privately through GitHub Security Advisories or contact the maintainers directly.

## Code Review Process

1. All submissions require review
2. Maintainers will review your PR
3. Address feedback
4. Once approved, your PR will be merged

## License

By contributing, you agree that your contributions will be licensed under the Apache License 2.0.

## Questions?

Feel free to ask questions in:
- [GitHub Discussions](https://github.com/thtcsec/aegis/discussions)
- [GitHub Issues](https://github.com/thtcsec/aegis/issues)

## Project Maintainers

- **Trinh Hoang Tu** ([@thtcsec](https://github.com/thtcsec)) - Creator & Lead Developer
- **Aegis Foundation** - Project organization

Thank you for contributing to Aegis!
