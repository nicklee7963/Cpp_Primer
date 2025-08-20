# OOP
# 15.1 OOP 概觀
#### Inheritance
**預期衍生類別會為自己定義的函式為`virtual`**
```cpp
class Quote {
public:
    std::string isbn() const;
    virtual double net_price(std::size_t n) const;
};

class Bulk_quote : public Quote{
public:
    double net_price(std::size_t) const override;
};
```
#### Dynamic Binding(run-time binding)

# 15.2 定義基礎與衍生類別
```cpp
class Quote{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { }
    std::string isbn() const { return bookNo; }
    virtual double nte_price(std::size_t n) const { return n * price; }
    virtual ~Quote() = default;

private:
    std::string bookNo;

protected:
    double price = 0.0;
};
```
#### Access and Inherit
- public: 衍生類別可以用
- private: 衍生類別不能用
- protected: 衍生類別可以用，禁止其他使用者存取

### 15.2.2 定義衍生的類別
**Derined-to-base conversion**: 一個基礎類別bind to衍生物件
#### 衍生類別建構器:
可以繼承基礎成員的變數，卻無法初始話
```cpp
Bulk_quote(const std::string& book, double p, std::size_t qty, double disc): Quote(book, p), min_qty(qty), discount(disc) {}
```
**用別人的constructor 初始化**
#### Inherit and Static Member
如果定義一個static variable, then everyone will use the same one.
```cpp
class Base {
public:
    static void statmem();
};
class Derived : public Base {
    void f(const Derived&);
};

void Derived::f(const Derived& derived_obj)
{
    Base::statmem();
    Derived::statmem();
    derived_obj.statmem();  // access statmem by derived_obj
    statmem();  // access by this object
}
```
#### 衍生類別的宣告
```cpp
class Bulk : public quote; // wrong
class Bulk; // OK
```
**基礎類別要被定義才能繼承**
```cpp
class Quote;
class Bulk_quote : public Quote { };  //  wrong Quote must be defined
```
#### 防止繼承
**在一個class 後面加`final`**
```cpp
class NoDerived final { };   // Noderived 不能被繼承
```

### 15.2.3 轉換與繼承
#### 靜態型別與動態型別
當我們以衍生型別的物件初始化或指定給基礎型別，所拷貝移動指定的只有基礎物件的部份


