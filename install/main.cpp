#include <string>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
using namespace std;

void writeStr(string s, string filename);
string sys(string sys, string sock);
string read(string filename, char stop = '\0');
unsigned long filesize(string file);
void Char(string s, char* &dest);
void executeCmd(string cmd, string filename, string socketfilename);

int main(int argc, char* argv[]) {
	/*
	 * Первый шелл
		 создает каталоги 
		 $home/.qdjs/gjs
		 $home/.qdjs/qdjs
		 создаёт файл  gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh
	*/
	string cmd = "#! /bin/bash\n";
	cmd += "mkdir $HOME/.qdjs\n";
	
	cmd += "rm -rf $HOME/.qdjs/gjs\n";
	cmd += "rm -rf $HOME/.qdjs/qdjs\n";
	
	cmd += "mkdir $HOME/.qdjs/gjs\n";
	cmd += "mkdir $HOME/.qdjs/gjs/releases\n";
	cmd += "mkdir $HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/\n";
	cmd += "mkdir $HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64\n";
	cmd += "mkdir $HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js\n";
	
	cmd += "echo 'dir=$HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js\n";
	cmd += "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$dir'/lib/lib'\n";
	cmd += "export QT_PLUGIN_PATH=$dir'/lib/plugins'\n";
	cmd += "' > $HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh\n";
	cmd += "echo '$dir/hw $1 $2 $3\n' >> $HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh\n";
	cmd += "chmod 766 $HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh\n";
	
	executeCmd(cmd, "/tmp/amarketshell1.sh", "/tmp/amarketsocket1");
	
	/**
	 * Второй шелл запускается от root и ставит 
	 git
	 и создает ссылку на 
	 /usr/local/bin/qdjs gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh
	*/
	
	cmd = "echo 'sudo apt-get install git'\n";
	cmd += "echo 'sudo rm /usr/local/bin/qdjs'\n";
	cmd += "echo \"sudo ln -s $1/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh /usr/local/bin/qdjs\"\n";
	
	cmd += "sudo apt-get install git -y\n";
	cmd += "sudo rm /usr/local/bin/qdjs\n";
	cmd += "sudo ln -s $1/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh /usr/local/bin/qdjs\n";
	
	//тут же начинаем добавлять третий шелл,
	//который качает данные из репозиториев и распаковывает их
	cmd += "cd $HOME/.qdjs\n";
	cmd += "mv gjs _gjs\n";
	cmd += "git clone https://github.com/lamzin-andrey/gjs.git\n";
	cmd += "cd gjs/releases/ubuntu-14.04-18.4/amd64\n";
	cmd += "tar -xvzf desktop-js.tar.gz\n";
	cmd += "cp -f $HOME/.qdjs/_gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh $HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64/desktop-js/run.sh\n";
	cmd += "rm -rf $HOME/.qdjs/_gjs\n";
	
	cmd += "cd $HOME/.qdjs/gjs/releases/ubuntu-14.04-18.4/amd64\n";
	cmd += "tar -xvzf hw.tar.gz\n";
	cmd += "cp -f hw desktop-js/hw\n";
	cmd += "rm hw\n";
	
	
	cmd += "cd $HOME/.qdjs\n";
	cmd += "git clone https://github.com/lamzin-andrey/qdjs.git\n";
	cmd += "\n";
	cmd += "\n";
	
	cmd += "echo 'Press any key to quit'\n";
	cmd += "read\n";
	
	writeStr(cmd, "/tmp/amarketshell2.sh");
	
	string filename = "/tmp/amarketshell2.sh";
	sys("chmod 766 " + filename, "/tmp/amarketsocket2");
	cmd = "xfce4-terminal --command=\"" + filename + " $HOME\" \n";
	
	executeCmd(cmd, "/tmp/amarketshell3.sh", "/tmp/amarketsocket3");
	
	//Запуск amarket/amarket-installer/amarket-installer.sh
	cmd = "$HOME/.qdjs/amarket/amarket-installer/amarket-installer.sh";
	executeCmd(cmd, "/tmp/amarketshell4.sh", "/tmp/amarketsocket4");
	
	
	cmd = "unlink /tmp/amarketshell4.sh\n";
	cmd += "unlink /tmp/amarketsocket4\n";
	
	cmd += "unlink /tmp/amarketshell3.sh\n";
	cmd += "unlink /tmp/amarketsocket3\n";
	
	cmd += "unlink /tmp/amarketshell2.sh\n";
	cmd += "unlink /tmp/amarketsocket2\n";
	
	cmd += "unlink /tmp/amarketshell1.sh\n";
	cmd += "unlink /tmp/amarketsocket1\n";
	
	executeCmd(cmd, "/tmp/amarketshell4.sh", "/dev/null");
	
	return 0;
}

void executeCmd(string cmd, string filename, string socketfilename) {
	writeStr(cmd, filename);
	sys("chmod 766 " + filename, socketfilename);
	sys(filename, socketfilename);
}

void writeStr(string s, string filename)
{
//Вывод в файл
  ofstream t;
  t.open(filename.c_str(), ios:: out);
  t << s;
  t.close();
}

string sys(string sys, string sock) {
        sys += " > " + sock;
        //char* s = new char[sys.length() + 1];
        //Char(sys, s);
        system(sys.c_str());

        unsigned long sz = filesize(sock);
        while (true) {
                system("sleep 1");
                unsigned long csz = filesize(sock);
                if (csz == sz) {
                        string s = read(sock);
                        return s;
                }
                sz = csz;                
        }
        return "";
}

string read(string filename, char stop)
{
	unsigned int i;
   string s = "";
   char* path = new char [filename.length()+1];
   for ( i = 0; i < filename.length(); i++)
	   path[i]= filename[i]; 
	   path[i] = '\0';
  ifstream t;
  t.open(path, ios:: in);
  
  string q = "";
  while ( std::getline(t, q ) ) {
	  s += q + "\n";
	  //for (int i = q.length(); i < 32000; i++) res[i] = '\0';
	  q = "";
  }
  t.close();
  
  if (s.length() > 0)
	s = s.substr(0, s.length() - 1);
  //cout <<"\nReport = '" << s<< "'\n";
  return s;
}


unsigned long  filesize(string file) {
        char* c_file = new char[file.length() + 1];
        Char(file, c_file);
        struct stat state;
        stat(c_file, &state);
        return (unsigned long)state.st_size;
}

void Char(string s, char* &dest)
{
 dest = new char[s.length()];
 int i = 0;
 for (i = 0;  i < s.length(); i++) 	dest[i] = s[i]; 
 dest[i] = '\0';
}
