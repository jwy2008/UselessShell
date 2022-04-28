#include <iostream>
#include <unistd.h>
#include <cstring>
#include <strings.h>
#include <pwd.h>
#include <dirent.h>

using namespace std;

string user(string a);
void pwd();
void cname();
void ps1();
void cd();
void ls();

string cwd = get_current_dir_name();

typedef void (*DoFunc)();

struct TCommandMap
{
    char mCommand[32];
    DoFunc mFunc;
};

struct TCommandMap gCommandMaps[] =
{
    {"ls",ls},
    {"pwd",pwd},
    {"cd",cd}
};

int main()
{
    while (true)
    {
	string input;
	ps1();
	cin >> input;
	int len = input.size();
	if (input[len-1] == '\n') input[len-1] = '\0';
	if (len == 0) continue;
	bool bFunc = false;
	for (int i=0;i<sizeof(gCommandMaps)/sizeof(struct TCommandMap);i++)
	{
	    char ch[32];
	    strcpy(ch,input.c_str());
	    if (strcasecmp(gCommandMaps[i].mCommand,ch) == 0)
	    {
		bFunc = true;
		gCommandMaps[i].mFunc();
		break;
	    }
	}
	if (!(bFunc)) cout << "sh: command not found: " << input << endl;
    }
}

void pwd()
{
    cout << cwd << endl;
}
string user(string a)
{
    uid_t userid;
    struct passwd* pwd;
    userid=getuid();
    pwd = getpwuid(userid);
    if (a == "name") return pwd->pw_name;
    else if (a == "dir") return pwd->pw_dir;
    return "";
}
void cname()
{
    char name[32];
    if(gethostname(name,sizeof(name))) perror("gethostname");
    cout << name;
}
void ps1()
{
    cout << user("name") << "@";
    cname();
    cout << ":";
    if (cwd == user("dir")) cout << "~";
    else if (cwd == "/") cout << "/";
    else cout << cwd;
    if (user("name") == "root") cout << " # ";
    else cout << " $ ";
}
void cd()
{
    string temp;
    cin >> temp;
    string temp1 = cwd + "/" + temp;
    DIR *pDir;
    if (temp == "~") cwd = user("dir");
    else if (temp == ".") cwd = cwd;
    else if (temp == "..") {for (int i=cwd.size()-1;i>=0;i--) if (cwd[i]=='/' and i != 0) {cwd=cwd.substr(0,i);break;} else if (cwd[i]=='/' and i == 0) {cwd="/";break;}}
    else if (temp[0] == '/') if (!(pDir = opendir(temp.c_str()))) {cout << "cd: no such file or directory: " << temp << endl; return ;} else cwd = temp;
    else if (!(pDir = opendir(temp1.c_str()))) {cout << "cd: no such file or directory: " << temp << endl; return ;} else cwd += "/" + temp;
    if (cwd[0] == '/' and cwd[1] == '/') cwd = cwd.substr(1,cwd.size()-1);
}
void ls()
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(cwd.c_str())))
    {
        return;
    }
    while((ptr = readdir(pDir))!=NULL)
    {
        if (strcmp(ptr->d_name, ".") != 0 and strcmp(ptr->d_name, "..") != 0 and strncmp(ptr->d_name, ".", 1) != 0)
        {
            if (ptr->d_type == DT_REG) cout << ptr->d_name << endl;
            else if (ptr->d_type == DT_DIR) cout << ptr->d_name << "/" << endl;
        }
    }
    closedir(pDir); 
}
