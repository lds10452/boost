// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
#include <stack>
//using namespace std;
using std::vector;
using std::stack;
using std::cout;
using std::endl;

//#define BOOST_THREAD_PROVIDES_VARIADIC_THREAD
//#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_VERSION 4
#include <boost/bind.hpp>
#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
using namespace boost;

//////////////////////////////////////////

#include <boost/chrono.hpp>
using namespace boost::chrono;
extern boost::chrono::seconds operator"" _s(unsigned long long n);

extern boost::chrono::milliseconds operator"" _ms(unsigned long long n);
//////////////////////////////////////////
class buffer
{
    private:
        mutex mu;
        condition_variable_any cond_put;
        condition_variable_any cond_get;

        stack<int> stk;
        int un_read,capacity;

        bool is_full()
        {   return un_read == capacity; }

        bool is_empty()
        {   return un_read == 0 ;   }
    public:
        buffer(size_t n):un_read(0),capacity(n){}

        void put(int x)
        {
            {
                auto lock = make_unique_lock(mu);
                cond_put.wait(lock,
                    [this]{return un_read < capacity;});
                //for(;is_full();)
                //{
                //    cout << "full waiting... "  << endl;
                //    cond_put.wait(lock);
                //}
                stk.push(x);
                ++un_read;
            }
            cond_get.notify_one();
        }

        void get(int *x)
        {
            {
                auto lock = make_unique_lock(mu);
                cond_get.wait(lock,
                    [this]{return un_read > 0;});
                //for(;is_empty();)
                //{
                //    cout << "empty waiting... " << endl;
                //    cond_get.wait(lock);
                //}
                --un_read;
                *x = stk.top();
                stk.pop();
            }
            cond_put.notify_one();
        }
};

buffer buf(5);

void producer(int n)
{
    for (int i = 0;i < n; ++i)
    {
        cout << "put " << i << endl;
        buf.put(i);
    }
}

void consumer( int n)
{
    int x;
    for (int i = 0;i < n; ++i)
    {
        buf.get(&x);
        cout << "get " << x << endl;
    }
}


void case41()
{
    thread_group tg;

    tg.create_thread(bind(producer, 20));
    tg.create_thread(bind(consumer, 10));
    tg.create_thread(bind(consumer, 10));

    tg.join_all();
}

//////////////////////////////////////////
//#include <future>
extern void dummy(int n);
void case42()
{
    //auto x = async(&dummy, 10);
    //x.wait();

    boost::async(bind(dummy, 10));

    auto f = boost::async([]{cout << "hello" << endl;});
    f.wait();

    async(launch::async, dummy, 100);
}

//////////////////////////////////////////
extern int fab(int n);

void case43()
{
    auto f5 = async(fab, 5);
    auto f7 = async(launch::async, fab, 7);

    cout << f5.get() + f7.get() << endl;
    assert(!f5.valid() && !f7.valid());

    auto f10 = async(fab, 10);
    auto s = f10.wait_for(100_ms);

    if(f10.valid())
    {
        assert(s == future_status::ready);
        cout << f10.get() << endl;
    }

    vector<boost::future<int>> vec;
    for(int i = 0;i < 5; ++i)
    {
        vec.push_back(async(fab, i + 10));
    }

    wait_for_any(vec[3], vec[4], vec[2]);
    for(auto& x : vec)
    {
        if(x.valid())
        {   cout << x.get() << endl;        }
    }

    //wait_for_all(vec.begin(), vec.end());

    //for(auto& x : vec)
    //{
    //    cout << x.get() << ',';
    //}
    cout << endl;
}

//////////////////////////////////////////
void case44()
{
    //shared_future<int> f5 = async(fab, 5);
    auto f5 = async(fab, 5).share();
    //cout << f5.get() << endl;

    auto func = [](decltype(f5) f){
        cout << "[" << f.get() << "]";
        };

    async(func, f5);
    async(func, f5);

    this_thread::sleep_for(100_ms);

    assert(f5.valid());
}

//////////////////////////////////////////
void case45()
{
    auto func = [](int n, promise<int>& p){
        p.set_value(fab(n));
    };

    promise<int> p;

    thread(func, 10, boost::ref(p)).detach();

    auto f = p.get_future();
    cout << f.get() << endl;

}

//////////////////////////////////////////
void case46()
{
    boost::atomic<int> x;
    barrier br(5);

    auto func = [&](){
        cout << "thread"<< ++x <<" arrived barrier." << endl;
        br.wait();
        cout << "thread run."  << endl;
    };

    thread_group tg;
    for (int i = 0;i < 5;++i)
    {
        tg.create_thread(func);
    }
    tg.join_all();
}

//////////////////////////////////////////

void case47()
{
    thread_specific_ptr<int> pi;

    auto func = [&]{
        pi.reset(new int());

        ++(*pi);
        cout << "thread v=" << *pi <<  endl;
    };
    async(func);
    async(func);

    this_thread::sleep_for(100_ms);
}


//////////////////////////////////////////

int thread2()
{
    cout << "thread v=" << BOOST_THREAD_VERSION << endl;
    case41();
    case42();
    case43();
    case44();
    case45();
    case46();
    case47();
    //case8();
    return 0;
}

