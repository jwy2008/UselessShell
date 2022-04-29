# Ush(Useless Shell)
It is useless because it has only 6 commands, can not modify files and directories, and can not even run .sh files!  
ush will be deactivated and discontinued after it is open sourced, but you can still use it for free and quickly, as it is still a good computer shell, but we cannot guarantee its security.  
ush has the following issues when writing, but it doesn't affect everyday use, so we'll ignore it:
1. When you use the ```cd``` command, you will not be able to jump to multiple directories at once
2. When you run multiple instructions at once, the output may be confusing, but it is still readable  
- We will always look forward to your fixing this issue
- <u>But please don't add new directives to keep it safe and portable!</u>

You can build as an executable by running `./install.sh` in the directory of this project, and if that fails, install a C/C++ compiler like G++  

beautification:  
Although ush does not have a configuration file, you can still configure it by modifying the source code  
You can modify the following sections:
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
The default output here is
```
runner:docs$
```

robbyrussel:
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