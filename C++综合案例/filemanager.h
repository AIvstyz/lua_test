#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
using namespace std;

class Mangerfile
{
public:
	void handleline_info(vector<string> & v, string & s);
	void readline(string path, map<string, map<string, string>> & m);
};