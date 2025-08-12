# Classes
# 7.1 定義抽象資料型別
### 7.1.2定義
#### `this` 為一隱含的 Sales_data *const
`const Sales_data a` Then the object a is const, and only member functions marked with const can be called on it

When you define a member function (either inside or outside a class/struct), you can directly access member variables without writing Sales_data::price
**成員的宣告會先進行 再處理成員函式**
```cpp
#include <iostream>

struct Sales_data {
    // constructor
    Sales_data() = default;  //




    std::string isbn() const { return bookNo; }   // 可以先用booksNo,  add const so that this point to const
    // std::string isbn() const { return this -> book; }   // same
    Sales_data& combine(const Sales_data&);   // define outside
    double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

// 界面函式
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream, Sales_data&);



double Sales_data::avg_price() const {
    if (units_sold)
        return revenue/units_sold;
    else    
        return 0;
}

// # 7.1.2 回傳this
Sales_data& Sales_data:combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;  // When you define a member function (either inside or outside a class/struct), you can directly access member variables without writing Sales_data::price

    revenue += rhs.revenue;
    return *this
}


// # 7.1.3 定義非成員函式
// IO class can't be copied so we use reference
istream &read(istream& is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * items.units_sold;
    return is;
}

ostream& &print(ostream &os, const Sales_item &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}


```

# 7.1.4 Constructors
**can't not be declared as const**
- synthesized default constructor
    - if we didn't write constructor it use default constructor
    - **synthesized default constructor** use default constructor when there is no initializer
Some type can't use default constructor: if we create our own constructor then default constructor won't be created unless we use `default`
```cpp
struct Sales_data {
    Sales_data() = default; // default constructor
    
    // constructor initializer list
    Sales_data(const std::string &s) : bookNo(s){}
    Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){}
}
```
#### 在類主體外定義constructor
```cpp
#include <iostream>
#include <string>

struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    Sales_data() = default;
    Sales_data(std::istream &is) { read(is, *this); }
};

std::istream& read(std::istream &is, Sales_data &s) {
    double price = 0.0;
    is >> s.bookNo >> s.units_sold >> price;
    s.revenue = price * s.units_sold;
    return is;
}

int main() {
    std::cout << "請輸入 bookNo units_sold price（以空白分隔）：" << std::endl;
    Sales_data item(std::cin);  // 這裡會呼叫 Sales_data(istream&)，從標準輸入讀取資料
    std::cout << "你輸入的資料：" << std::endl;
    std::cout << "BookNo: " << item.bookNo << std::endl;
    std::cout << "Units sold: " << item.units_sold << std::endl;
    std::cout << "Revenue: " << item.revenue << std::endl;
    return 0;
}

```
### 7.1.5 Copy Assign and Destruct
...
# 7.2 Encapsulated and Access Specifiers
**access specifiers**
- public
- private
**struct** -> public
**class** -> private

### 7.2.1 Friends
在class內宣告friends 這樣外面的function可以直接用成員
```cpp
#include <iostream>
#include <string>

class Sales_data {
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p) 
        : bookNo(s), units_sold(n), revenue(p * n) {}

    // 宣告 read 為 friend 函式
    friend std::istream& read(std::istream &is, Sales_data &s);

    // 宣告 print 為 friend 函式
    friend std::ostream& print(std::ostream &os, const Sales_data &s);
};

// friend 函式，可以直接存取 Sales_data 的 private 成員
std::istream& read(std::istream &is, Sales_data &s) {
    double price = 0.0;
    is >> s.bookNo >> s.units_sold >> price;
    s.revenue = price * s.units_sold;
    return is;
}

std::ostream& print(std::ostream &os, const Sales_data &s) {
    os << "BookNo: " << s.bookNo
       << ", Units sold: " << s.units_sold
       << ", Revenue: " << s.revenue;
    return os;
}

int main() {
    Sales_data item;
    std::cout << "請輸入 bookNo units_sold price：" << std::endl;
    read(std::cin, item);
    print(std::cout, item) << std::endl;
    return 0;
}

```
# 7.3 額外的類別功能
### 7.3.1 再訪類別成員
#### 定義型別成員：在class中定義type
```cpp
class Screen {
public :
    using pos = std::string::size_type;

public:
    pos cursor = 0;
    pos height = 0;
};
```

#### mutable 資料成員
    mutable 是為了讓 const 成員函式裡可以修改特定成員變數 的一個關鍵字
    `mutable int a;`

#### 類別宣告
    `class Screen;`

### 7.3.4 重訪朋友關係
#### 類別之間的朋友關係
```cpp
class Screen {
    friend class Window_mgr;  // window mr 可以用 screen private
    
}
// or
```
class Acreen {
    friend void Window_mgr::clear(ScreenIndex);
}
**class friend don't have transitive 朋友的朋友不是我的朋友**

# 7.4 類別範疇


# 7.5 再訪constructor
### 7.5.1 
**if member is const, reference or something didn't have default constructor, we should use 建構初始器串列**

### 7.5.2 delegating constructors
```cpp
class Sales_data {
public;
    Sales_data(std::string s, unsigned cnt, double price): bookNo(s), units_sold(cnt), revenur(cnt*price) {}
    // 剩餘委派
    Sales_data(): Sales_data("", 0, 0){};
    Sales_data(std::strin s) : Sales_data(s, 0, 0){}
};
```
### 7.5.5 aggregate class
a class is aggregate when 
- member is all public
- no constructor
- no inclass initializers

```cpp
struct Data{
    int ival;
    string s;
}
// we can use list initializer
Data val = {0, "anna"};
```
#### explicit

without explicit:
explicit 是「不讓編譯器偷偷幫你轉型」
```cpp
class MyClass {
public:
    MyClass(int x) {
        std::cout << "MyClass(" << x << ")\n";
    }
};

void print(MyClass obj) {
    // ...
}

int main() {
    print(10);  // 會隱式地建立 MyClass(10)
}
```

with explicit:
```cpp
class MyClass {
public:
    explicit MyClass(int x) {
        std::cout << "MyClass(" << x << ")\n";
    }
};

void print(MyClass obj) {
    // ...
}

int main() {
    print(10);       // 編譯錯誤：不能隱式轉型
    print(MyClass(10));  // 正確，顯式轉型
}

```
# 7.6 static 
**類別共同使用的變數**




