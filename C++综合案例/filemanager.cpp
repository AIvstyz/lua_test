#include "filemanager.h"
//#include <fstream>

void Mangerfile::handleline_info(vector<string> & v, string & sl)//���ַ����а�������ȡ�ַ���
{
	int pos = -1;
	int start = 0;
	while (1)
	{
		string s = "";
		pos = sl.find(',', start);//�ӵ�ǰλ�ò��Ҷ���
		if (pos == -1)
		{
			s = sl.substr(start, sl.size() - start);
			v.push_back(s);
			break;
		}
		s = sl.substr(start, pos - start);//������λ�ã������ĳ���
		v.push_back(s);//���ַ������Ƶ�������
		start = pos + 1;//�������¼��ǰ���ŵ���һ��λ��
	}
}
void Mangerfile::readline(const string path, map<string, map<string, string>> & m)
{
	ifstream ism;
	ism.open(path,ios::in);
	if (!ism.is_open())
		cout << path << "��ʧ��" << endl;
	//vector<string> v;
	string Dline = "";
	ism >> Dline;//���ļ����ж�ȡ��һ���ַ���

	vector<string> title;
	handleline_info(title,Dline);
	string tmpline ="";
	while (ism >> tmpline)//�ӵڶ��п�ʼ��һ�У�����ѭ���Զ���ֹ
	{
		map<string, string> mtemp;
		vector<string> vtemp;//ÿһ��Ӣ��
		handleline_info(vtemp, tmpline);
		vector<string>::iterator vtit = vtemp.begin();
		for (vector<string>::iterator vit = title.begin(); vit != title.end()&&vtit!=vtemp.end(); vit++, vtit++)
		{
			mtemp.insert(make_pair(*vit, *vtit));
		}
		m.insert(make_pair(*(vtemp.begin()),mtemp));
	}
}

