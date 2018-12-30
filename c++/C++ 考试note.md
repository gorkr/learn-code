# C++ 考试note

## chapter 1

- 什么是消息？消息具有什么性质？
  
  一个对象向另一个对象发出的请求被称作消息。当对象接受发向它的消息时，就调用有关方法，执行相应操作。

  1. 一个对象可以接受不同形式的多个消息，做出不同的响应。
  2. 相同形式的消息可以传递给不同对象，所作出的响应也可以是不同的。
  3. 对消息的响应不是必须的。

## chapter 2 Overview

- 函数没有指明返回值类型时，默认为`int`
- `int * p = new int[40](0);` **错误**。
- 顶层 代表指针是一个常量， 底层 代表指向对象是一个常量。 char * const p; 属于顶层。 
- 内联函数体内一般**不能**包含复杂的控制语句，如`for`,`switch`。
- `new`创建对象是调用构造函数， `delete`删除对象是调用析构函数。

```C++
//this is a strange /* way */
//返回值类型是引用， 这个引用是全局变量， 再将返回值作为右值时， 其实这个右值是这个全局变量。
//并不是将引用赋值给了引用
#include<iostream>
using namespace std;
int &f(int &i){
  i+=10;
  return i;
}
int main(){
  int k = 0;
  int &m=f(k);//相当于 int &m = i;
  cout<<k<<endl;
  m=20;
  cout<<k<<endl;
  return 0;
}
```

## chapter 3 Class and Object

- 常对象只能调用常成员函数
- 注意调用函数时，参数对象的构造和析构
- 静态成员函数中不能使用`this`指针
- 静态成员函数一般只用于访问静态数据成员，此时不带参数； 也可以访问非数据成员，此时要又对象的引用作为参数。

## chapter 4 派生类和继承

- 派生类中调用构造函数时：

  ```c++
  class C:public B, public A{
      C()：A(),B(){    
      }
  }
  ```
  **根据`class`行的生命顺序**调用构造函数， 先调用`B()`，再调用`A()`。
  
- 派生类对象可以转换为基类对象使用。

## chapter 5 多态性

- 使用对象名和点调用虚函数时，是静态联编，它没有利用到虚函数的额特性。
- 静态联编支持的多态性称为编译时多态。通过函数重载和模板实现。
- 动态联编通过虚函数实现



# 源代码

## 异常处理

```C++
#include<iostream>
#include<cmath>  //包含sqrt(com)
using namespace std;
int Div(int y)
{
	if (y<0)
		throw y;
	return sqrt(y);
}
int main()
{
	try
	{
		cout << Div(9) << endl;
		cout << Div(-1) << endl;
	}
	catch (int)
	{
		cout << "被开方数为负数！！！" << endl;
	}
	cout << "end";
	return 0;
}

```



## 文件

```C++
#include<iostream> 
#include<fstream> 
using namespace std;
int main()
{
	char ch;
    
	ifstream file1;
	ifstream file2;
	ofstream file3;
    
	ofstream fout1("a.txt", ios::out);
	if (!fout1)
	{
		cout << "Cannot open output file" << endl;
		return 1;
	}
	fout1 << 99 << " " << 2017.6 << "  " << "This is a text file" << endl;
	fout1.close();
	ofstream fout2("b.txt", ios::out);
	if (!fout2)
	{
		cout << "Cannot open output file" << endl;
        return 1;
	}
	fout2 <<"hfhggg" << endl;
	fout2.close();


	
	file1.open("a.txt", ios::in);
	file2.open("b.txt", ios::in);
	file3.open("c.txt", ios::out);

	if (!file1|| !file2)
	{
		cout << " cannot open" << endl;
		abort();
	}

    //------------------------------------------------------
    //将指针指向开头
    file1.seekg(0);
	file2.seekg(0);
    //------------------------------------------------------

	while (!file1.eof())
	{
		file1.get(ch);
		if (ch <= 122 && ch >= 97)
			ch = ch - 32;
		file3.put(ch);
		cout << ch;
	}
	while (!file2.eof())
	{
		file2.get(ch);
		if (ch <= 122 && ch >= 97)
			ch = ch - 32;
		file3.put(ch);
		cout << ch;
	}
    file1.close();
	file2.close();
	file3.close();
	return 0;
}



```

## 多重继承

```C++
#include<iostream>
#include<string>
using namespace std;
class Time
{
public:
	Time(int h, int m, int s)
	{
		hours = h;
		minutes = m;
		seconds = s;
	}
	void display()
	{
		cout << "出生时间：" << hours << "时" << minutes <<"分" << seconds << "秒" << endl;
	}
protected:
    int hours, minutes, seconds;
};
class Date
{
public:
	Date(int m, int d, int y)
	{
		month = m;
		day = d;
		year = y;
	}
	void display()
	{
		cout << "出生年月：" << year << "年" << month << "月" << day << "日" << endl;
	}
protected:
	int month, day, year;
};
class Birthtime :public Time, public Date
{
	char *Childname;
	public:
	Birthtime(char *name, int m, int d, int y, int hh, int mm, int ss);
	void display();
};
Birthtime::Birthtime(char *name, int m, int d, int y, int hh, int mm, int ss) :Date(m, d, y), Time(hh, mm, ss)
{
    //------------------------------------------------------------------------------------------------------------------
    //初始化字符串
	Childname = new char[strlen(name) + 1];
	strcpy(Childname, name);
    //------------------------------------------------------------------------------------------------------------------
}
void Birthtime::display()
{
	cout << "姓名  \t:" << Childname << endl;

}
int main()
{
	Birthtime  a("Han", 9, 26, 1997, 5, 2, 1);
	Birthtime  b("WU", 7, 21, 1984, 6, 26, 36);
	a.display();
    
    //------------------------------------------------------
    //调用不同类中的同名函数
	a.Date::display();
    a.Time::display();
    //------------------------------------------------------
	b.display();
	b.Date::display();
	b.Time::display();
	return 0;
}
```

