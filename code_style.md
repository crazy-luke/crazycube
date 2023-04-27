# Code Style


##  Clang-Format 

```
google
```

## 项目特定约定
### 1. 头文件保护

```
#pragma once
```

## 通用约定
以 **Google C++ Style** 为基础代码风格。
* [Google C++ Style 中文](
https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)
* [Google C++ Style EN](
https://google.github.io/styleguide/cppguide.html#C++_Version)


以下为简略说明

### 1. 文件命名
全部小写，下划线分割单词

```
	app_os.h
```


###2. 类型命名：类 class , 结构体 struct,类型定义 typedef, 枚举 enum
大写字母开始, 不包含下划线

```	
    class AppOS
    struct WifiInfo
    enum GestureAction
```

###3. 变量命名

3.1 普通变量命名, 单词之间用 `_` 连接  

```
    string table_name;  //Good
    string tablename;   //Good
```


3.2 类的成员变量以 下划线 结尾

```
private：
    int num_completed_connections_;
```

3.3 全局变量以 g_ 开头

```
    bool g_data_ready;
```


3.4 结构体成员变量可以和普通变量相同

```
Struct Account{
    string nick_name;  //Good
    string age;      	//Good
};
```


3.5 常量命名，在名称前加 k 后接大写字母单词

```
    const int kDaysInAWeek = 7;
```


###4. 函数命名

4.1 普通函数: 以大写字母开头，每个单词首字母大写，没有下划线

```
uint32_t MyAwesomeMethod(CodeStype &code_style, char *output);
```

4.2 存取函数要与存取的变量名匹配

```
    int num_entries() { return num_entries_; }
	
    void set_num_entries(int num_entries) { num_entries_ = num_entries;}
```

###5. 枚举值
全部大写，单词间可以用下划线

```
	enum class GestureAction {
		FORWARD,
		ERROR_UNKNOW,
		...
	}
```



