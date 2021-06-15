/*
Thread Safe Version STL in C++11
Copyright(c) 2021
Author: tashaxing
*/
#ifndef THREAD_SAFE_QUEUE_INCLUDED
#define THREAD_SAFE_QUEUE_INCLUDED

#include <queue>
#include <vector>
#include <deque>
#include <mutex>

namespace thread_safe {

template < class T, class Container = std::deque<T> >
class queue {
public:
    explicit queue( const Container & ctnr = Container() ) : storage( ctnr ) { }
    bool empty( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.empty(); }

    size_t size( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.size(); }

    T & back( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.back(); }
    const T & back( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.back(); }

    T & front( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.front(); }
    const T & front( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.front(); }

    void push( const T & u ) { std::lock_guard<std::mutex> lock( mutex ); storage.push( u ); }

    void pop( void ) { std::lock_guard<std::mutex> lock( mutex ); storage.pop(); }
private:
    std::queue<T, Container> storage;
    mutable std::mutex mutex;
};

template < class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> >
class priority_queue {
public:
    explicit priority_queue ( const Compare& x = Compare(), const Container& y = Container() ) : storage( x, y ) { }
    template <class InputIterator> priority_queue ( InputIterator first, InputIterator last, const Compare& x = Compare(), const Container& y = Container() ) : storage( first, last, x, y ) { }

    bool empty( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.empty(); }

    size_t size( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.size(); }

    const T & top( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.top(); }

    void push( const T & u ) { std::lock_guard<std::mutex> lock( mutex ); storage.push(u); }

    void pop( void ) { std::lock_guard<std::mutex> lock( mutex ); storage.pop(); }
private:
    std::priority_queue< T, Container, Compare > storage;
    mutable std::mutex mutex;
};

}

#endif // THREAD_SAFE_QUEUE_INCLUDED
