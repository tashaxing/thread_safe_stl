/*
Thread Safe Version STL in C++11
Copyright(c) 2021
Author: tashaxing
*/
#ifndef THREAD_SAFE_STACK_H_INCLUDED
#define THREAD_SAFE_STACK_H_INCLUDED

#include <stack>
#include <mutex>

namespace thread_safe {

template < class T, class Container = std::stack<T> >
class stack {
public:
    explicit stack( const Container & ctnr = Container() ) : storage( ctnr ) { }
    bool empty( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.empty(); }

    size_t size( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.size(); }

    T & top( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.top(); }
    const T & top( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.top(); }

    void push( const T & u ) { std::lock_guard<std::mutex> lock( mutex ); storage.push( u ); }

    void pop( void ) { std::lock_guard<std::mutex> lock( mutex ); storage.pop(); }
private:
    Container storage;
    mutable std::mutex mutex;
};

}

#endif // THREAD_SAFE_STACK_H_INCLUDED
