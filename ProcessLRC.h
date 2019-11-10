#pragma once
#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include <string>
#include <regex>
#include<algorithm>
#include <time.h>

using namespace std;

class ProcessLRC
{
public:
	ProcessLRC();
	~ProcessLRC();

	vector<string> LoadLRC(string fileName);  //load change lrc File
	string refreshLrc(int pos, int flage = 0);

	void showLog(string log);
	void showLog(int log);
private:
	string       currentLrcFileName;  //��¼����ļ�
	vector<string>   ListLrcBody;  //��¼ÿ�еĸ��
	map<int, map<int, string>>  MapTime;   //��¼ÿ�е�ʱ��
	int		lrcPosIndex = 0;
	int       lrcLastPosIndex = 0;
	int		lrcLastMediaPos = 0;


	//function:

	size_t GetFileSize(const std::string& file_name);
	vector<string> split(const std::string& input, const std::string key);
	string&   replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value);
	int convert_str_to_tm(const char * str_time);
};

