#include <std.hpp>
#include <regex>
#include <thread>
#include <fstream>
using namespace std;
#define PRINTEXP(e) cout<<e.what()<<"   "<<__FUNCTION__ << "   " <<__FILE__<< "   " << __LINE__<< endl;
typedef void (*ptr)();
ptr func;
class myException
{
public:
	virtual const char* why()const = 0;
	virtual int code()const = 0;
};
class childExp1 :public myException
{
	const char* why()const
	{
		return "�Զ����쳣��";
	}
	int code()const
	{
		return 111;
	}
};
class childExp2 :public runtime_error
{
public:
	childExp2(const string& s) :runtime_error(s) {};
};
void invalidArgument();
void regexError();//�����׳����쳣�������ͣ��Ա���������ʽ���еĴ���
void badTypeid();//�����͵��쳣��Ӧ�� typeid ���������̬���͵Ŀ�ָ��ֵʱ�׳���
void badCast();
void badAlloc();//����洢����ʧ�ܡ�
void badArrayNewLength();//��Ϊ�쳣�׳��Ա���Ƿ����鳤��
void customExp1();
void customExp2();
void otherError();
int customException()
{
	try
	{
		//func = invalidArgument;
		//func = regexError;
		//func= badTypeid;
		//func= badCast;
		//func = badAlloc;
		//func=badArrayNewLength;
		//func=customExp1;
		//func = customExp2;
		func = otherError;
		func();
	}
	catch (const std::exception&e)
	{
		PRINTEXP(e);
	}
	catch (const myException& e)
	{
		cout << e.why() << "  " << e.code() << endl;
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	catch (int e)
	{
		cout << e << endl;
	}
	catch (...)
	{
		cout << "other exception!!"<< endl;
	}
	cout << "success!!!" << endl;
	return 0;
}
void invalidArgument()
{
	throw invalid_argument("The input should be a number!");
	throw length_error("The input should be less than 100!");
	throw out_of_range("The input should be Non-negative number!");
}
void regexError()
{
	std::regex re("[a-b][a");//regex_error caught: The expression contained mismatched [ and ].
}
void badTypeid()
{
	class temp
	{
		virtual void f()=0;
	};
	temp* p = NULL;
	std::cout << typeid(*p).name() << '\n';//Attempted a typeid of NULL pointer!
}
void badCast()
{
	class child { public:virtual ~child() {} };
	class base { public:virtual ~base() {} };
	base b;
	child& a = dynamic_cast<child&>(b);//Bad dynamic cast
}
void badAlloc()
{
	while (true) {
		new int[9999999];//Allocation failed: std::bad_alloc
	}
}
void badArrayNewLength()
{
	int negative = -1;
	int small = 1;
	int large = INT_MAX;
	new int[negative];           // ����С�� bad_array_new_length
	new int[small] {1, 2, 3};       // �����ʼ������ bad_array_new_length
	new int[large][1000000];     // ���� bad_alloc �� bad_array_new_length
}
void customExp1()
{
	throw childExp1();
}
void customExp2()
{
	throw childExp2("�̳���runtime_error�쳣��");
}
void otherError()
{
	bool flag = 1;
	if (flag)
		throw "�׳��ַ���";
	else
		throw 88;
}