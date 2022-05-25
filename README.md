# Stingray
Stingray is object-oriented, functional general purpose programming language supporting:
- Variables
- Simple Classes
- Type Ascription
- Recursion
- Arrays

Stingray source files have the extension of `.stingray` or `.sg`


## Basic Types:
Stingray allows for some of the following basic types:
- Integer (i32)
- Double  (f64)
- String  (i8[])
- Nothing

## Program Structure

Program consists of import statements and declarations:
```java
Program ::= {Import} {Declaration}

Import ::= 'import' identifier {'.' identifier} 'as' identifier

Declaration ::= 'declare' identifier as TypeReference
```

We can compose 3 types of declarations in Stingray:
- Type alias `declare MyIntArray as Integer[]`
- Class/Interface declaration `declare MyClass as class {...}`
- Function declaration `declare MyFunc as Int x -> Int {...}`

Any Type Reference has the following syntax:
```java
Function Declaration has the folowing syntax:
```

## Functions

Stingray allows for top-level function declarations with the following syntax rules:
```java
FunctionDeclarationType ::= FunctionRangeDomain '->' FunctionRangeDomain
FunctionDefinitionType  ::= NamedFunctionRange '->' FunctionRangeDomain Body
FunctionRangeDomain     ::= TypeReference | '(' [TypeReference {',' TypeReference}] ')'
NamedFunctionRange      ::= TypeReference identifier | '(' [TypeReference identifier {',' TypeReference identifier}] ')'
```

## Classes
Class declarations in Stingray have the following syntax:

```java
ClassType        ::= 'class' [ExtendsList] [StaticsBody] "{" [ClassBody] "}" 
ExtendsList      ::= '<' [identifier] '>';
StaticsBody      ::= '(' FieldDefinition {FieldDefinition} ')'
ClassBody        ::= {FieldDefinition}

FieldDefinition  ::= identifier [':' TypeReference] [Value]
Value            ::= '<-' Expression | '{' Expression '}'
Body             ::= '{' {Statement} '}'
```

## Function Bodies
### Statements
Bodies of all the functions are sequences of statements:
```java
Statement        ::= identifier [':' TypeReference] [Value]
                   | IfStatement
                   | 'while' Expression Body
                   | 'for' identifier 'in' RangeExpr Body
                   | 'return' Expression
                   | FunctionCall

IfStatement     ::= 'if' Expression Body ['else' (IfStatement | Body)]
FunctionCall    ::= Term '(' [Expression {',' Expression}] ')'
```

### Expressions

```java
LambdaExpr   ::= '(' {identifier} ')' Body

MethodRef    ::= identifier '::' identifier

Expression   ::= Term [Binop Term] | LambdaExpr | MethodRef

ArrayRef     ::= Term '[' Expression ']'
FunctionCall ::= Term '(' [Expression {',' Expression}] ')'
FieldRef     ::= Term '.' identifier

Term         ::= '(' Expression ')'  
               | ArrayRef 
               | FunctionCall  
               | FieldRef  
               | ('true' | 'false' | 'empty') 
               | (numeric | string | identifier) 
               | '[' [Expression {',' Expression}] ']' 
               | RangeExpr  

RangeOpening    ::= '[' | '('
RangeClosing    ::= ']' | ')'
RangeExpr       ::= RangeOpening Expression ';' Expression RangeClosing [':' Expression]

Unop    ::= '#' | '+' | '-' | 'not'
Binop   ::= '=' | '!=' | '<' | '>' | '<=' | '>=' | '+' | '-' | '*' | '/' | '%' | '^' | 'and' | 'xor' | 'or' | '=>' | '<=>' | 'is' 
```

Range expressions examples are:
- `[0; 5]    <=> [0, 1, 2, 3, 4, 5]`
- `[0; 5)     <=> [0, 1, 2, 3, 4]`
- `(0; 5)     <=> [1, 2, 3, 4]`
- `(0; 5]     <=> [1, 2, 3, 4, 5]`
- `[0; 5]:2  <=> [0, 2, 4]`
- `[0; 5):2   <=> [0, 2, 4]`
- `(0; 5):2   <=> [1, 3]`
- `(0; 5]:2   <=> [1, 3, 5]`

