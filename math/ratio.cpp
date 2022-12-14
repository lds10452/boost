// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

//#define BOOST_RATIO_EXTENSIONS
#include <boost/ratio.hpp>
using namespace boost;

//////////////////////////////////////////

void case21()
{
    typedef ratio<1, 2> half;

    assert(half::num == 1);
    assert(half::den == 2);

#if 0
    auto v = half::value();
    cout << v << endl;
    assert(v * 2 == 1);

    half frac;
    assert(frac().numerator() == frac.num);

    typedef ratio<2, 4> two_fourth;
    cout << two_fourth()() << endl;
    assert(half::value() == two_fourth::value());
#endif

    typedef ratio<12> dozen;
    assert(2 * dozen::num == 24);
}

//////////////////////////////////////////
typedef ratio<1, 2> half;
typedef ratio<1, 4> quater;

typedef ratio<12, 1> dozen;
typedef ratio<kilo::num * 10, 1> cn_wan;

typedef ratio<                           1024>     kibi;   //KB
typedef ratio<                      1024 * 1024>  mebi;   //MB
typedef ratio<                 1024 * 1024 * 1024>  gibi;   //GB


void case22()
{
    assert(kilo::num < kibi::num);
    cout << kilo::num << endl;
    cout << kibi::num << endl;

#if 0
    assert((quater())() * 2 == half()());
    assert((mega())() == cn_wan()() * 100);
#endif
    assert(mega::num == cn_wan::num * 100);
}

//////////////////////////////////////////
boost::intmax_t operator"" _kb(unsigned long long n)
{
    return n * kibi::num;
}

boost::intmax_t operator"" _gb(unsigned long long n)
{
    return n * gibi::num;
}

void case23()
{
    auto x = 2_gb;
    auto y = 10_kb;

    assert(x = 2 * 100 * y);
}

//////////////////////////////////////////
template<typename R>
using string_out = ratio_string<R, char>;

void case24()
{
    cout << string_out<kilo>::prefix() << endl;
    cout << string_out<kilo>::symbol() << endl;

    cout << string_out<nano>::prefix() << endl;
    cout << string_out<nano>::symbol() << endl;

    cout << string_out<ratio<22, 7>>::prefix() << endl;
}

//////////////////////////////////////////

int ratioTest()
{
    case21();
    case22();
    case23();
    case24();
    return 0;
}
