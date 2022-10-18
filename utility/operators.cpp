// Copyright (c) 2015
// Author: Chrono Law
#include <utility>
#include <std.hpp>
using namespace std;

#include <boost/operators.hpp>
using namespace boost;

//////////////////////////////////////////
class demo_class
{
public:
    demo_class(int n) :x(n) {}
    int x;
    friend bool operator<(const demo_class& l, const demo_class& r)
    {
        return l.x < r.x;
    }
};

void case11()
{
    demo_class a(10), b(20);
    using namespace std::rel_ops;

    assert(a < b);
    assert(b >= a);


}

//////////////////////////////////////////

class point : //boost::less_than_comparable<point,
              //boost::equality_comparable<point> >
    totally_ordered<point,
    additive<point> >
{
    int x, y, z;
public:
    explicit point(int a = 0, int b = 0, int c = 0) :x(a), y(b), z(c) {}
    void print()const
    {
        cout << x << "," << y << "," << z << endl;
    }

    friend bool operator<(const point& l, const point& r)
    {
        return (l.x * l.x + l.y * l.y + l.z * l.z <
            r.x* r.x + r.y * r.y + r.z * r.z);
    }

    friend bool operator==(const point& l, const point& r)
    {
        return r.x == l.x && r.y == l.y && r.z == l.z;
    }

    point& operator+=(const point& r)       //֧��addable����
    {
        x += r.x;
        y += r.y;
        z += r.z;
        return *this;
    }

    point& operator-=(const point& r)   //֧��subtractable����
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;
        return *this;
    }

};

void case12()
{
    point p0, p1(1, 2, 3), p2(3, 0, 5), p3(3, 2, 1);

    assert(p0 < p1&& p1 < p2);
    assert(p2 > p0);
    assert(p1 <= p3);
    assert(!(p1 < p3) && !(p1 > p3));

    {
        point p0, p1(1, 2, 3), p2(p1), p3(3, 2, 1);
        assert(p1 == p2);
        assert(p1 != p3);
    }
}

//////////////////////////////////////////
#include <boost/assign.hpp>
void case13()
{
    point p0, p1(1, 2, 3), p2(5, 6, 7), p3(3, 2, 1);

    using namespace boost::assign;
    vector<point> v = (list_of(p0), p1, p2, p3);

    auto pos = std::find(v.begin(), v.end(), point(1, 2, 3));
    pos->print();

    (p1 + p2).print();
    (p3 - p1).print();

    assert((p2 - p2) == p0);

}

//////////////////////////////////////////
void case14()
{
    point p0, p1(1, 2, 3), p2(5, 6, 7), p3(3, 2, 1);

    using namespace boost::assign;
    vector<point> v = (list_of(p0), p1, p2, p3);

    auto pos = std::find(v.begin(), v.end(), point(1, 2, 3));
    for (; pos != v.end();
        pos = std::find(pos + 1, v.end(), point(1, 2, 3)))
    {
        pos->print();
    }

    pos = std::find(v.begin(), v.end(), point(2, 1, 3));
    assert(pos == v.end());

}

//////////////////////////////////////////
template<typename T>
class my_smart_ptr :
    public dereferenceable<my_smart_ptr<T>, T* >
{
    T* p;
public:
    my_smart_ptr(T* x) :p(x) {}
    ~my_smart_ptr() { delete p; }
    T& operator*() const
    {
        return *p;
    }
};

void case15()
{
    my_smart_ptr<string > p(new string("123"));
    assert(p->size() == 3);
}

//////////////////////////////////////////
template<typename T>
class my_smart_array :
    public indexable<my_smart_array<T>, int, T& >
{
    T* p;
public:
    typedef my_smart_array<T> this_type;
    typedef T* iter_type;

    my_smart_array(T* x) :p(x) {}
    ~my_smart_array() { delete[] p; }

    friend iter_type operator+(const this_type& a, int n)
    {
        return a.p + n;
    }
};

void case16()
{
    my_smart_array<double> ma(new double[10]);
    ma[0] = 1.0;
    *(ma + 1) = 2.0;
    cout << ma[1] << endl;

}

//////////////////////////////////////////
#include <boost/core/explicit_operator_bool.hpp>

struct demo_a
{
    BOOST_EXPLICIT_OPERATOR_BOOL()
        bool operator!() const
    {
        return false;
    }
    //explicit operator bool() const {
    //    return true;
    //}
};

struct demo_b
{
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
        bool operator!() const
    {
        return true;
    }
    //explicit operator bool() const {
    //    return false;
    //}
};

void case17()
{
    demo_a a;
    demo_b b;
    assert(a && !b);
    //assert(a != b);
    //assert(a > b);
}

//////////////////////////////////////////


int operators()
{
    case11();
    case12();
    case13();
    case14();
    case15();
    case16();
    case17();
    return 0;
}
