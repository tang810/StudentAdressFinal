#ifndef ADDRESS_H
#define ADDRESS_H
#pragma warning (disable:4996)
#pragma once
#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include<Windows.h>
#include<conio.h>
#include "Student.h"


using namespace std;

#define FILENAME "NameList.csv" //保存通讯录名单在名为 NameList 的文件中
#define Width 100
#define Length 50
#define BeginRow 0

class Address
{
public:
	Address();						 //构造函数

	void ShowMenu();				 //显示菜单

	void ExitSystem();				 //退出系统

	void AddMember();				 //添加联系人

	void AppSave(Student NewMember); //保存新增联系人

	void AllSave();					 //覆盖保存所有联系人

	void LoadMember();				 //读入所有联系人

	void ShowAllMember();			 //查看所有联系人

	void FindMember();				 //查找联系人

	void DeleteMember();			 //删除联系人

	void Modify();					 //修改联系人信息

	~Address();						 //析构函数
	void Go(short x, short y);       //控制光标移动

	void Clear();					 //清屏操作

	void Endl();                     //换行

	HANDLE HOut;                     //句柄
	COORD  Pos;                      //光标坐标
	int    ROW;
	int    ClearRow;                 //开始清屏的行数
private:
	map<string, Student> MyListID; //按学号排序存储联系人

	multimap<string, Student> MyListName; //按姓名排序存储联系人
};

#endif