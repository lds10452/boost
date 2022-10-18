// Copyright (c) 2015
// Author: Chrono Law
#include <bitset>
#include <std.hpp>
using namespace std;

#include <boost/utility.hpp>

//////////////////////////////////////////
void case41()
{
    cout << hex << showbase;
    cout << BOOST_BINARY(0110) << endl;
    cout << BOOST_BINARY(0110 1101) << endl;
    cout << BOOST_BINARY(10110110 01) << endl;
    cout << bitset<5>(BOOST_BINARY(0110)) << endl;

    cout << BOOST_BINARY_UL(101 1001) << endl;
    long long x = BOOST_BINARY_LL(1101);
    cout << x << endl;

}

//////////////////////////////////////////
#include <boost/current_function.hpp>

double func()
{
    cout << BOOST_CURRENT_FUNCTION << endl;
    return 0.0;
}

//string str = BOOST_CURRENT_FUNCTION;      //�����÷����������ں�����������

void case42()
{
    //cout << str << endl;
    cout << __FUNCTION__ << endl;
    cout << BOOST_CURRENT_FUNCTION << endl;
    func();
}



//////////////////////////////////////////

int utilityTest()
{
    case41();
    case42();
    return 0;
}