## 类与对象

```C++
#include<iostream>
using namespace std;
class Time
{
	int hour, minute, second;
public:
	Time();
	Time(int h, int m, int s);
	Time(const Time &);
	void Time_add(Time &);
	void Time_sub(Time &);
	friend Time operator+(Time &, Time &);
	friend Time operator-(Time &, Time &);
	void display();
};
Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}
Time::Time(int h, int m, int s)
{
	hour = h;
	minute = m;
	second = s;
}
Time::Time(const  Time &t)
{
	hour = t.hour;
	minute = t.minute;
	second = t.second;
}
void Time::Time_add(Time &a)
{
	hour = hour + a.hour;
	minute = minute + a.minute;
	second = second + a.second;
}
void Time::Time_sub(Time &a)
{
	hour = hour -a.hour;
	minute = minute - a.minute;
	second = second - a.second;
}
Time operator +(Time & a,Time &b)
{
	Time temp;
	temp.hour = a.hour + b.hour;
	temp.minute = a.minute +b.minute;
	temp.second = a.second + b.second;
	return temp;
}
Time operator -(Time & a, Time &b)
{
	Time temp;
	temp.hour = a.hour - b.hour;
	temp.minute = a.minute -b.minute;
	temp.second = a.second - b.second;
	return temp;
}
void Time::display()
{
	cout << "The time is " << hour << "h" << minute << "m" << second << "s" << endl;
}
int main()
{
	Time a;
	Time b(5, 6, 7);
	Time c(b);
	a.display();
	b.display();
	c.display();
	a.Time_add(b);
	a.display();
	a.Time_sub(c);
	a.display();
	a = a + b;
	a.display();
	a = b + c;
	a.display();
	return 0;
}

```

## 静态成员函数

```c++
#include<iostream>
using namespace std;
class Student
{
	double score;
public:
	static double total_score;
	static int count;
	void account(double s);
	double sum();
	double average();
};
void Student::account(double s)
{
	score = s;
	count++;
	total_score += score;
}
double Student::sum()
{
	return total_score;
}
double Student::average()
{
	return total_score / count;
}
double Student::total_score = 0.0;
int Student::count = 0;
int main()
{
	Student a, b, c, d, e;
	a.account(100.0);
	b.account(90.0);
	c.account(80.0);
	d.account(70.0);
	e.account(60.0);
	cout << "该班的总成绩：" << a.sum() << endl;
	cout << "该班的平均成绩： " << a.average() << endl;
	return 0;
}
```

## 派生类

```C++
#include<iostream>
#include<string>
using namespace std;
class person
{
	char *id, *name;
	char * gender;
	int age;
public:
	person(char *ids, char *names, char *genders, int ages)
	{
		id = new char[strlen(ids) + 1];
		strcpy(id, ids);
		name = new char[strlen(names) + 1];
		strcpy(name, names);
		gender = new char[strlen(genders) + 1];
		strcpy(gender, genders);
		age = ages;
	}
	void show()
	{
		cout << "  编号： \t" << id << endl;
		cout << "  姓名 ：\t" << name << endl;
		cout << "  性别：\t" << gender << endl;
		cout<<"  年龄：\t" << age << endl;
	}
};
class Student :public person
{
	char *department;
	double score;
public:
	Student(char *ids, char *names, char *genders, int ages, char *departments, double scores) :person(ids, names, genders, ages)
	{
		department = new char[strlen(departments) + 1];
		strcpy(department, departments);
		score = scores;
	}
	void show1()
	{
		cout << "  系别: \t" << department << endl;
		cout<<"  分数：\t" << score << endl;
	}
};
class Teacher :public person
{
	char *title;
	char *department;
public:
	Teacher(char *ids, char *names, char *genders, int ages, char *titles, char *departments) :person(ids, names, genders, ages)
	{
		title = new char[strlen(titles) + 1];
		strcpy(title, titles);
		department = new char[strlen(departments) + 1];
		strcpy(department, departments);
	}
	void show2()
	{
		cout << "  职称 :\t" << title << endl;
		cout<<"  部门 :\t" << department << endl;
	}
};
int main()
{
	Student stu("000", "jjj", "男", 19, "计算机科学与软件学院", 99);
	stu.show();
	stu.show1();
	Teacher  tea("  000", "uuu", "男", 28, "fff", "计算机科学与软件学院");
	tea.show();
	tea.show2();
	return 0;
}
```

