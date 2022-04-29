# Ush(无用的计算机壳层)
它很没用，因为它只有6个命令，不能修改文件和目录，甚至不能运行.sh文件！  
ush将于开源后将被停用并停止支持，但您仍然可以免费且便捷的使用它，因为它仍然是一个很好的计算机壳层，但我们不能保证它的安全性。  
ush在编写写的时候有以下问题，但是不影响日常使用，我们将忽略它：  

1. 当你使用`cd`命令时，你将无法一次跳转到多个目录
2. 当您尝试一次运行多条指令时，输出可能会令人困惑，但仍然具有可读性
- 我们将永远期待您解决以上问题
- <u>但请不要添加新指令以确保其的安全性与便携性！</u>  

您可以通过在此项目目录中运行`./install.sh`来构建为可执行文件，如果失败，请安装 C/C++ 编译器，如 G++  

美化：
ush虽然没有配置文件，但是还是可以通过修改源码来配置  
您可以修改以下部分：
```c++
void config() //config (beautification)
{
    /*---------------------------
        user("name"): user name
        cname() computer name
        user("dir"): user dir
    ---------------------------*/
    cout << user("name") << "@" << cname() << ":";
    if (path == user("dir")) cout << "~";
    else if (path == "/") cout << "/";
    else cout << path;
    if (user("name") == "root") cout << "#";
    else cout << "$";
    }
```
以下为输出内容
```
runner:docs$
```
主题：  
robbyrussel
```
> docs
```
```c++
void config() //config (beautification)
{
    /*---------------------------
        user("name"): user name
        cname() computer name
        user("dir"): user dir
    ---------------------------*/
    cout << "> ";
    if (path == user("dir")) cout << "~";
    else if (path == "/") cout << "/";
    else cout << path;
    }
```
ys
```
# runner in docs
$
```
```c++
void config() //config (beautification)
{
    /*---------------------------
        user("name"): user name
        cname() computer name
        user("dir"): user dir
    ---------------------------*/
    cout  << "#" << user("name") << "@" << cname() << " in ";
    if (path == user("dir")) cout << "~";
    else if (path == "/") cout << "/";
    else cout << path;
    cout << endl << "$";
    }
```