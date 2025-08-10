# Sequential Containers
# 9.1 Overview
- vector:
    - 大小彈性的陣列
    - 快速的隨機存取
- deque:
    - 快速的隨機存取
    - 兩端開口的queue
- list: 
    - doubly linked list
    - 雙向循序存取
    - 任一點插入刪除快速
- forward_list:
    - singly linked list
    - 任一點插入刪除快速
- array:
    - 大小固定
    - 無法新增或刪除
- string:
    - 類似vecor
# 9.2 容器程式庫概觀
### 9.1.2 iterator
```cpp
while (begin != end) {    // begin = end when it is empty
    *begin = val;
    ++begin;
}
```
### 9.2.2 容器型別成員
`list<string>::iterator`
`vector<int>::diffenence_type`
### 9.2.3 begin and end member
```cpp
list<string> a = {"hello", "star", "austin"}
auto it1 = a.begin() // list<string>::iterator
auto it2 = a.rbegin() // list<string>::iterator
auto it3 = a.cbegin() // list<string>::const_iterator
auto it2 = a.crbegin() // list<string>::const_reverse_iterator

```
**if we don't need to write in we use cbegin and cend**
### 9.2.4 Define and Initialize a container
- we can use list initialize to initialize a container
- every containers except for array can use `vector<int> ivec(10, -1)` to initialize
    `C c;`
     預設建構器。如果 C 是 array，那麼 c 中的元素就是預設初始化的，否則 c 為空。

    `C c1(c2)`
    `c1 = c2`
     c1 是 c2 的一個拷貝。c1 和 c2 必須有相同的型別（也就是說，它們必須有相同的容器型別），並存放相同的元素型別。對 array 來說還必須有相同的大小。

    `C c{a,b,c...}`
    `C c = {a,b,c...}`
     c 是初始器串列中元素的一個拷貝。串列中的元素之型別必須與 C 的元素型別相容。對於 array，初始器必須有相同數量的元素，或者省略數少於 array 的長度，缺少的元素會使用值初始化（§3.3.1）。

    `C c(b,e)`
     c 是由 b 和 e 所表示的範圍中元素的拷貝。這兩個迭代器必須與 C 的元素型別相容（對 array 無效）。

    接受一個大小的建構器只對順序容器（不包括 array）有效
    `C seq(n)`
     seq 有 n 個值初始化的元素。這個建構器為 explicit  的。對 string 無效。

    `C seq(n,t)`
     seq 有 t 值的 n 個元素。




#### array has fixed size
```cpp
array<int, 42>   // store 42 integers array 
```
#### assign and swap
- assign:
    `c1 = c2`
     將 c1 中的元素取代為 c2 中元素的拷貝。c1 和 c2 必須有相同型別。

    `c = {a,b,c...}`
     以初始器串列中的元素取代 c1 中的元素。 （對 array 無效）

    `swap(c1, c2)`
    `c1.swap(c2)`
     將 c1 中的元素與 c2 中的元素互換。c1 和 c2 必須是相同型別。
     swap 通常會比 c1 與 c2 的元素逐項拷貝要快很多。


    **assign 運算對關聯式容器或 array 來說無效**

    seq.assign(b,e)
     將 seq 中的元素以迭代器 b 和 e 所代表的元素取代。迭代器 b 和 e 不
     可以指向 seq 中的元素。

    seq.assign(il)
     以初始器串列 il 中的元素取代 seq 中的元素。

    seq.assign(n,t)
     以值為 t 的 n 個元素取代 seq 中的元素。

### 9.2.6 容器大小的運算
e.g. .size(), .empty(), .max_size()
### 9.2.7 Relational Operator
**To use relational operator(<, >, =, ...), container need to have same type including its elements' type**


# 9.3 Operation in Sequential Container
operations for both sequential container and relational container
型別別名
iterator
 此容器型別的迭代器（iterator）之型別

const\_iterator
 可讀取但不能更改元素的迭代器之型別

size\_type
 大型到足以表示此容器中任意大小的非負整數的型別

difference\_type
 足以表示同一個容器中兩個迭代器間的距離之型別

value\_type
 元素型別

reference
 元素的 lvalue 型別；value\_type& 的同義詞

const\_reference
 元素的 const lvalue 型別（即 const value\_type&）

---

建構
C c;
 預設建構器。空的容器（array 參閱 §9.2.4）

