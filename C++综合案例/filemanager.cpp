#include "filemanager.h"
//#include <fstream>

void Mangerfile::handleline_info(vector<string> & v, string & sl)//从字符串中按逗号提取字符串
{
	int pos = -1;
	int start = 0;
	while (1)
	{
		string s = "";
		pos = sl.find(',', start);//从当前位置查找逗号
		if (pos == -1)
		{
			s = sl.substr(start, sl.size() - start);
			v.push_back(s);
			break;
		}
		s = sl.substr(start, pos - start);//拷贝的位置，拷贝的长度
		v.push_back(s);//将字符串复制到容器中
		start = pos + 1;//拷贝后记录当前逗号的下一个位置
	}
}
void Mangerfile::readline(const string path, map<string, map<string, string>> & m)
{
	ifstream ism;
	ism.open(path,ios::in);
	if (!ism.is_open())
		cout << path << "打开失败" << endl;
	//vector<string> v;
	string Dline = "";
	ism >> Dline;//从文件流中读取第一行字符串

	vector<string> title;
	handleline_info(title,Dline);
	string tmpline ="";
	while (ism >> tmpline)//从第二行开始读一行，读完循环自动终止
	{
		map<string, string> mtemp;
		vector<string> vtemp;//每一个英雄
		handleline_info(vtemp, tmpline);
		vector<string>::iterator vtit = vtemp.begin();
		for (vector<string>::iterator vit = title.begin(); vit != title.end()&&vtit!=vtemp.end(); vit++, vtit++)
		{
			mtemp.insert(make_pair(*vit, *vtit));
		}
		m.insert(make_pair(*(vtemp.begin()),mtemp));
	}
}

