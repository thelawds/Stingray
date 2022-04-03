# Stingray
Stingray is object-oriented, functional general purpose programming language supporting:
- Variables
- Simple Classes
- Type Ascription
- Recursion
- Arrays

Stingray source files have the extension of `.stingray` or `.sg`

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
ClassType        ::= [ExtendsList] ['(' StaticsBody ')'] '{' [ClassBody] '}'
ExtendsList      ::= {identifier} (identifier | 'class' | 'interface')
StaticsBody      ::= FieldDefinition {FieldDefinition}
ClassBody        ::= {FieldDefinition}

FieldDefinition  ::= identifier [':' TypeReference] [Value]
Value            ::= '<-' Expression | '{' Expression '}'
Body             ::= '{' {Statement} '}'
```

There are special types of Functions in Stingray called Constructors. Syntactically, for class `T` they are defined as:
```java
Constructor ::= 'new' ':' NamedFunctionRange '->' 'T' '{' {Statement} 'return' 'this' '}'
```

If there is no constructors in the class, then default constructor created, which initializes all the fields in the class with value of `empty`

## Function Bodies
### Statements
Bodies of all the functions are sequences of statements:
```java
Statement        ::= identifier [':' TypeReference] [Value]
                   | IfStatement
                   | 'while' Expression Body
                   | 'for' identifier 'in' RangeExpr Body
                   | 'return' Expression

IfStatement     ::= 'if' Expression Body ['else' (IfStatement | Body)]
```

### Expressions

```java
LambdaExpr   ::= NamedFunctionRange '->' (Expression | Body) 
                   | '(' [identifier {',' identifier}] ')' -> (Expression | Body)

MethodRef    ::= identifier '::' identifier

Expression   ::= Term [Binop Term] | LambdaExpr | MethodRef

ArrayRef     ::= Term '[' Expression ']'
FunctionCall ::= Term '(' [Expression {',' Expression}] ')'
FieldRef     ::= Term '.' identifier

Term         ::= '(' Expression ')'
               | [Unop] Term
               | ArrayRef
               | FunctionCall
               | FieldRef
               | ('true' | 'false' | 'empty')
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

# Program Example
```java
import system.io.readInt as readInt
import system.io.print as print

declare fact as Integer n -> Integer {

    if n = 0 {
        return 1
    } else {
        return n * fact(n-1)
    }

}

declare fib as Integer n -> Integer {
    if n = 0 or n = 1 {
        return 1
    } else {
        return fib(n-1) + fib(n-2)
    }
}

declare main as String[] args -> Nothing {
    queriesCnt <- Integer.parseInt(args[1])

    fibNumbers: IntegerVector // Default constructor is called
    factNumbers <- new IntegerVector(queriesCnt)

    for _ in [0; queriesCnt) {
        q <- readInt()
        fibNumbers.add(fib(q))
        factNumbers.add(fact(q))
    }

    for q in [0; queriesCnt) {
        print("Fib " + q + " is " + fib[q])
        print("Fact " + q + " is " + fact[q])
    }

    fibNumbers.clear()
    factNumbers.clear()
}

declare IntegerCollection as interface {
    add:        Integer -> Boolean
    remove:     Integer -> Boolean
    size:       Nothing -> Boolean
    forEach:    (Integer -> Nothing) -> Nothing
}

declare IntegerVector as IntegerCollection {
    data:       Integer[10] <- []
    size:       Integer     <- 0
    capacity:   Integer     <- 10

    new: Integer size -> IntegerVector {
        this.capacity   <- size
        this.data       <- new Integer[size]

        return this
    }

    add: Integer el -> Boolean {
        if size = capacity {
            newData  <- new Integer[capacity * 2]
            capacity <- capacity * 2

            for i in [0; size) {
                newData[i] <- data[i]
            }
            
            data <- newData
        }

        data[size] <- el;
        size <- size + 1
        return true
    }

    remove: Integer el -> Boolean {
        idx <- -1

        for i in [0; size) {
            if data[i] = el {
                idx <- i
            }
        }

        if id = -1 {
            return false
        }

        for i in [idx; size - 1) {
            data[i] <- data[i+1]
        }

        size = size - 1
        return true
    }


    size: Nothing -> Integer <- size

    forEach: Integer -> Nothing f -> Nothing {
        for i in [0; size) {
            f(data[i])
        }
    }

    
    remove: Integer el -> Nothing {
        remove(el)
    }

    clear: Nothing -> Nothing {
        // forEach(this::remove)
        forEach(el -> this.remove(el))
    }
}
```

# Project Requirenments:
- Flex >= 2.6.4
- Bison >= 3.8.2
- BNFC >= 2.9.4