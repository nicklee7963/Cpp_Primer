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








