# Strings, Vectors and Arrays
# 3.1 'Using' to Declare Namespace
**Header file should have using**
# 3.2 String
```cpp
#include <string>
using std::string;
```
### 3.2.1 Define and Initialize String
```cpp
string s1;
string s2 = s1;
string s3 = "hiya";
string s4(10, 'c');
```
**Initialize**
- copy initialization: `string s5 = "hiya";`
- direct initialization: `string s6("hiya");`

### 3.2.2 Operation on String
**getline(std::cin, line)**: read a line
#### When we use both string and char literals a operand has to be string
```cpp
string s4 = s1 + ", "; //ok
string s5 = "hello" + "world" //wrong
string s6 = s1 + ", " + "world" // ok
string s7 = "hello" + ',' + s2;  // wrong because "hello" + "," is wrong
```
#### How to Deal With each char
```cpp 
for (auto c: str)
```

### Use for loop to Change Char in a String
```cpp
for (auto &c: str)
```

# 3.3 Vector
vector 是一個物件的群集，每個物件都有相同type
```cpp
#include <vector>
using std::vector;

vector<int> ivec;
```

**vector is a class template**
### 3.3.1 Define and Initiaize
```cpp
vector<int> ivec;   // empty
vector<int> ivec2(ivec);   // copy ivec to ivec2
vector<int> ivec3 = ivec;    //copy ivec to ivec3

// list initialize
vector<string> articles = {"a", "av", "abc"};
vector<string> articles2{"a", "av", "abc"}; // ok
vector<string> articles2("a", "av", "abc"); // wrong 


### 3.3.2 Add an Element to a Vector
```cpp
vector<int> v2;
for (int i = 0; i != 100; ++i)
    v2.push_back(i);
```


### 3.3.3 Other Operations on Vector
**For loop to get each element**
```cpp
for (auto i: v)
```

# 3.4 Introduction of Iterator
**Iterator give as a indirect access to an object**
### 3.4.1 Getting Started
**begin, end** is iderators, end return a iterator which is out of bound
```cpp
string s("some string");
if (s.begin() != s.end())     // make sure s is not empty
{
    auto it = s.begin();
    *it = toupper(*it);
}


for (auto it = s.begin(); it != s.end() && !isspace(*it); ++ it)
    *it = toupper(*it);
```
**If a string or vector is const we can only use const_iterator**
```cpp
auto it3 = v.cbegin()  // return a const_iterator
auto it4 = v.cend()
```
### 3.4.2 Iterator Arithmetic 
```cpp
iter + n  // move back n elements
```

# 3.5 Array
**Have fixed size**
### 3.5.1 Define and Initialize
**Size in array must be constexpr**
**Char array has null in the end**
```cpp
const char ar[4] = "Anne"   // wrong Null has no space to place

// no copy and assign
int a2[] = a;   // wrong 
a2 = a;    // wrong

int *ptrs[10];  // ptrs is an array of int*
int (*parray)[10]  // parray points to int[10]
```
### 3.5.2 Access an Element
**size_t is defined in <cstddef>

### 3.5.3 Pointer and Array
**When we use array, we actually points to its initial element**
```cpp
int ia[] = {0, 1, 2, 3, 4}
auto ia2(ia);    // ia2 is a int* points to first element in ia
```
**decltype(ia) will return type array not pointer**

#### Use iterator to get the begin of c-style array
```cpp
#include <iterator>
int ia[] = {1, 2, 3,4 }
int *beg = begin(ia);
```

### 3.5.5 Std::string v.s. C-style string
std::string convert to c-style string need to use `.c_str()`


# 3.6 Multidimensional Arrays
```cpp
int ia[2][3];
for(const auto row: ia)
    for(auto col :row)
        cout << col <<endl;    
// wrong 
```
**Except the inner for loop all variable should use references**
```cpp 
int ia[2][3];
for(const auto &row: ia)
    for(auto col :row)
        cout << col <<endl;    
```































