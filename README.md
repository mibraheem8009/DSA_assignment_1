# Arithmetic Expression Evaluator

A command-line program that takes an infix arithmetic expression, converts it to postfix notation, and evaluates it.

## How to Compile

Make sure you have g++ installed, then run:

```
g++ -std=c++17 -o expr main.cpp
```

## How to Run

```
./expr
```

The program reads the expression from standard input:

```
a + b * (c + 2)
```

Then it asks for the value of each variable:

```
Enter val for a: 3
Enter val for b: 5
Enter val for c: 2
```

Then it prints the postfix form and the result:

```
a b c 2 + * +
23
```

## Supported Syntax

- **Operators:** `+`, `-`, `*`, `/`
- **Grouping:** `()`, `[]`, `{}`
- **Operands:** integer constants and variables
- **Variables:** follow C++ identifier rules — start with a letter or underscore, followed by letters, digits, or underscores (e.g. `x`, `my_var`, `_val1`)

## Error Handling

| Exit Code | Meaning | Example |
|-----------|---------|---------|
| 0 | Success | expression evaluated correctly |
| 1 | Syntax error | invalid character, mismatched brackets |
| 2 | Runtime error | division by zero, non-integer input |
| 3 | Logical error | malformed expression |

## Example

Input:
```
a + b * (c + 2)
```

Variable prompts :
```
Enter val for a: 3
Enter val for b: 5
Enter val for c: 2
```

Output :
```
a b c 2 + * +
23
```
