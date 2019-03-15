#include<io.h>
#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
string self,name,ids;
int id;
void init_data()
{
	for(int i=self.size()-1;i>=0;i--)
		if(self[i]=='/'||self[i]=='\\'||i==0)
		{
			name=self.substr(i+1);
			name=name.substr(0,name.size()-4);
			ids=self.substr(0,i);
			break;
		}
	for(int i=ids.size()-1;i>=0;i--)
		if(ids[i]=='/'||ids[i]=='\\'||i==0)
		{
			ids=ids.substr(i+2);
			break;
		}
	for(int i=0;i<ids.size();i++)
		if(ids[i]=='.')
		{
			ids=ids.substr(0,i);
			break;
		}
	sscanf(ids.c_str(),"%d",&id);
}
void Add(vector<string> &lst,string na)
{
	long handle;
    struct _finddata_t fileinfo;
    handle=_findfirst(na.c_str(),&fileinfo);
    if(-1==handle) return;
	lst.push_back(fileinfo.name);
    while(!_findnext(handle,&fileinfo)) lst.push_back(fileinfo.name);
    _findclose(handle);
}
bool cmp(string a,string b)
{
	int na,nb;
	if(a.substr(0,name.size())==name)
	{
		a=a.substr(name.size());
		b=b.substr(name.size());
	}
	sscanf(a.substr(0,a.size()-name.size()-4).c_str(),"%d",&na);
	sscanf(b.substr(0,b.size()-name.size()-4).c_str(),"%d",&nb);
	return na<nb;
}
vector<string> GetFile()
{
	vector<string> res;
	Add(res,"..\\..\\data\\"+name+"\\*.out");
	Add(res,"..\\..\\data\\"+name+"\\*.ans");
	sort(res.begin(),res.end(),cmp);
	return res;
}
int file_size(char* filename)
{
    FILE *fp=fopen(filename,"r");
    if(!fp) return -1;
    fseek(fp,0,SEEK_END);
    int size=ftell(fp);
    fclose(fp);
    return size;
}
int main(int argc,char** argv)
{
	self=argv[0];
	init_data();
	vector<string> fs=GetFile();
	FILE *fin=fopen(("..\\..\\data\\"+name+"\\"+fs[id]).c_str(),"rb");
	FILE *fout=fopen((name+".out").c_str(),"wb");
	int len=file_size((char*)("..\\..\\data\\"+name+"\\"+fs[id]).c_str());
	char *p=new char[len+5];
	fread(p,len,1,fin);
	fwrite(p,len,1,fout);
	fclose(fin);
	fclose(fout);
	return 0;
}