C c1(c2);
C c1 = c2;
 將 c1 建構為 c2 的一個拷貝

---

Copy 產生的迭代器、參考以及所存的指標都會失效（對 array 來說無效）

C c{a,b,c...};
 串列初始化

---

指定和對調
c1 = c2
 將 c1 中的那些元素換成 c2 中那些

c1 = {a,b,c...}
 將 c1 中的那些元素換成串列中的那些（對 array 來說無效）

a.swap(b)
swap(a, b)
 將 a 中的元素與 b 中的互換
 等同於 a.swap(b)

---

大小
c.size()
 c 的元素數

c.max\_size()
 c 能夠存放的最大元素數

c.empty()
 如果 c 有任何元素，就為 false；否則就為 true

---

新增或移除元素（對 array 來說無效）
注意：這些運算的介面會根據容器型別而變

c.insert(args)
 將 args 所指定的元素拷貝到 c

c.emplace(inits)
 使用 inits 在 c 中建構一個元素

c.erase(args)
 移除 args 所指定的元素

c.clear()
 移除所有元素，回傳 void

---

相等性相關關係運算子
!=  <=  <  >=  >
 相等性：對所有的容器型別都有效
 關係運算（對無序的關聯式容器無效）

---

獲取迭代器
c.begin()  c.end()
 回傳指向 c 中第一個元素的迭代器，以及指向超出最後一個元素下一個位置的迭代器

c.cbegin()  c.cend()
 回傳 const\_iterator

---

可反向的容器額外的成員（對 forward\_list 無效）
reverse\_iterator
 以相反順序走訪元素的迭代器

const\_reverse\_iterator
 無法寫入元素的反向迭代器

c.rbegin()  c.rend()
 回傳指向 c 中最後一個元素，以及超出第一個元素前一個元素的位置的迭代器

c.crbegin()  c.crend()
 回傳 const\_reverse\_iterator

### 9.3.1 新增元素
#### push_back
array, forward_list 不支援
#### push_front
list, forward_list, deque 支援

新增一元素到container的運算：
    **array不支援**
    **forward_list 有特殊的insert, emplace(9.3.4)**
    **push_back, emplace_back 對forward_list無效**
    **push_front, emplace_front 對vector, string 無效**
    `c.push_back(t)`, `c.emplace_back(args)`: 在c的後面創建t or args, return void
    `c.push_front(t)`, `c.emplace_front(args)`: 在c的前面創建t or args, return void
    `c.insert(p, t)`, `c.emplace(p, args)`: 在iterator p前建立一元素, return iterator which points to the added element 
    `c.insert(p, n, t)`: 在p前面新增n個t, return iterator points to the first adding element
    `c.insert(p, b, e)`: 在p前插入iterator b, iterator e範圍中的元素
    `c.insert(p, il)`: 在p前, 插入大括號元素直傳列il
**emplace 會建構而非拷貝元素**
### 9.3.2 存取元素
存取運算:
    `c.back()`: return a reference points to the last element in c
    `c.front()`: return a reference points to the first element in c
    `c[n]`: return a reference of c[n], **no bounds checking — if n is out of range, behavior is undefined (may crash or corrupt data).**
    `c.at(n)`: return a reference of c[n],  **If n is out of range, it throws a std::out_of_range exception.**


### 9.3.3 Delete Element
#### pop_front and pop_back
`c.pop_back()`: 移除最後一個, return void
`c.pop_front()`: 移除第一個, return void
`c.erase(p)`: 移除iterator p 代表元素
`c.erase(b, e)`: 移除iterator b, e 範圍中的元素
`c.clear()`: 移除所有元素

### 9.3.4 forward_list 運算
`lst.before_begin()`: off-the-beginning iterator
insert_after, erace_after ..
移除奇數值：
```cpp
forward_list<int> flst = {0, 1, 2, 3, 4, 5};
auto prev = flst.before_begin();
auto curr = flst.begin();
while (curr != flst.end()){
    if (*curr % 2)
        curr = flst.erase_after(prev);
    else {
        prev = curr;
        ++curr;
    }
}
```
### 9.3.5 modify size of container
`c.resize(n)`: 重新調整c大小，if `n < c.size()` 元素會被捨棄.若加入新的元素，為直初始話
`c.resize(n, t)`: 調整c大小，讓它為n個t


