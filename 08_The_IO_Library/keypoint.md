# The IO Library
# 8.1 IO 類別
**iostream**: 定義用來讀寫資料流的型別
**fstream**: 定義用來讀寫具名檔案型別
**sstream**: 定義用來讀寫記憶體內string的型別

### 8.1.1 IO 物件不能拷貝或指定
因此回傳通常是參考或資料流

### 8.1.2 Condition State
`while (cin >> word)` 避免錯誤
`iostate`用以傳達有關資料流狀態的資訊

### 8.1.3 管理輸出緩衝區
#### 排清輸出緩衝區
```cpp
cout << "hi!" << endl;   // 寫入一個newline 清空buffer
cout << "hi!" << flush;  // 不新增資料
cout << "hi!" << ends;   // 寫入一個null
```
#### unitbuf
`cout << unitbuf;   // 所有的寫入都被清`  之後cout都會自動flush
`cout << nounitbuf; // 回到原本` 

Two Ways to Tie
- 傳入 nullptr      ：解除綁定，並回傳原本綁定的 ostream*
- 傳入 ostream*     ：將 cin 綁定到該 ostream，並回傳原本綁定的 ostream*

```cpp
cin.tie(&cout) // cin cout tie
ostream *old_tie = cin.tie(nullptr);   // cin 不再綁定
cin.tie(&cerr) 
cin.tie(old_tie);
```

# 8.2 檔案輸入與輸出
- ifstream 讀取檔案
- ofstrean 寫入檔案
- fsream 讀寫檔案
### 8.2.1 使用檔案資料流物件
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 處理輸入檔案內容的函數（這裡只是範例，你可以自訂處理邏輯）
void process(ifstream& input) {
    string line;
    while (getline(input, line)) {
        cout << line << endl;
    }
}

int main(int argc, char* argv[]) {
    // 檢查是否有提供檔案名稱
    if (argc < 2) {
        cerr << "請提供至少一個檔案名稱作為參數。" << endl;
        return 1;
    }

    // 從 argv[1] 到 argv[argc - 1] 一個個讀檔
    for (auto p = argv + 1; p != argv + argc; ++p) {
        ifstream input(*p);  // 嘗試打開檔案

        if (input) {
            cout << "正在處理檔案: " << *p << endl;
            process(input);
        } else {
            cerr << "無法開啟檔案: " << *p << endl;
        }
    }

    return 0;
}


```

if `./myprog hello world 123`
then 
```cpp
argc = 4
argv[0] = ./myprog
argv[1] = hello
argv[2] = world
argv[3] = 123

```
### 8.2.2
#### File mode
預設情況下 out mode 的file會被truncated, 要保留以out開啟的內容用`app`
```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    using namespace std;

    // 動態檔名
    string filename = "example.txt";

    // 1. 用建構子打開檔案，寫入模式（會覆蓋原檔）
    ofstream out1(filename, ios::out);
    if (!out1) {
        cerr << "無法開啟檔案 " << filename << " 來寫入" << endl;
        return 1;
    }
    out1 << "這是用建構子開檔，覆蓋寫入的第一行。" << endl;
    out1.close();  // 關閉檔案

    // 2. 用預設建構子宣告，再用 open() 開檔，這次用追加模式
    ofstream out2;
    out2.open(filename, ios::app);  // 追加模式
    if (!out2) {
        cerr << "無法開啟檔案 " << filename << " 來追加" << endl;
        return 1;
    }
    out2 << "這是用 open() 加追加模式寫入的第二行。" << endl;

    // 記得關閉檔案
    out2.close();

    cout << "寫入完成，請打開 " << filename << " 查看內容。" << endl;

    return 0;
}

```
用ofstream宣告並tie to a file接這就可以用<< >> 來輸入輸出至檔案

# 8.3 String 資料流
三個型別來支援記憶體內的io
- istringstream 讀取string
- ostringstream 寫入一個string
- stringstream 讀寫string
### 8.3.1 istringstream
```cpp
struct PersonInfo{
    string name;
    vector<string> phones;
};


string line, word;
vector<personInfo> people;
while (getline(cin, line)){
    PersonInfo info;
    istringstream record(line);
    record >> info.name;
    while (record >> word)
        info.phones.push_back(word);
    people.push_back(info);

}

```

### 8.3.2 ostringstream
when we want to output multiple times, but we also want to print them later, use ostringstream
```cpp
for (const auto &entry : people) {
    ostringstream formated, badNums;
    for (const auto &nums : entry.phones){
        if(!valid(nums)) {
            badNums << " " << nums;
        }else
            formatted << " " << format(nums);

    }
    if (badNums.str().empty())
        os << entry.name << " " << formatted.str() << endl;
    else
        cerr << "input error: " << entry.name << "invalid number" << badNums.str()<<endl;
}
```
