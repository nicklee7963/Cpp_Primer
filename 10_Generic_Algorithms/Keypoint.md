# Generic Algorithms
# 10.1 概觀
`#include <algorithms` 
```cpp find(vec.cbegin(), vec.cend(), val); // look for every elements between cbegin and cend, find the one equal to val
```
# 10.2 演算法初探
### 10.2.1 唯讀演算法
e.g. find, accumulate, equal
#### `accumulate`
```cpp
#include <numeric>
int sum = accumulate(vec.cbegin(), vec.cend(), 0);
// the first two argument is the range that we want to get the sum
// the last one is the initial value
// last one also determent which + operator to use
```
```cpp
string sum = accumulate(v.cbegin(), v.cend(), string(""));
// string sum = accumulate(v.cbegin(), v.cend(), ""); // compile error, string literal doesn't have + operator
```

#### `equal`
`equal(roster1.cbegin, roster1.end(), resoter2.cbegin())`  check if they are the same
### 10.2.2 寫入容器元素的演算法
e.g. fill
#### `fill`
```cpp
fill(vec.begin(), vec.end(), 0); // initialize every element to zero
```
#### `fill_n`
```cpp
fill_n(dest, n, val);  // dest is the first iterator we want to write in 
```

#### back_inserter Indroduction
**To ensure an algorithm have enough element to store an output is using 'insert interator'.**
`#include <iterator>`
```cpp
vector<int> vec;
auto it = back_iterator(vec);
*it = 42;    // equal to vec.push_back(42)

fill_n(back_inserter(vec), 10, 0)
```

#### Copy Algorithm
- `copy`
    `copy(itr1, itr2, itr2)`: itr1, itr2 表示要複製的東西, itr3表示目的位置的第一個元素
- `replace`
    `replace(ilist.begin(), ilist.end(), 0, 42)`;   // every 0 change to 42
- `replace_copy`: if we don't want to change the original container
    `replace_copy(list.cbegin(), list.cend(), back_inserter(ivec), 0, 42)`  // 將更改後的果傳入 `back_inserter(ivec)`
### 10.2.3 Algorithm Changing Sequence
e.g. sort
#### 消除重複的
check 01_unque.cpp
```cpp
void elimDups(vector<string> &words)
{
    sort(words.begin(), words.end();

    auto end_unique = unique(words.begin(), words.end());

    words.erase(end_unique, words.end());

}
```
#### `unique`
- return a iterator pointes to the end of unique values  (超出最後位置一個位置)

# 10.3 自訂運算
### 傳遞函式給演算法
#### Predicates(判斷式)
用參數數量區分
- unary predicates
- binary predicates
```cpp
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}
sort(words.begin(), words.end(), isShorter);
```
#### Sorting Algorithm
- stable_sort: 相等的元素維持原本排序
`stable_sort(words.begin(), words.end(), isShorter)`
### 10.3.2 Lambda 
**prdeicates must only have one or two argument**

```cpp
void biggies(vector<string> &words, vector<string>::size_type sz){
    elimDups(words); 
    stable_sort(words.begin(), words.end(), isShorter());
}

```


`find_if`: first two arguments is iterator as range, the last one is an arg, it put every elements to this arg and return the first non zero 
#### Lambda Introduction
we can pass any **callable object** to algorithm: if we can use() it is a callable object, e.g. function, function pointer, lambda ...
**lamba**: a no name inline function
`[capture list](parameter list) -> return type {function body}`
- capture list: 是定義在外圍函式中的一個區域變數串列
**lambda 必須用tralling return**
**capture list, function body can't ignore**
```cpp
auto f = [] { return 42;};
cout << f() << std::endl;

```
**lambda 不能有預設引述**
isShorter:
`[](const string &a, const string &b) { return a.size() < b.size();}`
**lambda 可以使用外圍函式的某個區域變數，但只有在這個lambda 有捕捉才可以**

#### for_each Algorithm
```cpp
auto wc = find_if(words.begin(), words.end(), [sz](const string &a){return a.size() >= sz; });

for_each(wc, words.end(), [](const string &s) { cout << s << " "; });
```
### 10.3.3 Lambda 的捕捉與回傳
#### Capture by Value
與參數不同，被捕捉的變數會在lambda被創建時捕捉，不是呼叫時
```cpp
void fc1()
{
    size_t v1 = 42;
    auto f = [v1] {return v1;};
    v1 = 0;
    auto j = f();  // j is 42

}
```
#### Capture by Reference
```cpp
void fc2(){
    size_t v2 = 42;
    auto f2 = [&v2] {return v2;};
    v2 = 0;
    auto j = fc2();   // j is 0
}
```
**ostream can not be copied**

#### Implicit Capture
**不明確列出用捕捉變數**
- &: 用參考捕捉
- =: 用值捕捉
```cpp
wc = find_if(words.begin(), words.end(), [=](const string &s){ return s.size() >= sz;});

```cpp
Lambda 捕捉串列
- []: 空的
- [names]: 捕捉變數
- [&]: 參考捕捉, implicit
- [=]: capture by value, implicit
- [&, identifier_list]: identifier_list is captured by value, the other is captured by reference
- [=, reference_list]: reference_list is captured by reference, the other is captured by value 
#### Mutable Lambda
一般情況lambda 不能改變它捕捉的變數值
**Mutable Lambda must have parameter list**
```
auto f = [v1] () mutable { return ++v1;};
```
#### 指定lambda 的回傳型別
```cpp
transform(v1.begin(), v1.end(), v2.begin(), [](int i) { return i < 0 ? -i : i;}); // wrong, lambda return void
// transform 把input list 經過 lambda 傳入v2.begin()
// if v2.begin() == v1.begin() then every element in v1 will be changes to value after lambda

transform(v1.begin(), v1.end(), v2.begin(), [](int i) -> int{ return i < 0 ? -i : i;});  // ok
```

