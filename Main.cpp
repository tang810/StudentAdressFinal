#include <iostream>

#include "Address.h"

using namespace std;

int main()
{
	Address Main;
	system("mode con cols=100 lines=50");
	while (1)
	{
		Main.ShowMenu();
		int Select = 0;
		cin >> Select;
		switch (Select)
		{
		case 0:
			Main.ExitSystem(); //退出程序
			break;
		case 1:
			Main.AddMember(); //增加新的联系人
			break;
		case 2:
			Main.DeleteMember(); //删除联系人
			break;
		case 3:
			Main.FindMember(); //查找联系人
			break;
		case 4:
			Main.ShowAllMember(); //查看所有联系人
			break;
		case 5:
			Main.Modify(); //修改已有联系人
			break;
		default:
			cout << "输入有误，请重新输入！" << endl;
			Main.Clear();
			break;
		}
	}
}