// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
#include <type_traits>
using namespace std;

//////////////////////////////////////////

#include <boost/integer_traits.hpp>
using namespace boost;

void case31()
{
    cout << integer_traits<int >::const_max << endl;
    cout << integer_traits<bool>::const_min << endl;
    cout << integer_traits<long>::is_signed << endl;
}

//////////////////////////////////////////

#include <boost/cstdint.hpp>
#include <limits>

void case32()
{
    uint8_t         u8;
    int_fast16_t    i16;
    int_least32_t   i32;
    uintmax_t       um;

    u8 = 255;
    i16 = 32000;
    i32 = i16;
    um = u8 + i16 + i32;

    assert(sizeof(u8) == 1);

    cout << "u8 :" << sizeof(u8)
        << " v = " << (short)u8 << endl;
    cout << "i16 :" << sizeof(i16)
        << " v = " << i16 << endl;
    cout << "i32 :" << sizeof(i32)
        << " v = " << i32 << endl;
    cout << "um :" << sizeof(um)
        << " v = " << um << endl;

    cout << (short)numeric_limits<int8_t>::max() << endl;
    cout << numeric_limits<uint_least16_t>::max() << endl;
    cout << numeric_limits<int_fast32_t>::max() << endl;
    cout << numeric_limits<intmax_t>::min() << endl;
}

//////////////////////////////////////////

#include <boost/integer.hpp>
#include <boost/type_index.hpp>

void case33()
{
    typedef int_fast_t<char>::fast cfast;
    cout << typeindex::type_id<cfast>().pretty_name() << endl;

    typedef int_fast_t<int>::fast ifast;
    cout << typeindex::type_id<ifast>().pretty_name() << endl;

    typedef int_fast_t<uint16_t>::fast u16fast;
    cout << typeindex::type_id<u16fast>().pretty_name() << endl;
}

//////////////////////////////////////////

#include <boost/format.hpp>

template<typename T>
string type_name()
{
    return typeindex::type_id<T>().pretty_name();
}

void case34()
{
    format fmt("type:%s,size=%dbit\n"); //һ��format����

    typedef uint_t<15>::fast u15;                 //������15λ���޷����������
    cout << fmt % type_name<u15>() % (sizeof(u15) * 8);

    typedef int_max_value_t<32700>::fast i32700;     //�ɴ���32700���������
    cout << fmt % type_name<i32700>() % (sizeof(i32700) * 8);

    typedef int_min_value_t<-33000>::fast i33000;        //�ɴ���-33000���������
    cout << fmt % type_name<i33000>() % (sizeof(33000) * 8);

    typedef uint_value_t<33000>::fast u33000;            //�ɴ���33000������޷�������
    cout << fmt % type_name<u33000>() % (sizeof(u33000) * 8);
}

int integerTest()
{
    case31();
    case32();
    case33();
    case34();
    return 0;
}

