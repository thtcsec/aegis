# Changelog

All notable changes to Aegis will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Initial project structure
- Lexer implementation with token recognition
- Type system v1 design
  - Primitive types: int, float, bool, string, byte
  - Generic types: array<T>, map<K,V>
  - Security types: tainted<T>, safe<T>
- Syntax specification (SYNTAX.md)
- Formal grammar definition (GRAMMAR.md)
- Type system documentation (TYPE_SYSTEM.md)
- Project scope definition (SCOPE.md)
- Security analysis module skeleton
  - Taint analysis engine
  - SQL injection checker
  - Vulnerability detector
- Example programs demonstrating:
  - Taint analysis
  - Secure database operations
  - Network scanning
  - Type system features
  - Cybersecurity DSL
- Documentation
  - Getting started guide (English)
  - Getting started guide (Vietnamese)
  - Architecture overview
  - Security features documentation
  - Development roadmap
  - Contributing guidelines
- GitHub templates
  - Issue templates (bug, feature, security)
  - Pull request template
  - CI/CD workflow
- Apache 2.0 License

### Changed
- Updated syntax to use explicit types and `let` for inference
- Refined variable declaration syntax
- Enhanced lexer with all operators and delimiters

### Security
- Designed taint tracking system for untrusted data
- SQL injection prevention through parameterized queries
- Command injection detection

## [0.1.0] - TBD

### Planned
- Complete lexer implementation
- Parser with AST generation
- Basic interpreter
- Type checking and inference
- Security analysis (Phase 3)

---

## Version History

- **v0.1.0** (Planned) - Phase 1: Foundation
  - Toy compiler with lexer, parser, interpreter
  - Basic type system
  - Simple security checks

- **v0.2.0** (Future) - Phase 2: LLVM Integration
  - LLVM IR generation
  - Native compilation
  - Optimization passes

- **v0.3.0** (Future) - Phase 3: Security Analysis
  - Complete taint analysis
  - Vulnerability detection
  - Security reporting

- **v1.0.0** (Future) - Production Ready
  - Stable language specification
  - Complete standard library
  - Full security analysis
  - Production-ready tooling

---

**Note**: This project is in early development. Breaking changes are expected until v1.0.0.
