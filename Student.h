#ifndef STUDENT_H
#define STUDENT_H

#pragma once
#include <iostream>
#include <string>
#include<fstream>
using namespace std;
class Student {
public:
	friend ostream& operator<<(ostream& OutPut, Student& Stu);

	Student();

	Student(string ID,string Name,string PhoneNumber,string Gender,string Academy);

	string GetStudentName();

	string GetStudentID();

	string GetStudentPhoneNumber();

	string GetStudentGender();

	string GetStudentAcademy();
private:
	string m_ID;          //学号

	string m_Name;		//姓名

	string m_PhoneNumber; //电话号码

	string m_Gender;		//性别

	string m_Academy;     //学院
};




#endif