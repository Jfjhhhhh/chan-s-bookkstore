# chan-s-bookstore
#
# 程序功能：
######        构建三个系统，记录账户、图书、日志相关信息。读入指令，判断指令是否合法，并进行对应操作。
#

# 类的接口与成员：

主要类有：
- TokenScanner类（负责获取指令）
- user_account类 （负责存储账户信息）
- user类 （处理账户相关指令）
- book_inf类 （负责存储书的信息）
- book类 （负责维护图书信息）
- error类 

## 各个类的接口和成员说明

### **TokenScanner类**

成员：
- std::string line 存储要处理的字符串

函数：
```
TokenScanner () 构造函数
~TokenScanner () 析构
std::string nextToken() 获得下一片切分
bool haveMoreTokens() 判断是否还有
bool check_? 检查各种合法
double StringtoDouble()
```
### **account类**
成员
```
 char ID[32];
 char password[32];
 int privilege;
 char name[32];
```
函数
```
user_account()
user_account(const char* ID_,const char* password_,const int privilege_,const char* name_)
user_account &operator= (const account &obj)‘’

重载运算符
```
### **user类**

成员

```
database<user_account> users; 存账户信息的数据库
std::vector<user_account> login_stack; 登录栈
bool exit; 退出条件
```

函数
```
user(); 初始化root
void su(Tokenscanner &scanner); 登录
void logout(); 登出
void Register(Tokenscanner &scanner); 注册
void passwd(Tokenscanner &scanner); 修改密码
void user_add(Tokenscanner &scanner); 创建账户
void user_delete(Tokenscanner &scanner); 删除用户
```
### **book_inf类**
成员
```
char ISBN[21];
char bookname[61];
char author[61];
char keyword[61];
int store;
double price;
```
函数
```
book_inf() 初始化
book_inf(const char* ISBN_,const char* bookname_,const char* author_,const char* keyword_)
重载运算符
```
### **book类**

成员
```
database<book_inf> books;
std::vector<std::string> book_stack; 图书信息栈
```

函数
```
void login() 登录的同时选一本空书
void logout() 登出的同时取消选书
void show(Tokenscanner &scanner,user &users) 查询书籍
void buy(Tokenscanner &scanner,user &users,diary &diarys)买书
void select(Tokenscanner &scanner,user &users) 选书
void modify(Tokenscanner &scanner,user &users) 修改图书信息
void import(Tokenscanner &scanner,user &users,diary &diarys) 进货
```
 ## 
