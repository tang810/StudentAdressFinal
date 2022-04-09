#include "Student.h"

ostream& operator<<(ostream& OutPut, Student& Stu)
{
	OutPut << "学号:"<<Stu.m_ID << "姓名:" << Stu.m_Name << " 性别:" << Stu.m_Gender << " 号码:" << Stu.m_PhoneNumber<<" 学院:"<<Stu.m_Academy<<" "<< endl;
	return OutPut;
}

Student::Student(string ID, string Name, string PhoneNumber, string Gender, string Academy)
{
	m_ID = move(ID);       //学号
	m_Name = move(Name);		//姓名
	m_PhoneNumber = move(PhoneNumber); //电话号码
	m_Gender = move(Gender);		//性别
	m_Academy = move(Academy);     //学院
}
Student::Student()
{

}
string Student::GetStudentName()// 获取学生姓名
{
	return this->m_Name;
}
string Student::GetStudentID()//获取学生学号
{
	return this->m_ID;
}
string Student::GetStudentPhoneNumber()// 获取学生号码
{
	return this->m_PhoneNumber;
}
string Student::GetStudentGender()//获取学生性别
{
	return this->m_Gender;
}
string Student::GetStudentAcademy()// 获取学生学院
{
	return this->m_Academy;
}
