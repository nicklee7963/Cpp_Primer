# Variables and Basic Type
# 2.1 原始內建型別
- arithmetic types(算術型別) -> char, int, boolean, float
- void

### 2.1.1 Arithmetic Types
1. integral types -> int , char, boolean
2. float
**char may be either signed or unsigned**
- When you know that it can't be negative use unsigned
- for integer use int, short is too small
- When you need a small integer, specify using signed char or unsigned char
- Use double, since it it more precise than float

### 2.1.2 Type Convertion
signed + unsigned -> unsigned

### 2.1.3 Literal
1. Integer/Float
    -> exponent use E 
2. Character/String
    -> string literal(字串自面值)會在結尾加一個'/0'
    ```cpp
    std::cout << "hello my name is nick "
                "i am a college student" << std::endl;
    // multiple line output
    ``` 
3. Escape Sequences(轉義序列)


**Char that are not printable**
| name | symbol | 
|---|---|
| newline |`\n` |
| vertical tab | `\v` |
| horizontal tab | `\t` |
| backspace | `\b` |



| Name              | Escape Sequence | ASCII Value | Description                          |
|-------------------|------------------|-------------|--------------------------------------|
| Newline           | `\n`             | 10          | Moves cursor to the next line        |
| Vertical Tab      | `\v`             | 11          | Moves cursor vertically (rarely used)|
| Horizontal Tab    | `\t`             | 9           | Inserts a horizontal tab             |
| Backspace         | `\b`             | 8           | Moves cursor one character back      |
| Carriage Return   | `\r`             | 13          | Returns cursor to beginning of line  |
| Alert (Bell)      | `\a`             | 7           | Makes a beep sound (if supported)    |
| Null              | `\0`             | 0           | Null terminator (end of string)      |

4. Boolean and Pointer Literal
**Pointer Literal** -> nullptr

# 2.2 Variable
### 2.2.1 The definition of variable
**Initializers**: initialize and assign are difference 
```cpp
int a = 0;
int a = {0};
int a{0};
int a(0);
```
#### List Initialization
-> `int a{3}`
-> `int a{3.14} // return error because list initialization avoid missing info`
#### Default Initialization
Define out of function -> initialize to 0
Define inside function -> uninitialized
Check 02/default/initialize


### 2.2.2 Declarations and Definitions
**Declarations**: Let the program know its name and type
**Definitiona**: allocate memory
```cpp
// to declare use extern
extern int i;  // declare
int j; // declare + define
extern int i = 3.14 // wrong
```
### 2.2.3 Identifier
naming convention:
- usually lower case
- -> studentLoan or `student_loan`
###  2.2.4 Scope of a variable
Usually determined by curly braces

# 2.3 Compound Type
以其他型別定義的型別
1. reference
    ```cpp
    // reference can't rebind
    int ival = 1024;
    int &refVal = ival;
    int &refVal2;   // wrong need initializing

    int i = 11, i2 = 12;
    int &r = 10; // wrong -> need object
    double dval - 3.14;
    int &r
    refVal = dval;  // wrong -> need same type
    ```
    **a reference is not an object**

    
2. pointer
    **to use nullptr you need to include <cstdlib>**
    ```cpp
    int *&r = p;  // r is a reference to pointer p
    ```
# 2.4 const

**需要初始化:**`const int k;  // wrong need value `
### 2.4.1 對const的參考
```cpp
const int ci = 1024;
const int &ri = ci; //ok    -> this specify that ci can't change value through ri
                    //         if ci is not a const it can changes
int &r2 = ci;  // wrong 
```


### 2.4.2 指標與const
- 對const的指標
```cpp
const double pi = 3.14;
double *ptr = &pi;    // wrong, ptr isn't const
const double *cptr = &pi    // ok, cptr is a pointer to const double
*cptr = 42;   // wrong, you can't modify 
```
- const指標
```cpp
int errNumb = 0;
int *const curErr = &errNumb;  // curErr 永遠指向errNumb
const double pi = 3.14;
const double *const pip = &pi;
```
### 2.4.3 頂層的const
**頂層的const**: 指標本身是一個const
**底層的const**: 指標能夠指向一個const
When we copy, high-level const will be ignored, however low-level will not be ignored
### 2.4.4 constexpr與常數運算式
**constant expression**: 其值不能被改變，且可在編譯時期估算
```cpp 
const int max = 20; // yes
int staff = 27; // no
const int sz = get_size();  // no


constexpr int mf = 20;   
```
**literal types**:能在constexpr使用的型別 -> arthmetic, reference, pointer
#### pointer and constexpr
```cpp
const int *p = nullptr;
constexpr int *q = nullptr;  // q是指向int的一個const 指標
constexpr const int *p = &i;
// notice: constexpr 用在指標上
```
# 處理型別
### 2.5.1 type alias
- type alias
```cpp
typedef double wages;
typedef wages base, *p;  // base is an alias of double, while p is an alias of double*
```
- alias declaration
```cpp
using db = double;
```
### 2.5.2 auto
```cpp
auto item = val1 + val2;

auto sx = 0, pi = 3.14;  //wrong need to be same type
```
**top-level const will be ignored**
`const auto f = 1`

### 2.5.3 decltype
```cpp
decltype(f()) sum = x;   // sum has the type f() return
```
**decltype((variable)) is always a reference, however decltype(variable) depends on variable

# 2.6
header guaders: ensure the file only include once
```cpp
#ifndef MYHEADER_H
#define MYHEADER_H
...
...
...
#endif
```





























