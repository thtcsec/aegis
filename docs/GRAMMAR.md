# Aegis Formal Grammar

## Lexical Grammar

### Tokens

```
// Keywords
KEYWORD     = "fn" | "let" | "mut" | "if" | "else" | "while" | "for" | 
              "return" | "break" | "continue" | "int" | "string" | "bool" |
              "input" | "sql" | "command" | "scan" | "sniff" | "capability"

// Identifiers
IDENTIFIER  = LETTER ( LETTER | DIGIT | "_" )*
LETTER      = "a".."z" | "A".."Z"
DIGIT       = "0".."9"

// Literals
INTEGER     = DIGIT+
STRING      = '"' ( ~["\] | ESCAPE )* '"'
ESCAPE      = "\" ( "n" | "t" | "r" | '"' | "\" )
BOOLEAN     = "true" | "false"

// Operators
PLUS        = "+"
MINUS       = "-"
STAR        = "*"
SLASH       = "/"
PERCENT     = "%"
EQ          = "=="
NE          = "!="
LT          = "<"
GT          = ">"
LE          = "<="
GE          = ">="
AND         = "&&"
OR          = "||"
NOT         = "!"
ASSIGN      = "="

// Delimiters
LPAREN      = "("
RPAREN      = ")"
LBRACE      = "{"
RBRACE      = "}"
LBRACKET    = "["
RBRACKET    = "]"
COMMA       = ","
COLON       = ":"
ARROW       = "->"
DOT         = "."
RANGE       = ".."

// Whitespace and Comments
WHITESPACE  = [ \t\r\n]+
COMMENT     = "//" ~[\r\n]* | "/*" .*? "*/"
```

## Syntax Grammar

### Program Structure

```
program
    : declaration*
    ;

declaration
    : function_declaration
    | import_declaration
    | capability_declaration
    ;

import_declaration
    : "import" module_path
    ;

module_path
    : IDENTIFIER ( "." IDENTIFIER )*
    ;

capability_declaration
    : "capability" IDENTIFIER ( "(" capability_args ")" )?
    ;

capability_args
    : capability_arg ( "," capability_arg )*
    ;

capability_arg
    : IDENTIFIER "=" STRING
    ;
```

### Functions

```
function_declaration
    : "fn" IDENTIFIER "(" parameter_list? ")" return_type? block
    ;

parameter_list
    : parameter ( "," parameter )*
    ;

parameter
    : IDENTIFIER ":" type
    ;

return_type
    : "->" type
    ;

type
    : "int"
    | "float"
    | "bool"
    | "string"
    | "byte"
    | "array" "<" type ">"
    | "map" "<" type "," type ">"
    | "tainted" "<" type ">"
    | "safe" "<" type ">"
    | "void"
    ;
```

### Statements

```
statement
    : variable_declaration
    | assignment_statement
    | if_statement
    | while_statement
    | for_statement
    | return_statement
    | break_statement
    | continue_statement
    | expression_statement
    | scan_statement
    | sniff_statement
    | block
    ;

variable_declaration
    : type IDENTIFIER
    | type IDENTIFIER "=" expression
    | type "mut" IDENTIFIER "=" expression
    | "let" IDENTIFIER "=" expression
    | "let" "mut" IDENTIFIER "=" expression
    ;

assignment_statement
    : IDENTIFIER "=" expression
    | IDENTIFIER "+=" expression
    | IDENTIFIER "-=" expression
    | IDENTIFIER "*=" expression
    | IDENTIFIER "/=" expression
    ;

if_statement
    : "if" expression block ( "else" ( if_statement | block ) )?
    ;

while_statement
    : "while" expression block
    ;

for_statement
    : "for" IDENTIFIER "in" expression block
    ;

return_statement
    : "return" expression?
    ;

break_statement
    : "break"
    ;

continue_statement
    : "continue"
    ;

expression_statement
    : expression
    ;

block
    : "{" statement* "}"
    ;
```

### Cybersecurity DSL Statements

```
scan_statement
    : "scan" expression "port" ( INTEGER | range_expression )
    | "scan" expression "ports" range_expression
    ;

sniff_statement
    : "sniff" expression ( "filter" expression )?
    ;

range_expression
    : expression ".." expression
    ;
```

### Expressions

```
expression
    : logical_or_expression
    ;

logical_or_expression
    : logical_and_expression ( "||" logical_and_expression )*
    ;

logical_and_expression
    : equality_expression ( "&&" equality_expression )*
    ;

equality_expression
    : relational_expression ( ( "==" | "!=" ) relational_expression )*
    ;

relational_expression
    : additive_expression ( ( "<" | ">" | "<=" | ">=" ) additive_expression )*
    ;

additive_expression
    : multiplicative_expression ( ( "+" | "-" ) multiplicative_expression )*
    ;

multiplicative_expression
    : unary_expression ( ( "*" | "/" | "%" ) unary_expression )*
    ;

unary_expression
    : ( "!" | "-" ) unary_expression
    | postfix_expression
    ;

postfix_expression
    : primary_expression ( call_suffix | index_suffix | member_suffix )*
    ;

call_suffix
    : "(" argument_list? ")"
    ;

argument_list
    : expression ( "," expression )*
    ;

index_suffix
    : "[" expression "]"
    ;

member_suffix
    : "." IDENTIFIER
    ;

primary_expression
    : INTEGER
    | STRING
    | BOOLEAN
    | IDENTIFIER
    | "input" "(" ")"
    | sql_expression
    | command_expression
    | array_literal
    | "(" expression ")"
    ;

sql_expression
    : "sql" "(" STRING ( "," expression )* ")"
    ;

command_expression
    : "command" "(" STRING "," array_literal ")"
    ;

array_literal
    : "[" ( expression ( "," expression )* )? "]"
    ;
```

## Operator Precedence (Highest to Lowest)

1. Member access (`.`)
2. Function call `()`, Array index `[]`
3. Unary operators (`!`, `-`)
4. Multiplicative (`*`, `/`, `%`)
5. Additive (`+`, `-`)
6. Relational (`<`, `>`, `<=`, `>=`)
7. Equality (`==`, `!=`)
8. Logical AND (`&&`)
9. Logical OR (`||`)
10. Assignment (`=`, `+=`, `-=`, `*=`, `/=`)

## Associativity

- Most operators are left-associative
- Assignment operators are right-associative

## Examples

### Valid Programs

```aegis
// Example 1: Simple function
fn add(a: int, b: int) -> int {
    return a + b
}

// Example 2: Security-aware code
fn login(username: string, password: string) -> bool {
    let hash = crypto.sha256(password)
    let query = sql("SELECT * FROM users WHERE username = ? AND password_hash = ?", username, hash)
    let result = db.execute(query)
    return result.count() > 0
}

// Example 3: Cybersecurity DSL
fn scan_network() {
    scan "192.168.1.1" port 80
    sniff "eth0" filter "tcp port 80"
}
```

## Grammar Notes

1. **Newlines are statement terminators** (no semicolons needed)
2. **Blocks require braces** (no Python-style indentation)
3. **Type annotations are required** for function parameters
4. **Type inference** for local variables
5. **No implicit type conversions**

## Future Extensions

- Pattern matching (`match` expression)
- Struct and enum definitions
- Trait definitions and implementations
- Async/await syntax
- Generics (`<T>`)
- Unsafe blocks

---

This grammar is designed to be:
- **Simple to parse** (LL(1) or recursive descent)
- **Unambiguous** (no shift/reduce conflicts)
- **Extensible** (easy to add new features)
- **Security-focused** (explicit syntax for dangerous operations)
