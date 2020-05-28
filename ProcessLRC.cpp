#include "processlrc.h"
#include <string.h>
#include <windows.h>
ProcessLRC::ProcessLRC()
{
    
}


ProcessLRC::~ProcessLRC()
{
}

vector<string> ProcessLRC::LoadLRC(string fileName)
{
	//每次载入之前先把上次的数据清空
	currentLrcFileName = fileName;
	ListLrcBody.clear();
	MapTime.clear();
	lrcPosIndex = 0;
	lrcLastPosIndex = 0;
	lrcLastMediaPos = 0;

	ifstream file;
	file.open(fileName, ios::in);
	if (!file)
	{
        int nmum = GetLastError();
        char *str = strerror(errno);
		return vector<string>();
	}

	//读取文件大小，申请相当内存
	int fileSize = GetFileSize(fileName);
	char *buffer = new char[fileSize];

	file.read(buffer, fileSize);
	string lrc(buffer, fileSize);//将数据转存到string

	delete buffer;
	buffer = nullptr;

	vector<string> vlist;
	lrc = replace_all_distinct(lrc, "\r", "");
	lrc = replace_all_distinct(lrc, "?", "");
	//lrc.replace();  //将每行的歌词读取
	vector<string> list = split(lrc, "\n");

	for (int i = 0; i < list.size(); i++)
	{
		//处理每一行的数据
		string str = list.at(i);
		//	showLog( str);
		string app = str.substr(str.find("]") + 1, str.length() - str.find("]") - 1);
		//	showLog("geci  " + app);
		ListLrcBody.push_back(app);

		string tp = str.substr(1, str.find("]") - 1);//读取时间部分
		tp = replace_all_distinct(tp, "[", "");

		int sec = convert_str_to_tm(tp.data());  //转换成秒数
		int min = sec / 60;

		map<int, map<int, string>>::iterator it = MapTime.find(min);


		if (it != MapTime.end())
		{
			//表示之前已经有了
			map<int, string> &sMap = it->second;
			sMap.insert(pair<int, string>(sec, app));
		}
		else
		{  //之前没有创建过
			map<int, string> sMap;
			sMap.insert(pair<int, string>(sec, app));
			MapTime.insert(map<int, map<int, string>>::value_type(min, sMap));
		}



		showLog(tp);
		showLog(sec);
	}

	return ListLrcBody;
}

string ProcessLRC::refreshLrc(int pos, int flage)
{

	int index = 0;
	int sindex = 0;
	if (MapTime.size()< 0 || flage == 2)
	{
		return string();
	}
	int sec = pos / 60;
	map<int, map<int, string>>::iterator it = MapTime.find(sec); //先按秒索引，再按毫秒比较

	while (it != MapTime.end())
	{
		map<int, string> &sMap = it->second;
		map<int, string>::iterator sit = sMap.begin();
		while (sit != sMap.end())
		{
			if (sit->first < pos)
			{
				map<int, string>::iterator asit = sit;
				asit++;
				if (asit == sMap.end())
				{
					//当前项是最后一个，是最合适的了

					return sit->second;
				}
				else if (pos < asit->first)
				{
					//当前项不是最后一个，但是是最合适的
					return sit->second;
				}
			}
			else if (sit == sMap.begin())
			{

				//后面的更加不合适
				return sit->second;
			}

			sit++;
		}

		it++;
	}

	return refreshLrc(pos + 1, flage + 1);

	return string();
}

void ProcessLRC::showLog(string log)
{
	cout << (string("\n") + log).data();
}

void ProcessLRC::showLog(int log)
{
	cout << "\n";
	cout << log;
}

size_t ProcessLRC::GetFileSize(const std::string & file_name)
{
	std::ifstream in(file_name.c_str());
	in.seekg(0, std::ios::end);
	size_t size = in.tellg();
	in.close();
	return size; //单位是：byte
}

vector<string> ProcessLRC::split(const std::string& input, const std::string key)
{
	std::regex re(key);

	std::sregex_token_iterator p(input.begin(), input.end(), re, -1);
	std::sregex_token_iterator end;
	vector<string> vec;
	while (p != end)
		vec.emplace_back(*p++);

	return vec;
}

string&   ProcessLRC::replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}

int ProcessLRC::convert_str_to_tm(const char * str_time)
{
	string min(str_time, 2);
	string sec(str_time + 3, 2);
	int s = 0;

	s += atoi(min.data()) * 60;
	s += atoi(sec.data());
	return s;//28800是一个偏差。。加上这个。。刚好等于PHP的strtotime
}