### 10.3.4 繫結引數
bind function:
`#include <functional>`
通用的函式轉接器，接受一個可呼叫物件，並產生一個新的collable 來轉接原物件的參數列
`auto newCallable = bind(collable, arg_list)`: 當我們呼叫newCallable, newCallable 會呼叫collable,傳入arg_list中的引數
```cpp
auto wc = find_if(words.begin(), words.end(),
                  std::bind(check_size, std::placeholders::_1, 6));
```
- `_1` 代表第一個參數位置，保留給 find_if 的元素傳進來

- 6 固定為 check_size 的第二個參數
#### 繫結參考引數
bind 用的都是copy, in order to copy by reference we need to use 'ref'
```cpp
for_each(words.begin(), words.end(), bind(print, ref(os), -1, ' '));
```
**`cref` 用來存放對一個const的reference**
# 10.4 再訪迭代器
`#include <iterator>`
- insert iterator: 
    接受一個容器，產生一個能把元素新增到容器的iterator
    - back_inserter: an iterator using push_back
    - front_inserter: an iterator using push_front
    - inserter: an iterator using insert
    ```cpp
    list<int> lst = {1, 2, 3, 4};
    list<int> lst2, lst3;
    copy(lst.cbegin(), lst.cend(), front_inserter(lst2)); //4, 3, 2, 1
    copy(lst.cbegin(), lst.cend(), inserter(lst3)); // 1, 2, 3, 4
    ```

- stream iterator:
    bind to istream or ostream
    - istream iterator:
        ```cpp
        istream_iterator<int> int_it(cin);   //從cin讀取int
        istream_iterator<int> int_eof;    // 結尾
        ifstream in("afile");
        istream_iterator<string> str_it(in);  //從afile讀取string
        
        #include <iostream>
        #include <iterator>

        int main() {
            std::istream_iterator<int> int_it(std::cin);
            std::istream_iterator<int> int_eof;

            while (int_it != int_eof) {
                std::cout << "Read: " << *int_it << "\n";
                ++int_it; // 讀下一個 int
            }
        }

        ```
        一旦讀取失敗或 EOF，這個迭代器就變成「end 狀態」，等於 `int_eof`
    - ostream iterator:
        `ostream_iterator<T> out(os);   // out將type T 的直寫出資料流os`
        `ostream_iterator<T> out(os, d)`   // 每次輸出伴隨d
        ```cpp
        ostream_iterator<int> out_iter(cout, " ");
        for(auto e : vec)
            *out_iter++ = e;    // == out_iter=e

        ```
    
    

- reverse iterator:
    往回尋訪一個容器迭代器(++變成往前找)
    **reverse_iterator變回一般iterator**: .base()
    

- move iterator:


# 10.5 泛用演算法結構
演算法所需的迭代器運算可以分成五個 **iterator categories** 每個演算法都指定必須為每一個迭代器參數提供什麼迭代器
#### Iterator Categories
- input iterator: 讀取但不寫入, single pass
    need to provide:
    - `==, !=`
    - `++`
    - `*`
    - `->` 
    e.g.: `istream_iterator`
- output iterator: 寫入不讀取, single pass
    need to provide:
    - `++`
    - `*`
    e.g. `ostream_iterator`
- forward iterator:
    e.g. `forward_list`
- bidrectional iterator: 
    need `--`
    e.g. `reverse`

- random_access iterator:
    need to provide:
    - `<, <=, >=`
    - `+, -, +=, -=`
    - `-`: 算出距離
    - 下標運算子
    e.g. `sort`, `array`, `deque`, `vecttor`, `string`

### 10.5.3 Naming Algorithm
`unique(beg, end)` 使用==比較
`unique(beg, end, cond)` 使用cond比較

#### `_if`
`find(beg, end, val)` 找到val的第一個
`find_if(beg, end, pree)` 找到地一個pree為真的
#### copy
`reverse(beg, end)` 反轉輸入範圍中的元素
`reverse_copy(beg, end, dest)` 將反轉結果輸出給dest
# 10.6 容器限定的演算法
`list` & `forward_list`應該優先選用串列成員版本,而非泛用版本
Not Reccommended:
```cpp
#include <list>
#include <algorithm>

int main() {
    std::list<int> lst = {1, 2, 3, 2, 4};

    // std::remove 不會真的刪掉，只會移動元素
    auto new_end = std::remove(lst.begin(), lst.end(), 2);
    lst.erase(new_end, lst.end()); // 必須再呼叫 erase 才能刪掉
}
```
Reccommnded:
```cpp
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 2, 4};

    lst.remove(2); // 直接刪掉所有等於 2 的節點
}

```
#### `slice`

`splice` 是 C++ `list`（雙向鏈結串列）和 `forward_list`（單向鏈結串列）提供的成員函式，  
用來 **把另一個串列中的元素搬移到目前串列的指定位置**，  
搬移時不會複製元素，也不會產生新節點，僅透過改變節點指標連結達成，因此效率非常高。

1. 將 other 所有元素移到 pos 前
```cpp
void splice(iterator pos, list& other);
```
2. 把 other 中 it 指向的元素搬到 pos 之前
```cpp
void splice(iterator pos, list& other, iterator it);

```
3. 把 other 中 [first, last) 範圍的元素搬到 pos 之前
```cpp
void splice(iterator pos, list& other, iterator first, iterator last);

```







