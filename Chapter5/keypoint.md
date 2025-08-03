# Statements
# 5.1 Basic Statement
- Expression statement: e.g.`ival + 5;`
- Null Statement: e.g.`; `
- Compound Statement (block): e.g. inside {}

# 5.2 The Scope of Statement
...

# 5.3 Condition Statement
### 5.3.1 if statement
**dangling else**: else 會與其前面最接近尚未匹配的if為一對

### switch statement
**case 標籤必須市整數值的constexpr**
```cpp
switch (ch)
{
    case 'a' : case 'e' : case 'i' : case 'o': case 'u':
        ++vowelCnt;
        break;
        
    default:
        ++otherCnt;
        break;
}
```


# 5.4 Iterative Statement
### 5.4.1 while statement

### 5.4.2 Traditional for statement
```cpp
for(initializer; condition; expression)
    statement
```
### 5.4.3 Range for statement
```cpp
for (declaration : expression)    // expression can be string vector...
    statement
```
**如果想要寫入元素，要用reference**
### 5.4.4 do while statement
**不管條件如何，都會進行迴圈一次**

# 5.5 Jump Statements
- break
    interrupt the closet while, do while, for or switch statement
- continue
    interrupt the closet while, do while, for or switch statement's iterate and start a new iterate immediately
- goto
    **don't use**

# 5.6 Exception Handling
```cpp
#include <stdexcept>
```cpp
#include <iostream>
#include <stdexcept>  // for std::runtime_error

int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero!");
    }
    return a / b;
}

int main() {
    int x = 10;
    int y = 0;

    try {
        int result = divide(x, y);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;  // std::cerr output won't interrupt, e.what() can get the error
    }

    std::cout << "Program continues after exception handling." << std::endl;

    return 0;
}

```




