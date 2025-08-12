# Associative Containers
**There are eight kinds of associative containers, they all follow**
(1) either `set` or `met`
(2) need the only key or multiple key (multi)
(3) is it sequential (unordered)
map, multimap -> `#include <map>`
set, multiset -> `#include <set>`

- 元素以key sort:
    `map`: 
    `set`:
    `multimap`:
    `multiset`:
- unordered:
    `unordered_map`:
    `unorderet_set`
    `unordered_multimap`:
    `unorderet_multiset`

# 11.1 Using an Associative Containers
#### `map` (associative array)
- **key-value pairs**
- 下標不一定是整數

Using a map:
```cpp
map<string, size_t> word_count;
string word;
while(cin >> word)
{
    ++word_count[word];
}
for (const auto &w: word_count)
    cout << w.first << " occurs " << w.second;   // .first is key, .second is value
```



#### `set`
- key 構成的collection
Using a set:
```cpp
map<string, size_t> word_count;
set<string> exclude = {"The", "But", "And", "Or"};
```
# 11.2 	Overview of the Associative Containers
no push_front or back
### 11.2.1 Define a Container
```cpp
map<string, size_t> exclude={"The ", "but", "and"}
```
```cpp
map<string, string>  authors;
map <string, string> authors = {{"nick", "lee"}, {'Austen', 'may'}}


```
#### Initialize a multimap or multiset
  `multiset` can have duplicate value, while `set` can't

#### 自定義multiset
**multiset 需要 < 運算子 因此給一個函式的指標來決定我們比較的方式**
`multiset<Sales_data, decltype(compareIsbn) *`
### 11.2.3 pair 型別
`#include <utility`
**one pair has two members**
`pair<string, string> anon;`
`pair<string, string author{"James", "Joyce"}`
Pair Operation:
`make_pair(v1, v2)`: return pair of v1, v2
`p.first`: return first member
`p.second`: return second member

**map中的元素都是pair**

#### 用來創建pair 物件的一個function
```cpp
pair<string, int> process(vector<string> &v)
{
    if(!v.empty())
        return {v.back(), v.back().size()};   // list initialize
        // make_pair(v.back(), v.back.size())
        
    else
        return pair<string, int>()  // specific value
}
```
# 11.3 Operations on Associative Containers
**pair.first is a const**
- key_type
- mapped_type: only map
- value_type: for set it is also key_type; for map it is `pair<const key_type>`
```cpp
set<string>::value_type v1;  // string
map<string, string>::value_type v2; // pair<const string, string>
map<string, int>::key_type v3;  // string
map<string, int>::mapped_type v4; // int
```

#### Iterator of `set` is const
### 11.3.2 Add Element
use `insert`
```cpp
vector<int> ivec = {1, 2, 3, 4, 5, 6};
set<int> set2;
set2.insert(ivec.cbegin(), ivec.cend());

```
#### Insert to map
four ways to insert:
```cpp
word_count.insert({word, 1});
word_count.insert(make_pair(word, 1));
word_count.insert(pair<string, size_t>(word, 1);
word_count.insert(map<string, size_t>::value_type(word, 1);
```
#### Return from insert
pair.first: iterator points to element(type == pair) to insert
pair.second: bool, check if the element is inserted
#### Insert to multiset/ multimap
no need to return bool: because it will always insert
### 11.3.3 Clear Element
`c.erase(k)`: erase element whose key is k, return size_type indicating how many elements be removed
`c.erase(p)`: erase element p points to, return the next of p (p is not c.end())
`erase(b, e)`: erase elements inside b and e, return e
### 11.3.4 為一個map 添標
**set 不支援下標** because it has no value
**multimap, unordered_multimap 沒有下標**
**使用下標如果不存在 會創要新的值**
```cpp
map <string, size_t> word_count;
word_count["Anna"] = 1;   // create an element
```
**下標回傳的是 mapped_type, 解參考map 的到的是 value_type**
### 11.3.5 Accessing Element
Operation:
`c.find(k)`: find k, return a iterator points to the first element with k; if no elements, return off-the-end iterator
`c.count(k)`: count the number of elements which value is k
`c.lower_bound(k)`: return a iterator pointing to the first element which is not smaller than k
`c.upper_bound(k)`
`c.equal_range(k)`: return two iterators, within them are the elements equal to k
#### 使用find 取代下標
**If we don't want to change tha map and find if an element is in the map, use find**
#### Find Element in multimap / multiset
**有多個元素具有一個key 會彼此相鄰**
# 11.4 Unordered Container
**hash function and == operator in key**
use Buckets to make hash table
Operation:
- Bucket Interface:
    - `c.bucket_count()`: count bucket
    - `c.max_bucket_count()`: max bucket
    - `c.bucket_size(n)`: nth bucket elements number
    - `c.bucket(k)`: find the bucket with k
- Bucket Iteration:
    - `local_iterator`
    - `c.begin(n), c.end(n)`: points to the first element in bucket n, and 超出最後一個
- Hash Strategy:
    - `c.load_factor()`: 每個bucket's average number 
    - `c.max_load_factor()`: 
    - `c.rehash(n)`: 重新組織讓bucket_count >= n
    - `c.reserve(n)`: 重組, 讓c可以存放n個元素



