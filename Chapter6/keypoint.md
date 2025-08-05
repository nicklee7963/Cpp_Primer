# Functions
# 6.1 Basic
we use **void** to imply no arguments
can't return a list
### 6.1.1 Local Objects
- Automatic Objects: 只在一個區塊執行時存在的物件
- Local static Objects: `static`不會在函式結束被摧毀，整個程式結束才會摧毀
### 6.1.2 Function Declaration (function prototype)
benefit:

- You can reuse the same function in multiple source files (.cpp) by just including the header file (.h).
- The compiler checks if a function is called with the correct number and types of parameters.

### 6.1.3 Seperate Compilation
...

# 6.2 Passing Arguments
### 6.2.1 Passed by Value
**won't affect arguments**
### 6.2.2 Passed by Reference
**will affect arguments**
If we don't want to change parameter we need to use `const (type)&`

### 6.2.3 Const Arguments and Parameter
頂層的const會被忽略
#### pointer reference and const

### 6.2.4 陣列參數


### 6.2.6 帶有不定參數的函式
- initializer_list
    - 接受單一型別，未知數目的引數
    ```cpp
    #include <initializer_list>
    initializer<int> lst;
    ```
- ellipsis

# 6.3 return statement
#### 回傳的參考是lvalue
```cpp
char &get_val(string &str, string::size_type ix)
{
    return str[ix];
}
int main()
{
    string s("a value");
    cout << s << endl;
    get_val(s, 0) = 'a';   // s[0] change to a
    return 0;
}
```

**trailing return type**: 可以用參數決定type

```cpp
auto add(int a, int b) -> int {
    return a + b;
}

```
**使用decltype**
```cpp
int odd[] = {1, 3, 5, 7, 9};
decltype(odd) *arrPtr(int i)
{
    return (i % 2) ? &odd : &even;
}

```
`int (*a)[10]` 的type 不等於 `int (*a)[20]`

# 6.4 Function Overload
**parameter's number or type must be different**
```cpp
// wrong
int lookup(int);
int lookup(const int);

int lookup(int *);
int lookup(int* const);

// correct
int lookup(int &);
int lookup(const int &);

int lookup(int *);
int lookup(const int*);


```

# 6.5 特殊用途的功能
### 6.5.1 default argument
...

### 6.5.2 inline and constexpr function
- inline function
```cpp
inline const string &
shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
}

```
- constexpr function
    - **return and parameter should be literal type, and only 1 return**
    - it is also **inline**


### 6.5.3 用於除錯的輔助功能
- assert
    - is a preprocessor macro
    - `assert(expr)` : when expr is false it will stop the code, when it is true it does nothing.
    - `#include <cassert>`
- NDEBUG
    - if we `#define NDEBUG` then assert can't use


# 6.6 Function Matching
...
# 6.7 Function Pointer
```cpp
bool (*pf) (const string &, const string &);
```
**when we use a function name as a value, it will be turned to pointer

```cpp

pf = lengthCompare;

bool b1 = pf("hello" "goodbye");
```

























