# Variables and Basic Type
## 2.1 原始內建型別
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
| ---  | ---    |
| newline | \n |
| vertical tab | \v |
| horizontal tab | \h |
| backspace | \b |

4. Assigned a type for literal 
**Prefix**












