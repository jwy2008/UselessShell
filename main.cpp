#include <iostream>
#include <unistd.h>
#include <cstring>
#include <strings.h>
#include <pwd.h>
#include <dirent.h>

using namespace std;

string user(string a);
void cname();
void config();
void pwd();
void cd();
void ls();
void help();
void exit();

string path = get_current_dir_name();

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
    {"cd",cd},
    {"help",help},
    {"exit",exit}
};

int main()
{
    while (true)
    {
	string input;
	config();
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

void config()
{
    cout << user("name") << "@";
    cname();
    cout << ":";
    if (path == user("dir")) cout << "~";
    else if (path == "/") cout << "/";
    else cout << path;
    if (user("name") == "root") cout << " # ";
    else cout << " $ ";
}

void pwd()
{
    cout << path << endl;
}

void cd()
{
    string temp;
    cin >> temp;
    string temp1 = path + "/" + temp;
    DIR *pDir;
    if (temp == "~") path = user("dir");
    else if (temp == ".") path = path;
    else if (temp == "..") {for (int i=path.size()-1;i>=0;i--) if (path[i]=='/' and i != 0) {path=path.substr(0,i);break;} else if (path[i]=='/' and i == 0) {path="/";break;}}
    else if (temp[0] == '/') if (!(pDir = opendir(temp.c_str()))) {cout << "cd: no such file or directory: " << temp << endl; return ;} else path = temp;
    else if (!(pDir = opendir(temp1.c_str()))) {cout << "cd: no such file or directory: " << temp << endl; return ;} else path += "/" + temp;
    if (path[0] == '/' and path[1] == '/') path = path.substr(1,path.size()-1);
}

void ls()
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
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

void help()
{
    cout << "[Help]:" << endl << "cd exit help ls pwd" << endl;
}

void exit()
{
    exit(0);
}
