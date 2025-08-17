# Copy Control
- copy constructor
- copy-assignment operator
- move constructor
- move-assignment operator
- destructor
# 13.1 Copy, Assign and Destroy
### 13.1.1 Copy Constructor
參數是對const 的reference
```cpp
class Foo{
public:
    Foo();   // default constructor
    Foo(const Foo&)  // copy constructor

};
```
#### Synthesized Copy
When we don't diefine our own copy constructor, complier will help us synthesize one.
- memberwise copy

**synthesized copy對指標是shallow copy, 用copy constructor**
#### Copy Inistialize
- direct initialize: function matching, select the constructor match the argument we provide
- copy initialize: 將右手邊元素複製到左手邊
**When copy initialize occurs, we use either copy constructor or move constructor**
Conditions:
- when we use `=` to initialize variable
- a non reference argument
- return non reference
- 用大括號初始化一個陣列
### 13.1.2 Copy-Assignment Operator
控制類別的物件如何被指定
```cpp
Sales_data trans, accum;
trans = accum;
```
#### Overload Intro
```cpp
class Foo {
public:
    Foo& operator=(const Foo&); 
};
```
**指定運算子一般回傳一個參考指向左operand**
#### Synthesized Copy-Assignment Operator
### 13.1.3 Destructor
摧毀物件非static的成員
```cpp
class Foo {
public: 
    ~Foo();

};
```
**It can't not be overload**
**內建指標型別的成員不會delete指標所指的物件**
**對一個物件的指標、參考超出範疇, destructor不會執行**
#### Synthesized destructor 
### 13.1.4 Three/Five Principle
#### 需要destructor就需要copy and assign
### 13.1.5 Using = default
我們可以明確的要編譯器產生合成版本的copy
### 13.1.6 防止拷貝
e.g. iostream避免拷貝
```cpp
struct NoCopy{
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;   // no copy
    NoCopy &operator=(const NoCopy&) = delete;  // no assign
    ~NoCopy() = default;
};
```
# 13.2 拷貝控制與資源管理
### 13.2.1 Value-like Object
- 拷貝striong 而不是指標的copy constructor
- destructor to release the string
- a copy-assignment operator to release current string and copy the right one
```cpp
class HashPtr{
public:
    HashPtr(const std::string &s = std::string()):
        ps(new std::string(s), i()){}
    HashPtr(const HashPtr &p):
        ps(new std::string(*p.ps), i(p.i)){ }
    HashPtr& operator=(const HashPtr &);
    ~HashPtr() { delete ps; }
private:
    std::string *ps;
    int i;
};

HashPtr& HashPtr::operator=(const HasPtr &rhs)
{
    auto newp = new string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
};
```
#### 13.2.2 Pointer-like Object
We need copy constructor, copy-assignment operator to copy pointer, not the string pointer pointing to
```cpp
class Hasptr{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::strings(s)) , i(0), use(new std::size_t(1)) {}
    HasPtr(const HasPtr &p):
        ps(p.ps), i(p.i), use(p.use) {++*use;}
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
private:
    std::string *ps;
    int i;
    std::size_t *use;

};

// destructor 不能直接delete. Because other pointers may point to the same object
HasPtr::~HasPtr()
{
    if (--*use == 0) {
        delete ps;
        delete use;
    }
}

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    ++*rhs.use;
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;

}
```
# 13.3 Swap
```cpp
void swap(Foo &lhs, Foo &rhs)
{
    std::swap(lhs.h, rhs.h);    // this version use std::swap not the swap we defined
}
```
```cpp
void swap(Foo &lhs, Foo &rhs)
{
    using std::swap;
    swap(lhs.h, rhs.h);  // if there is a defined swap then use it or else use std::swap
}

```
#### assign operator using swap
```cpp
HasPtr& HasPtr::operator=(HasPtr rhs)
{
    swap(*this, rhs);
    return *this;
}
```
# 13.5 管理動態記憶體類別
StcVec:
```cpp
class StrVec {
public:
    StrVec():
        elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);
    StrVec &operator=(const StrVec&);
    ~StrVec();
    void push_back(const std::string&);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

private:
    static std::allocator<std::string> alloc;
    void chk_n_alloc()
        { if (size() == capacity()) reallocate(); }
    std::parin<std::string*, std::string*> alloc_n_copy (const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string *elements;
    std::string *first_free;
    std::string *cap;

        
};

```
#### `push_back()`
```cpp
void StrVec::push_back(const string& s)
{
    chk_n_allloc();
    alloc.construct(first_free++, s);  // 在first_free只的地方新增s的拷貝
}
```
#### `alloc_n_copy`
```cpp
pair<string*, string*>  // return (new head, and new tail)
StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e-b);
    return {data, unintialized_copy(b, e, data)};
}

```


#### `free`
**free 必須destroy元素，然後釋放StrVec所配置空間**
```cpp
void StrVec::free()
{
    if (elements) {
        for (auto p = first_free; p != elements;){
            alloc.destroy(--p)
        alloc.deallocate(elements, cap - elements);
        }
    }
}
```
#### `拷貝控制成員`
```cpp
StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVEc() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
```
#### Move Constructor and `std::move`
`#include <utility>`

#### reallocate 成員
```cpp
void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i){
        alloc.construct(dest++, std::move(*elem++));      
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
```
# 13.6 移動物件
iostream can't copy but it can move
### 13.6.1 Rvalue Reference
取得方式是用`&&` 不是 `&`
**只能bind to 快要被摧毀的物件**
可以將rvalue reference bind to 字面直 但是不行bind to lvalue
```cpp
int i = 42;
int &r = i;
int &&rr = i; // worong
int &r2 = i * 42 // wrong
const int &r3 = i * 42 // ok: 可以將對const reference bind to r value
int &&rr2 = i * 42;  // ok

```
#### Lvalue 是永恆的 Rvalue 是一時的
rvalue 繫結到的東西是一時的：
- 所指的東西即將被銷毀
- 那個物件不能有其他使用者
#### variable is Lvalue
```cpp
int &&rr1 = 42;
int &&rr2 = rr1;   // wrong: rr1 expression is an lvalue
```
#### `std::move`
獲取繫結到一個lvalue的一個rvalue reference
`int &&r3 = std::move(rr1)`: ok

### 13.6.2 Move Constructor and Move Assignment
**Move constructor 的參數是一個rvalue reference**
`noexcept` promise that the function won't throw exception
```cpp
class StrVec {
public:
    StrVec(StrVec&&) noexcept;
}
```
#### Move-Assignment Operator
```cpp
StrVec &StrVec::operatror=(StrVec &&rhs) noexcept
{
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this
}
```
#### Synthesized Move Operation
If a class has already defined its own copy constructor, compiler won't synthesize move constructor
**complier will only synthesize move constructor when a class doesn't define its own copy constructor and all the member should be able to use move**
#### Move Iterator
`#include <make_move_iterator>`: iterator -> move iterator
**Deference a move iterator will get a rvalue**



