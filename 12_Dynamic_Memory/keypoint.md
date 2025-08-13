# Dynamic Memory
# 12.1 動態記憶體與智慧指標
- `new`
- `delete`
Two kinds of smart pointer: delete object automatically
`#include <memory>`
- `shared_ptr`: allow multiple pointers point to smae object
- `unique_ptr`: owns the object it point
- `weak_ptr`
### 12.1.1 shared_ptr
```cpp
shared_ptr<string> p1;
shared_ptr<list<int>> p2;
```
#### `make_shared` function
**return a shared_ptr pointing to that object**
```cpp
shared_ptr<int> p3 = make_shared<int>(42);
shared_ptr<string p4 = make_shared<string>(10, '9');
```
**reference count**
```cpp
auto r = make_shared<int> (42);   //  r 所只的int有一個使用者 

r=q;  
```
#### shared_ptr delete object automatically
**shared_ptr 紀錄有多少指針指向同一個物件， 當變成0 自動刪除物件**
by using **destructor**
Operation for `shared_ptr`:
`p.unique()`: if p.count() is 1, return true

`p.use_count()`: return object used with p

#### Three condition to use dynamic memory
1. Don't know how many elements they need
2. Don't know the object type
3. Need to shared data **多個物件共用相同狀態**
#### Define StrBlob
### 12.1.2 直接管理記憶體
#### 使用 `new`
`int *pi = new int;`  undefined
`int *pi = new int(1024)`
`int *pi1 = new int()`  initialize to 0
#### 記憶體耗盡
`#include <new>`
**If fail to allocate by using new, it will throw 'bad_alloc'**
`int *p2 = new (nothrow) int;` if allocate failed, it will not throw exception
#### 在`delete` 後 重製一個指標的直
after delete pointer will become **dangling pointer** points to its old memory
### 12.1.3 併用`shared_ptr` and `new`
`shared_ptr<int> p2(new int (42));`
**Beause smart pointer's constructor is explicit**
`shared_ptr<int> p2 = new int (1024)`  is wrong
#### Don't use original pointer and smart_pointer together
`p.get()`: 會回傳普通指標(p is a smart_ptr)
#### Other Operation
`p = new int(1024)` wrong  int* -> smart_ptr will fail
`p.reset(new int (1024))` correct
#### Dumb Classes 
**有些類別沒有自己的清理函式，發生中斷時無法自動釋放資源，所以用 shared_ptr<T> p(p2, d) 讓 p 指向 p2 的物件，並在物件刪除時自動呼叫 d。**
`shared_ptr<int> p1(p2)` 不要這樣 用拷貝或指定的方式 讓它門共用一個控制區域
`shared_ptr<int> p1 = p2` 這樣


### 12.1.5 `unique_ptr`
一次只有一個unique pointer 可以指向一個物件
**no copy and assignment**
Operation:
`u = nullptr` 刪除u指到的物件
`u.release()`: 放棄u的控制權 return u 的指標
`u.reset()`: 刪除u 指的物件
`p2.reset(p3.release());`  將所有權從p3轉到p2
#### 覆寫一個deleter
需要在創見unique 時，把deleter 放在`<>` 中

`unique_ptr<objT, delT> p (new ogjT, fcn);`
### 12.1.6 `weak_ptr`
`weak_ptr` 指向 `shared_ptr` 指到的物件
**將一個`weak_ptr` 細節到smart pointer 物件上不會增加計數**
```cpp
auto p = make_shared<int> (42);
weak_ptr<int> wp(p);
```
因為weak pointer 的物件可能被刪除 所以要先用lock 檢查
```cpp
if (shared_ptr<int> np = wp.lock()){

}

```

`w.expired()`: if w.use_count == 0, return True;
`w.lock()`: if w.expired() == true , return null or else return a shared_ptr pointing to *w
# 12.2 Dynamic Array
### 12.2.1 `new` and Array
[] to assign how many objects to allocate
`int *piaj = new int[get_size()]`;
**Dynamic array doesn't have array type**
```cpp
int *pia = new int[10] // undifined
int *pia2 = new int[10](); // initialize to 0
int *pia3 = new int [10]{0, 1, 2, 3, 4, 5};

```
#### Release Dynamic Array
`delete [] pa;`  last element will be destroyed first
#### Smart Pointer and Dynamic Pointer
```cpp
unique_ptr<int []> up(new int[10]);
up.release();  // delete []
```
**When a unique pointer points to an array, we can't use .,  -> operator**
**When a unique pointer points to an array, we can**
`up[i] = i` to assign 
If we want to use shared_pointer to points to an array, we need to provide our own deleter
`shared_ptr<int> sp(new int[10], [](int *p){ delete[] p;});`
### 12.2.2 `allocator`
分配記憶體包含：
- allocation: get memory
- construction: call constructor on memory we got
為了一次拿很多記憶體 又不要一個一個等construct 我們使用'allocator'
#### allocator 類別
`#include <memory>`
```cpp
allocator<string> alloc;     // 能夠配置string的物件
auto const p = alloc.allocate(n); // 配置n個未建構 string

```
Operation:
- `allocator<T> a`  
  定義一個 allocator 物件 `a`，可以為類型 `T` 分配記憶體。

- `a.allocate(n)`  
  為 `T` 分配 `n` 個未初始化的記憶體單位。

- `a.deallocate(p, n)`  
  釋放由 `allocate` 分配的記憶體 `p`，在此之前需要先呼叫 `destroy`。

- `a.construct(p, args...)`  
  在指標 `p` 指向的記憶體上呼叫 `T` 的建構函式，`args` 是建構參數。

- `a.destroy(p)`  
  呼叫指標 `p` 上物件的析構函式，釋放物件資源，但不釋放記憶體。
#### 拷貝與填入未初始化的記憶體演算法
`#include <memory>`
#### 拷貝與填入未初始化的記憶體演算法
需要 #include <memory>

1. **uninitialized_copy** `(InputIt first, InputIt last, ForwardIt d_first)`  
   - 功能：將一個範圍的已初始化元素拷貝到未初始化的記憶體區域中。  
   - 參數說明：
     - `first`：來源範圍的起始迭代器  
     - `last`：來源範圍的結束迭代器  
     - `d_first`：目標未初始化記憶體的起始迭代器  

2. **uninitialized_copy_n** `(InputIt first, Size n, ForwardIt d_first)`  
   - 功能：將來源範圍前 n 個元素拷貝到未初始化記憶體。  
   - 參數說明：
     - `first`：來源範圍的起始迭代器  
     - `n`：要拷貝的元素個數  
     - `d_first`：目標未初始化記憶體的起始迭代器  

3. **uninitialized_fill** `(ForwardIt first, ForwardIt last, const T& x)`  
   - 功能：在未初始化的記憶體範圍中，用指定的值填滿。  
   - 參數說明：
     - `first`：目標未初始化記憶體的起始迭代器  
     - `last`：目標未初始化記憶體的結束迭代器  
     - `x`：要填入的值  

4. **uninitialized_fill_n** `(ForwardIt first, Size n, const T& x)`  
   - 功能：在未初始化記憶體中填入指定數量 n 的值。  
   - 參數說明：
     - `first`：目標未初始化記憶體的起始迭代器  
     - `n`：要填入的元素個數  
     - `x`：要填入的值


















