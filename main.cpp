#include <iostream>
#include<boost/timer.hpp>
#include <vector>
template<typename T>
class Vec_iterator
{
private:
    using iter_point = T*;
    using con_iter_point = const T*;
    using iter_obj_type = T;
    iter_point _save_ptr;
public:
    Vec_iterator(iter_point _ptr):_save_ptr(_ptr)
    {

    }
public:
    Vec_iterator& operator++()
    {
        _save_ptr++;
        return *this;
    }
    Vec_iterator& operator--()
    {
        _save_ptr--;
        return *this;
    }
    iter_obj_type& operator*()
    {
        return *_save_ptr;
    }
    bool operator!=(const Vec_iterator& c)
    {
        return _save_ptr!=c._save_ptr;
    }
};
template<typename T>
class Vec
{
private:
    using ele_type = T;
    using ele_point = T*;
    using con_ele_point = const T*;
    using iterator = Vec_iterator<T>;
    const std::size_t ele_size = sizeof(T);
    const std::size_t add_size = 2800;
    ele_point _now_ptr = nullptr;
    ele_point begin_ptr = nullptr;
    con_ele_point _con_now_ptr = nullptr;
    std::size_t _size = 0;
    std::size_t max_size = 0;
public:
    using size_type = T;
public:
    Vec()
    {
    }
private:
    void check_init()
    {
        if(_size==0)
        {
            _now_ptr = (ele_point)malloc(ele_size*add_size);
            _con_now_ptr = _now_ptr;
            begin_ptr = _now_ptr;
            max_size = add_size;
        }
    }
public:
    void push_back(const T& value)
    {
        check_init();
        ++_size;
        if(_size>max_size)
        {
            max_size = _size+add_size;
            ele_point tmp_ptr = (ele_point)malloc(ele_size*max_size);
            for(std::size_t index=0;index<_size;index++)
            {
                new(tmp_ptr+index) ele_type(begin_ptr[index]);
            }
            free(begin_ptr);
            _now_ptr = tmp_ptr+_size-1;
            begin_ptr = tmp_ptr;
        }
        new(_now_ptr) ele_type(value);
        ++_now_ptr;
    }
    template<typename...Args>
    void emplace_back(Args...args)
    {
        check_init();
        ++_size;
        if(_size>max_size)
        {
            max_size = _size+add_size;
            ele_point tmp_ptr = (ele_point)malloc(ele_size*max_size);
            for(std::size_t index=0;index<_size;index++)
            {
                new(tmp_ptr+index) ele_type(begin_ptr[index]);
            }
            free(begin_ptr);
            _now_ptr = tmp_ptr+_size-1;
            begin_ptr = tmp_ptr;
        }
        new(_now_ptr) ele_type(args...);
        ++_now_ptr;
    }
    T& operator[](std::size_t n)
    {
       return begin_ptr[n];
    }
    std::size_t size() const
    {
        return _size;
    }
public:
    iterator begin()
    {
        return iterator(begin_ptr);
    }
    iterator end()
    {

        return begin_ptr== nullptr? iterator(nullptr):iterator(begin_ptr+_size);
    }
};
class test
{
public:
    test(int _i,float _f):a(_i),f(_f)
    {

    }
public:
    int a;
    float f;
};
int main()
{
    boost::timer t;
    Vec<int> v;
    for(int b=0;b<50;b++)
    {
        v.push_back(b);
    }
    for(int c=50;c<10000;c++)
    {
        v.push_back(c);
    }
    for(auto &iter:v)
    {
//        std::cout<<iter<<std::endl;
    }
    std::cout<<t.elapsed()<<std::endl;
    t.restart();
    std::vector<int> v2;
    for(int b=0;b<50;b++)
    {
        v2.push_back(b);
    }
    for(int c=50;c<10000;c++)
    {
        v2.push_back(c);
    }
    for(auto &iter:v2)
    {
//        std::cout<<iter<<std::endl;
    }
    std::cout<<t.elapsed()<<std::endl;
    return 0;
}