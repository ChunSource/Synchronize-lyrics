// LRC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "ProcessLRC.h"
int main()
{
	ProcessLRC lrc;
	lrc.LoadLRC(string("887902.lrc"));
	cout << "\n";
	cout << lrc.refreshLrc(150).data();
}