Semantics for operators `=>` and `<=>`:
- `a => b` is equivalent to `not a or b`
- `a <=> b` is equivalent to `a and b or not a and not b`

# Operational Semantics, Typing Rules and Type Conversions:
## Arithmetic and Relational Expressions:
If arguments in arithmetic expression have different types, then one is converted to another: from smallest to largest. E. g. `Integer -> Double` and then typing rules are applied.

Arithmetic:
- Any Integer literal has type `Integer`. Any Floating-Point literal has type `Double`.
- if `a:T, b:T` then `(a + b): T`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a - b): T`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a * b): T`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a / b): T`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a % b): T`, where `T in {Integer}`
- if `a:T, b:T` then `(a ^ b): T`, where `T in {Integer, Double}`

Relational:
- if `a:T, b:T` then `(a <  b): Boolean`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a <= b): Boolean`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a >  b): Boolean`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a >= b): Boolean`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a =  b): Boolean`, where `T in {Integer, Double}`
- if `a:T, b:T` then `(a != b): Boolean`, where `T in {Integer, Double}`

## Logical Expressions:
If any of the arguments have numeric type - `Char, Integer, Long, Float, Double`, then it is converted to `Boolean` using the following rule:

`a: Num => a' := (a != 0): Boolean`, where `Num in {Char, Integer, Long, Float, Double}`.

- `true: Boolean, false: Boolean`
- if `a:Boolean, b:Boolean` then `(a and b): Boolean`
- if `a:Boolean, b:Boolean` then `(a or b): Boolean`
- if `a:Boolean, b:Boolean` then `(a xor b): Boolean`
- if `a:Boolean, b:Boolean` then `(a => b): Boolean`
- if `a:Boolean, b:Boolean` then `(a <=> b): Boolean`

# Program Example
```java
declare sayHello as Nothing -> Nothing

declare SimpleClass as class (
    foo : Integer <- 13
    bar : Double
) {
    classField  <- 12
    
    foox: Integer n -> Integer {
        return n + 1 + foox(n-1) + classField - foo
    }
}

declare ComplexClass as class <SimpleClass> {
    foox: Integer n -> Double {
        return n - 2
    }
}

declare fact as Integer n -> Integer {
    if (n = 0) {
        return 1
    }

    return n * fact(n-1)
}

declare main as String[] args -> Nothing {
    let foo: sayHello 
    let x : Double {empty}
    let y <- 12.32
    x <- 43
    let z {x = y}
    let f <- (12 + x < 45 + y) and (12 < 13) or "abc" <= "abcd" and empty
    let arr <- [12, true, 33.3]
    let arrElem <- arr[5]

    let simpleVariable <- SimpleClass()
    simpleVariable.foox(arr.length)
    let bar <- SimpleClass.bar

    if (f) {
        for i in [1; 5] {
            x  <- i + x
        }
    } else if (z) {
        f <- true
        let x <- "Hello"
    } else {
        let bar <- 1212
        return
    }

}
```

# Operator Precedences in Expressions:
Here are some operator preferences, from lowes to greatest (first line - lowest precedence, last line - highest)
- =>, <=>
- or, xor
- and
- not
- =, !=, <, >, <=, >=
- +, -
- *, /, %
- ^
- #, -
- [], ., ()


# Project Requirenments:
- Flex >= 2.6.4
- Bison >= 3.8.2
- BNFC >= 2.9.4

# Building the project:
1. Build BNFC syntax with `bnfc --cpp -m stingray.cf -o syntax/` being in `compiler/` directory.
2. Compile project using cmake

# Before you Commit:
1. Clear syntax directory by calling `make distclean` being in `compiler/syntax/` directory.
2. Make sure to run `clang-format`
3. Work in your own separate branch