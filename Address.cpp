#include"Address.h"

void Address::Go(short x, short y)//控制光标位置
{
	this->HOut = GetStdHandle(STD_OUTPUT_HANDLE);
	this->Pos = { x,y };
	SetConsoleCursorPosition(this->HOut, this->Pos);
}
void Address::ShowMenu() //显示菜单
{
	Go(Width / Widthdivisor+Add-5, ROW );
	cout << "----------学生通讯录---------" << endl;
	this->Endl();
	cout << "0、退出通讯录系统" << endl;
	this->Endl();
	cout << "1、添加联系人" << endl;
	this->Endl();
	cout << "2、删除联系人" << endl;
	this->Endl();
	cout << "3、查找联系人" << endl;
	this->Endl();
	cout << "4、查看所有联系人" << endl;
	this->Endl();
	cout << "5、修改已有联系人信息" << endl;
	this->Endl();
	cout << "请按下数字键进行操作" << endl;
	this->Endl();
	int col1 = Width / Widthdivisor + Add - 5, col2 = Width /  Widthdivisor + Add + 23;
	for (int row = 1; row < ROW; row++)
	{
		Go(col1, row);
		cout << "|";
		Go(col2, row);
		cout << "|";
	}
	Go(col1, ROW - 1);
	for (int i = col1; i <= col2; i++)
		cout << "-";
	this->Endl();
	this->ClearRow = ROW;
}
Address::Address()					 //构造函数
{
	this->MyListName.clear(); //清空容器
	this->MyListID.clear(); //清空容器
	this->LoadMember();//加载名单
	ROW = BeginRow;            //从ROW行开始输出
}
void Address::ExitSystem()			 //退出系统
{
	cout << "欢迎下次使用！" << endl;
	exit(0);
}
void Address::AddMember() 				 //添加联系人
{
	
	string ID, Name, PN, Gender, Academy;
	this->Endl();
	cout << "正在添加联系人..." << endl;
	this->Endl();
	cout << "请输入新建联系人的学号" << endl;
	this->Endl();
	cin.ignore();
	getline(cin, ID);
	this->Endl();
	cout << "请输入新建联系人的姓名" << endl;
	this->Endl();
	getline(cin, Name);
	this->Endl();
	cout << "请输入新建联系人的电话号码" << endl;
	this->Endl();
	getline(cin, PN);
	this->Endl();
	cout << "请输入新建联系人的性别" << endl;
	this->Endl();
	getline(cin, Gender);
	this->Endl();
	cout << "请输入新建联系人的学院" << endl;
	this->Endl();
	getline(cin, Academy);
	Student NewMember(ID, Name, PN, Gender, Academy);
	this->MyListName.insert(make_pair(Name,NewMember));
	this->MyListID[ID] = NewMember;
	this->AppSave(NewMember);
	this->Endl();
	cout << "新建联系人成功！" << endl;
	this->Clear();
	
}
void Address::AppSave(Student NewMember)  //保存新增联系人
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app); //以追加方式写文件
	ofs << NewMember.GetStudentID() << "," << NewMember.GetStudentName() << ","
		<< NewMember.GetStudentPhoneNumber() << "," << NewMember.GetStudentGender() << ","
		<< NewMember.GetStudentAcademy() << "," << endl;
	ofs.close();
	this->Endl();
	cout << "添加联系人成功！" << endl;
	this->Clear();
}
void Address::AllSave() 					 //覆盖保存所有联系人
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (auto It = this->MyListID.begin(); It != MyListID.end(); It++)
	{
		Student NewMember = It->second;
		ofs  << NewMember.GetStudentID() << "," << NewMember.GetStudentName() << ","
			<< NewMember.GetStudentPhoneNumber() << "," << NewMember.GetStudentGender() << ","
			<< NewMember.GetStudentAcademy() << "," << endl;
	}
	ofs.close();
}
void Address::LoadMember() 				 //读入所有联系人
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//文件不存在情况
	if (!ifs.is_open())
	{
	
		ifs.close();
		return;
	}
	//文件被清空情况
	char Check; //查看是否为空文件夹
	ifs >> Check;
	if (ifs.eof())
	{
		
		return;
	}
	//文件不为空
	ifs.putback(Check);
	string Information;
	while (getline(ifs, Information)) //姓名可带空格的输入
	{
		
		int Start = 0;
		int Pos = -1;
		int index = 0;
		string Data[5];
		while (1)
		{
			
			Pos = Information.find(',', Start);
			if (Pos == -1)
			{
				break;
			}
			Data[index++] = Information.substr(Start, Pos - Start);
			Start = Pos + 1;
		}
		
		Student Temp(Data[0], Data[1], Data[2], Data[3], Data[4]);
		this->MyListName.insert(make_pair(Temp.GetStudentName(),Temp) ); //将成员放入名单容器中
		this->MyListID.insert(make_pair(Temp.GetStudentID(),Temp) ); //将成员放入学号容器中
	}
}
void Address::ShowAllMember() 			 //查看所有联系人
{
	if (this->MyListID.empty())
	{
		this->Endl();
		cout << "当前联系人为空！" << endl;
		this->Clear();
		return;
	}
	/*Go(Width / 3 + Add, ROW += 2);*/
	this->Endl();
	cout << "所有联系人信息如下：" << endl;
	for (auto It = this->MyListID.begin(); It != this->MyListID.end(); It++)
	{
		Go(Width / 6 , ROW += 2);
		cout << It->second;
	}
	this->Clear();
}
void Address::FindMember() 				 //查找联系人
{
	this->Endl();
	cout << "正在查找联系人..." << endl;
	if (this->MyListID.empty())
	{
		Go(Width / 3 + Add, ROW += 2);
		cout << "当前联系人为空！" << endl;
		this->Clear();
		return;
	}
	this->Endl();
	cout << "按一下哪种方式查找：" << endl;
	this->Endl();
	cout << "1、学号" << endl;
	this->Endl();
	cout << "2、姓名" << endl;
	int Select = 0;
	this->Endl();
	cin >> Select;
	switch (Select)
	{
	case 1:
	{
		string TmpID;
		this->Endl();
		cout << "请输入学号：" << endl;
		this->Endl();
		cin >> TmpID;
		auto It = this->MyListID.find(TmpID);
		if (It == MyListID.end())
		{
			this->Endl();
			cout << "查无此联系人！" << endl;
			this->Clear();
		}
		else
		{
			this->Endl();
			cout << "查询结果如下：" << endl;
			Go(Width / 6 + Add, ROW += 2);
			cout << It->second;
			this->Clear();
		}
	}
		break; 
	case 2:
	{
		string TmpName;
		this->Endl();
		cout << "请输入姓名：" << endl;
		cin >> TmpName;
		int Cnt = this->MyListName.count(TmpName);
		auto It = this->MyListName.find(TmpName);
		if (It == MyListName.end())
		{
			this->Endl();
			cout << "查无此联系人！" << endl;
			this->Clear();
		}
		else
		{
			this->Endl();
			cout << "查询结果如下：" << endl;
			for (int i = 0; i < Cnt; i++)
			{
				Go(Width / 6 + Add, ROW += 2);
				cout << It->second;
				It++;
			}
			this->Clear();
		}
	}
			break;
	default:
		this->Endl();
		cout << "输入有误！" << endl;
		this->Clear();
	}
}
void Address::DeleteMember() 			 //删除联系人
{
	this->Endl();
	cout << "正在删除联系人..." << endl;
	if (this->MyListID.empty())
	{
		this->Endl();
		cout << "当前联系人为空！" << endl;
		this->Clear();
		return;
	}
	string TmpID;
	this->Endl();
	cout << "请输入学号：" << endl;
	this->Endl();
	cin >> TmpID;
	auto It = this->MyListID.find(TmpID);
	if (It == MyListID.end())
	{
			this->Endl();
			cout << "查无此联系人！" << endl;
			this->Clear();
	}
	else
	{
		this->Endl();
		cout << "查询结果如下：" << endl;
		this->Endl();
		cout << It->second;
		this->Endl();
		cout << "是否对其进行删除？" << endl;
		this->Endl();
		cout << "1、确定" << endl;
		this->Endl();
		cout << "2、取消" << endl;
		int Choice = 0;
		if (Choice == 1)
		{
			int Cnt = this->MyListName.count(It->second.GetStudentName());
			auto Iterator = this->MyListName.find(It->second.GetStudentName());
			for (int i = 0; i < Cnt; i++)
			{
				if (Iterator->second.GetStudentID() != TmpID)
					Iterator++;
			}
			this->MyListName.erase(Iterator);
			this->MyListID.erase(TmpID);
			this->Endl();
			cout << "删除成功！" << endl;
			this->AllSave();
			this->Clear();
		}
		else
			return;
	}
}
void Address::Modify() 					 //修改联系人信息
{
	this->Endl();
	cout << "正在修改联系人..." << endl;
	if (this->MyListID.empty())
	{
		this->Endl();
		cout << "当前联系人为空！" << endl;
		this->Clear();
		return;
	}
	this->Endl();
	cout << "请输入要修改的联系人的学号：" << endl;
	this->Endl();
	string TmpID;
	cin >> TmpID;
	auto It = this->MyListID.find(TmpID);
	if (It == this->MyListID.end())
	{
		this->Endl();
		cout << "查无此人！" << endl;
		this->Clear();
		return;
	}
	int Cnt = this->MyListName.count(It->second.GetStudentName());
	auto Iterator = this->MyListName.find(It->second.GetStudentName());
	for (int i = 0; i < Cnt; i++)
	{
		if (Iterator->second.GetStudentID() != TmpID)
			Iterator++;
	}
	this->MyListID.erase(It);
	this->MyListName.erase(Iterator);
	string ID, Name, PN, Gender, Academy;
	this->Endl();
	cout << "请输入联系人的学号" << endl;
	this->Endl();
	cin.ignore();
	getline(cin, ID);
	this->Endl();
	cout << "请输入联系人的姓名" << endl;
	this->Endl();
	getline(cin, Name);
	this->Endl();
	cout << "请输入联系人的电话号码" << endl;
	this->Endl();
	getline(cin, PN);
	cout << "请输入联系人的性别" << endl;
	this->Endl();
	getline(cin, Gender);
	this->Endl();
	cout << "请输入联系人的学院" << endl;
	this->Endl();
	getline(cin, Academy);
	Student NewMember(ID, Name, PN, Gender, Academy);
	this->MyListName.insert(make_pair(Name, NewMember));
	this->MyListID[ID] = NewMember;
	this->Endl();
	cout << "修改成功！" << endl;
	this->AllSave();
	this->Clear();
}
Address::~Address() 						 //析构函数
{

}
void Address::Clear()//清屏
{
	char ch = getch();
	for(int i=ClearRow;i<=this->ROW;i++)
		for (int j = 0; j < Width; j++)
		{
			Go(j, i);
			cout << " ";
		}
	this->ROW = BeginRow;
}
void Address::Endl()//换行
{
	Go(Width / Widthdivisor + Add, this->ROW += DistanceRow);
}