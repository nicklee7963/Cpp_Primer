# 4 Expressions
consist by **opearnds** & **operator**
# 4.1 Basic Knowledge
**Overloaded operators**: you define or change what an operator
#### Lvalues & Rvalues
**lvalue**: can take its' address
**rvalue**: a temporary storage

### 4.1.2 Priority and Associativity
```cpp 
int ia[] = {0, 2, 4, 5, 8};
int last = *(ia + 4);    // equal to ia[4]
last = *ia + 4   // equal to ia[0] + 4
```cpp
# C++ Operator Precedence and Associativity

| Precedence | Operator(s)                                   | Description                                 | Associativity         |
|------------|-----------------------------------------------|---------------------------------------------|------------------------|
| 1 (highest)| `::`                                           | Scope resolution                            | Left-to-right          |
| 2          | `++` `--`                                      | Post-increment, post-decrement              | Left-to-right          |
|            | `()`                                           | Function call                               |                        |
|            | `[]`                                           | Array subscript                             |                        |
|            | `.` `->`                                       | Member access                               |                        |
| 3          | `++` `--` `+` `-` `!` `~`                      | Pre-increment, pre-decrement, unary plus/minus, logical NOT, bitwise NOT | Right-to-left  |
|            | `*` `&`                                         | Dereference, address-of                     |                        |
|            | `sizeof` `typeid`                              | Sizeof/type info                            |                        |
|            | `new` `new[]` `delete` `delete[]`              | Memory allocation/deallocation              |                        |
| 4          | `.*` `->*`                                     | Pointer to member                           | Left-to-right          |
| 5          | `*` `/` `%`                                     | Multiplication, division, modulo            | Left-to-right          |
| 6          | `+` `-`                                         | Addition, subtraction                       | Left-to-right          |
| 7          | `<<` `>>`                                       | Bitwise shift left/right                    | Left-to-right          |
| 8          | `<` `<=` `>` `>=`                               | Comparison operators                        | Left-to-right          |
| 9          | `==` `!=`                                       | Equality operators                          | Left-to-right          |
| 10         | `&`                                             | Bitwise AND                                 | Left-to-right          |
| 11         | `^`                                             | Bitwise XOR                                 | Left-to-right          |
| 12         | `|`                                             | Bitwise OR                                  | Left-to-right          |
| 13         | `&&`                                            | Logical AND                                 | Left-to-right          |
| 14         | `||`                                            | Logical OR                                  | Left-to-right          |
| 15         | `?:`                                            | Ternary conditional                         | Right-to-left          |
| 16         | `=` `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `^=` `|=` | Assignment and compound assignment | Right-to-left          |
| 17         | `throw`                                         | Throw operator                              | Right-to-left          |
| 18         | `,`                                             | Comma operator                              | Left-to-right          |

```


### 4.1.3 Order of Evaluation
```cpp
int a = fa() * fb();   // we can't know which function been calculated first

int i = 0;
cout << i << ++i << endl;   // wrong
```

# 4.2 Arithmetic Operators
Arithmetic operators:
e.g. +, -, *, /, ...

# 4.3 Relational Operators & Logical Operators
Logical operators:
**short-circuit evaluation**
- `&&`的右邊只有在左邊是True才被算
- `||`的右邊只有在左邊是False才被算

Relational operators:
e.g. <, >, <= ...

# 4.4 Assignment Operator
**the left operand of assignment operator must be lvalue**
**narrowing conversion**: implicit conversion
```cpp
double pi = 3.14159;
int x = pi; // narrowing: fractional part is lost
```
- assignment operator has lower priority than relational operator
# 4.5 Increment & Decrement
```cpp
int i = 0, j;
j = ++i; // j = 1, i = 1:  prefix 有遞增後的值
j = i++; // j = 1, i = 2:  postfix 有未遞增的值
```
# 4.6 Member Access Operator
e.g. `.`, `->`


# 4.7 Ternary Operator
`cond ? expr1 : expr2;`
`string finalgrade = (grade < 60) ? "fail" : "pass";`

# 4.8 Bitwise Operator
`~`: not
`^`: XOR
**use unsigned to use bitwise operator**

# 4.9 `sizeof` Operator
**the result of sizeof is a constexpr**
- sizeof (type) ```sizeof(Sales_data)```
- sizeof expr: ```sizeof Sales_data::revenue;```

# 4.10 Comma Operator
e.g. `, `

# 4.11 Type Conversion
- **implicit conversions**: `int ival = 3.541 + 3;`
    - In arithmetic, small int will be convert to larger one: short -> int
    - In condition, non-bool -> bool
    - In assignment, right operands type -> left type
 
### 4.11.1 Arithmetic Conversions
**If a signed and an unsigned int appear in the same expression, the signed one will usually be converted to unsigned.**
### 4.11.2 Other Implicit Conversions
**array to pointer**: when we use an array it will be convert to pointer.
e.g.
```cpp
int ia[10];
int* ip = ia;   // ip points to ia's first element
```
**pointer conversion**: 
pointer points to non-const can be convert to void*, 
every pointer can be change to const void*
e.g.
```cpp
int x = 10;
int* p = &x;
void* vp = p; // p is converted to void*
```
**conversion to bool**: both pointer and arithmetic if not 0 , will be true
e.g.
```cpp
char *cp = get_string();
if (cp)  
...
while (*cp)
...
```
**conversion to const**: non const -> const
e.g.
```cpp
int i;
const int &j = i;  
const int *p = &i;  
```
**conversion  defined by class types**
e.g.
```cpp
string s, t = "a value";  // string literal -> string
while (cin >> s) // cin -> bool
```

### 4.11.3 Explicit Conversion
#### Named Cast
`cast-name<type>(expression)`
**If type is a reference the result is lvalue**
- ``static_cast``:用在較大的算術型別被指定給小的
    
    e.g.
    ```cpp
    int i, j;
    double slope = static_cast<double>(j) / i;

    void* p = &d;
    double *dp = static_cast<double*>(p);
    ```
    - can't change const to non const

- ``const_cast``: cast away the const, **使用const_cast以寫入const物件是未定義的
- ``reinterpret_cast``: 改變指標










