//Created by meoja 
//A simple gitupdate tool
//'g++ -o gitupdate update.cpp'to compile
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<string>

class FileExtra
{
public:
	FileExtra(const char* filename)
	{
		context = "";
		FILE* fp = NULL;
		fp = fopen(filename,"r");
		if(fp == NULL)
		{
			printf("Error accessing %s\n",filename);
			return ;
		}
		char buffer[2048];
		while(fgets(buffer,2048,fp)!=NULL)
		{
			context += buffer;
		}

		if(fp)
		{
			fclose(fp);
			fp = NULL;
		}
	}
	const std::string& getContext() noexcept
	{
		return context;
	}
private:
	std::string context;
};

int main(int cmdNum,char* args[])
{
//	printf("CMD: %d\n",cmdNum);
//	printf("Executing update option.\n");
//	if(cmdNum>=2)
	{
//		if(0 == strcmp(args[1],"update"))
		{
			std::cout<<"Executing update option.\n";
			//freopen("pwdfile","w",stdout);
			system("pwd > pwdfile");
			//freopen("CON","w",stdout);
			FileExtra* f = new FileExtra("pwdfile");
			std::string new_cmd = f->getContext();
			system("rm pwdfile");
			//std::cout<<new_cmd<<std::endl;
			
			std::string pwdString = f->getContext();
			if(pwdString.back() == '\n')
			{
				pwdString[pwdString.length() - 1] = '/';	
			}
			new_cmd = "cat ";
			new_cmd += f->getContext();
			if(new_cmd.back() == '\n')
				new_cmd[new_cmd.length() - 1] = '/';
			new_cmd += ".git/config > confile";
			//std::cout<<new_cmd<<std::endl;
			system(new_cmd.c_str());
			
			if(f)
			{
				delete f;
				f = NULL;
			}
			FileExtra* f2 = new FileExtra("confile");
			system("rm confile");
			auto foo = [](const std::string& a,const std::string& b)->long{
				if(a.length() < b.length())
				{
					return -1;
				}

				for(long i = 0;i<( a.length() - b.length());i++)
				{
					bool flag = true;
					for(long j=0;j<b.length();j++)
					{
						if(a[i + j] != b[j])
						{
							flag = false;
							break;
						}
					}
					if(flag)
					{
						return i;
					}
				}
			};
			
			long find_url = foo(f2->getContext(),"url ");
			std::string urlsuf = f2->getContext().substr(find_url);
			//std::cout<<urlsuf<<std::endl;
			std::string final_cmd = "git pull ";
			for(find_url = 4;find_url < urlsuf.length() && (urlsuf[find_url] == ' ');find_url++);
//				printf("_%c_",urlsuf[find_url]);
			for(long i=find_url+1;i<urlsuf.length() && (urlsuf[i] != '\n');i++)
			{
				final_cmd += urlsuf[i];
//				printf("[%c]",urlsuf[i]);
			}

			if(f2)
			{
				delete f2;
				f2 = NULL;
			}
//			final_cmd += " ";
//			final_cmd += pwdString;
			system(final_cmd.c_str());
		}
	}
	return 0;	
}
