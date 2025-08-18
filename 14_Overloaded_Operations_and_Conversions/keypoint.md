# Overloaded Operations and Conversions
# 14.1 Concept
**除了operator(), 不可以有預設引數**
**不能發明新的operator**
**&& || 沒有保留估算順序，不應被overloaded**
**取址不應該被overloaded**
#### 類別成員或非成員函式
`=`, `[]`, `()`, `->`: must be member
`increment`, `decrement`, `dereference`: member
`arithmetic`, `equality`, `relational`, `bitwise`: outside membeer
**If we define a operator as a member function, the left operands must be the object of the class**
# 14.2 輸入與輸出運算子
### 14.2.1 Overload <<
First parameter is **a reference to a non const ostream**
- it is a const because 寫入資料流會改變型態 
- it is a reference because we can't copy ostream
Second parameter is **a reference to a const** points to the type we want to print

```cpp
ostream &operator<<(ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold ;
    return os;
}
```
**輸出運算子不應該印出 newline**
**輸入輸出必須為非成員函式**

### 14.2.2 Overload >>
First parameter is  a reference 
Second parameter is a reference of a 非const object
```cpp
istream &operator>>(istream &is, Sales_data &item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();
    return is;
}
```
# 14.3 算術語關係運算子
**一般會定義為非成員函式** 以允許左右operands的轉換
Usually parameter is **reference to const**
```cpp
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}
```
### 14.3.1 Equality Operator
**member 一個一個比對**
```cpp
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn() &&
            lhs.units_sold == rhs.units_sold;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
    return !(lhs==rhs);
}
```
### Relational Operator
**如果<有唯一的邏輯定義，就要定義<，如果類別也有==,  他們的結果就必須一致**
# 14.4 Assignment Operator
**must be member function**
```cpp
StrVec &StrVec::operator=(initializer_list<string> il)
{
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this
}
```
#### Compound Assignment Operators
**prefer to define in class**
```cpp
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
```
# 14.5 下標運算子
**Must be a member function**
return a reference points to the elements we take
**One should determine two version: return a reference to const, return a reference**
```cpp
class StrVec {
public: 
    std::string& operator[] (sd::size_t n)
    { return elements[n]; }
    const std::string& operator[](std::size_t n) const 
        { return elements[n];}
private:
    std::string *elements;
};
```
# 14.6 遞增與遞減運算子
**前綴後綴都得定義**
```cpp
class StrBlobPtr {
public:
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    
};
```
**前綴應該回傳一個參考指向遞增過的物件**
前綴:
```cpp
StrBlobPtr& StrBlobPtr::operator++()
{
    check(curr, "increment past end of StrBlobPtr");
    +curr;
    return *this;
}
```
後綴:
**參數用int**
```cpp
class StrBlobPtr{
public:
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);

};

StrBlobPtr StrBlobPtr::operator++(int)
{
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}
```
**後綴應該回傳就的值,不是一個參考**
```cpp
StrBlobPTr p(a1);
p.operator++(0) // 後綴
p.operator--() // 前綴

```
# 14.7 Member Access Operator
```cpp
class StrBlobPtr {
public:
    std::string& operator* () const
    {
        auto p = check (curr, 'dereference past end');
        return (*p)[curr];
    }
    std::string* operator-> () const
    {
        return &this -> operator*();
    }
};
```
**Usually * -> is member**


















