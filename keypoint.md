# Copy Control
- copy constructor
- copy-assignment constructor
- move constructor
- move-assignment constructor
- destructor
# 13.1 Copy, Assign and Destroy
### 13.1.1 Copy Constructor
```cpp
class Foo{
public: 
    Foo();   // default constructor
    Foo(const Foo&);  // copy constructor

}
```
#### Synthesized Copy Constructor
```cpp
class Sales_data {
public:
    Sales_data(const Sales_data&);
private:
    std::string BookNo;
    int units_sold = 0;
    double revenue = 0.0;
};

// synthesized copy constructor
Sales_data::Sales_data(const Sales_data &orig):
    bookNo(orig.bookNo), 
    units_sold(orig.units_sold), 
    revenue(orig.revenue)
    {}
```
#### Copy Initialization
```cpp
string dots(10, '-'); // direct initialize
string s(dots) // direct initialize
string s2 = dots    // copy initialize

```

**copy initialize need either a move constructor or a copy constructor**
#### 參數和回傳值
拷貝constructor 的參數是參考
### 13.1.3 Destructor
```cpp
class Foo {
public:
    ~Foo ();   //destructor
}
```
#### Synthesized Destructor
### 13.1.4 Three/Five Principle
#### 需要destructor 就需要copy and assign constructor
#### 需要copy 的就需要assign 反之亦然
### 13.1.5 Using = default
### 13.1.6 Avoid Copying
e.g.: iostream
#### 將一個函式定義為已刪除
```cpp'
struc NoCopy{
    NoCopy() = default;
    Nocopy(const Nocopy&) = delete
    Nocopy &operator= (const NoCopy&) = delete;
    ~NoCopy() = default;

};