# 9.4 vector 的增長方式
resize can't deallocate memory
`c.shrink_to_fit()`: 請求將cpapcity()降到等於size()
`c.capacity()`: c可以有的元素數
`c.reverse(n)`: 為n個元素分配空間
# 9.5 額外的string 運算
# 9.5.1 建構字串的其他方式
除了 3.2.1, 循序容器共通的運算
`string c(cp, n);`: s 是cp 前n個string 的拷貝
`string s(s2, pos2)`: s 是s2 從pos2 開始的字元
`string s(s2, pos2, len2)`: s 是s2 從pos2 開始的len2 個字元

#### `substr`運算
`s.substr(pos, n)`: return 一個string 包含s從pos開始的n個字元

### 9.5.2 修改字串的其他方式
`s.insert(pos, arg)`
`s.erase(pos, len)`
`s.assign(args)`
`s.append(args)`
`s.replace(range, args)`
### 9.5.3 string 搜尋運算
return type of string::size_type, if no match return string::npos  -> unsigned
`s.find(args)`: 在s找尋第一個args
`s.rfind(args)`: 在s找出最後一個args
`s.find_first_of(args)`: 在s找args中任一個第一個出現處
`s.find_last_of(args)`: 在s找args中任一個最後一個出現處
`s.find_first_not_of(args)`: 在s找出第一個不再args的字元
`s.find_last_not_of(args)`: 在s找出最後一個不再args的字元

### 9.5.4 `compare`函式
```cpp
int result = s1.compare(s2);

    if (result == 0) {
        cout << s1 << " == " << s2 << endl;
    } else if (result < 0) {
        cout << s1 << " < " << s2 << endl;
    } else {
        cout << s1 << " > " << s2 << endl;
    }
```
`s1.compare(0, 3, s2, 0, 3);`
### 數值轉換
```cpp
int i = 42;
string s = to_string(i);   // int -> char
double d = stod(s)  // string -> double
```
`to_string(val)`: 算術型別->string
`stoi(s, p, b)`: string中有數值內容傳為一個int, long, unsigned long, long long, unsigned long long
`stol(s, p, b)`: b is numeric base, p return a pointer points to the first not number char
`stoul(s, p, b)`
`stoll(s, p, b)`
`stoull(s, p, b)`
`stof(s, p)`: return float, double, long double
`sotd`
`stold`

# 9.6 Container Adaptor
- **Definition**: Wrappers that provide a restricted interface to an underlying container.
- **Purpose**: Adapt an existing container (e.g., `deque`, `vector`, `list`) to behave like a specific abstract data type.
- **Common Examples**:
  - `std::stack` → LIFO stack (default: `deque`)
  - `std::queue` → FIFO queue (default: `deque`)
  - `std::priority_queue` → Max-heap priority queue (default: `vector`)
- **Characteristics**:
  - Not standalone containers — rely on another container for storage.
  - Restrict access to elements (no random access in `stack`/`queue`).
  - Allow customizing the underlying container type.
- **Time Complexity**:
  - Push/Pop/Top (or Front/Back) operations are typically **O(1)**.


**container adaptor 共通運算與型別**
```cpp
size_type: unsigned integer type in C++ (and C) that is used to represent the size of objects in memory or the number of elements in a container.  big enough to hold the maximum size of any object in memory.
value_type: 元素型別
container_type: 底層容器型別
A a: create a adaptor a
A a(c): a is a copy of c
a.empty()
a.size()
swap(a, b)
a.swap(b)
```

#### Define a Container Adaptor
- constructor to create a empty object
- constructor to accept a container
#### Stack Adaptor
need **push_back, pop_back, back**
`#include <stack>`
```cpp
stack<int> intStack;
for(size_t ix = 0; ix != 10; ++ix)
    intStack.push(ix);
while (!intStack.empty()) {
    int value = intStack.top();
    intStack.pop();
}

```
**stack專屬運算**
`s.pop()`: 移除頂端，不回傳
`s.push(item)`: 在stack創建一個新的頂端元素
`s.emplace(args)`
`s.top()`: 回傳stack頂端元素
#### Queue Adaptors
need front, push_back, pop_front, back
`#include <queue>`
**queue專屬運算**
`q.pop()`: 移除前端元素，不回傳
`q.front()`: return  // queue
`q.back()`
`q.top()`: 回傳最高優先序元素  // priority_queue
`q.push()` 
`q.emblace()`











    









