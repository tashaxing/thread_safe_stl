/*
Thread Safe Version STL in C++11
Copyright(c) 2021
Author: tashaxing
*/
#ifndef THREAD_SAFE_LIST_H_INCLUDED
#define THREAD_SAFE_LIST_H_INCLUDED

#include <list>
#include <mutex>

namespace thread_safe {

template < class T, class Allocator = std::allocator<T> >
class list {
public:
    typedef typename std::list<T, Allocator>::iterator iterator;
    typedef typename std::list<T, Allocator>::const_iterator const_iterator;
    typedef typename std::list<T, Allocator>::reverse_iterator reverse_iterator;
    typedef typename std::list<T, Allocator>::const_reverse_iterator const_reverse_iterator;
    typedef typename std::list<T, Allocator>::allocator_type allocator_type;
    typedef typename std::list<T, Allocator>::value_type value_type;
    typedef typename std::list<T, Allocator>::size_type size_type;
    typedef typename std::list<T, Allocator>::difference_type difference_type;

    // Constructor
    explicit list( const Allocator & alloc = Allocator() ) : storage( alloc ) { }
    explicit list( size_type n, const T & value = T(), const Allocator & alloc = Allocator() ) : storage( n, value, alloc ) { }
    template <class InputIterator> list( InputIterator first, InputIterator last, const Allocator & alloc = Allocator() ) : storage( first, last, alloc ) { }
    list( const thread_safe::list<T, Allocator> & x ) { std::lock_guard<std::mutex> lock( x.mutex ); storage = x.storage; }

    // Copy
    thread_safe::list<T,Allocator>& operator=( const thread_safe::list<T,Allocator>& x ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( x.mutex ); storage = x.storage; return *this;}

    // Destructor
    ~list<T,Allocator>( void ) { }

    // Iterators
    iterator begin( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.begin(); }
    const_iterator begin( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.begin(); }

    iterator end( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.end(); }
    const_iterator end( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.end(); }

    const_iterator cbegin() const { std::lock_guard<std::mutex> lock(mutex); return storage.cbegin(); }
    const_iterator cend() const { std::lock_guard<std::mutex> lock(mutex); return storage.cend(); }

    reverse_iterator rbegin( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.rbegin(); }
    const_reverse_iterator rbegin( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.rbegin(); }

    reverse_iterator rend( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.rend(); }
    const_reverse_iterator rend( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.rend(); }

    // Capacity
    size_type size( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.size(); }

    size_type max_size( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.max_size(); }

    void resize( size_type n, T c = T() ) { std::lock_guard<std::mutex> lock( mutex ); storage.resize( n, c ); }

    bool empty( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.empty(); }

    // Element access
    T & front( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.front(); }
    const T & front( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.back(); }

    T & back( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.back(); }
    const T & back( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.back(); }

    // Modifiers
    void assign( size_type n, T & u ) { std::lock_guard<std::mutex> lock( mutex ); storage.assign( n, u ); }
    template <class InputIterator> void assign( InputIterator begin, InputIterator end ) { std::lock_guard<std::mutex> lock( mutex ); storage.assign( begin, end ); }

    void emplace_back( const T& u ) { std::lock_guard<std::mutex> lock(mutex); storage.emplace_back(u); }

    void push_back( const T & u ) { std::lock_guard<std::mutex> lock( mutex ); storage.push_back( u ); }

    void pop_back( void ) { std::lock_guard<std::mutex> lock( mutex ); storage.pop_back(); }

    void emplace_front(const T& u) { std::lock_guard<std::mutex> lock(mutex); storage.emplace_front(u); }

    void push_front( const T & u ) { std::lock_guard<std::mutex> lock( mutex ); storage.push_front( u ); }

    void pop_front( void ) { std::lock_guard<std::mutex> lock( mutex ); storage.pop_front(); }

    iterator insert( iterator pos, const T & u ) { std::lock_guard<std::mutex> lock( mutex ); return storage.insert( pos, u ); }
    void insert( iterator pos, size_type n, const T & u ) { std::lock_guard<std::mutex> lock( mutex ); storage.insert( pos, n, u ); }
    template <class InputIterator> void insert( iterator pos, InputIterator begin, InputIterator end ) { std::lock_guard<std::mutex> lock( mutex ); storage.insert( pos, begin, end ); }

    void erase( iterator pos ) { std::lock_guard<std::mutex> lock( mutex ); storage.erase( pos ); }
    void erase( iterator begin, iterator end ) { std::lock_guard<std::mutex> lock( mutex ); storage.erase( begin, end ); }

    void swap( thread_safe::list<T, Allocator> & x ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( x.mutex ); storage.swap( x.storage ); }

    void clear( void ) { std::lock_guard<std::mutex> lock( mutex ); storage.clear(); }

    // Operations
    void splice ( iterator position, thread_safe::list<T,Allocator>& x ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( x.mutex ); storage.splice( position, x.storage ); }
    void splice ( iterator position, thread_safe::list<T,Allocator>& x, iterator i ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( x.mutex ); storage.splice( position, x.storage, i ); }
    void splice ( iterator position, thread_safe::list<T,Allocator>& x, iterator first, iterator last ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( x.mutex ); storage.splice( position, x.storage, first, last ); }

    void remove ( const T& value ) { std::lock_guard<std::mutex> lock( mutex ); storage.remove( value ); }

    template <class Predicate> void remove_if ( Predicate pred ) { std::lock_guard<std::mutex> lock( mutex ); storage.remove_if( pred ); }

    void unique ( void ) { std::lock_guard<std::mutex> lock( mutex ); storage.unique(); }
    template <class BinaryPredicate> void unique ( BinaryPredicate binary_pred ) { std::lock_guard<std::mutex> lock( mutex ); storage.unique( binary_pred ); }

    void merge ( thread_safe::list<T,Allocator>& x ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( x.mutex ); storage.merge( x.storage() ); }
    template <class Compare> void merge ( thread_safe::list<T,Allocator>& x, Compare comp ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( x.mutex ); storage.merge( x.storage, comp ); }

    void sort ( void ) { std::lock_guard<std::mutex> lock( mutex ); storage.sort(); }
    template <class Compare> void sort ( Compare comp ) { std::lock_guard<std::mutex> lock( mutex ); storage.sort( comp ); }

    void reverse( void ) { std::lock_guard<std::mutex> lock( mutex ); }

    // Allocator
    allocator_type get_allocator( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.get_allocator(); }

private:
    std::list<T, Allocator> storage;
    mutable std::mutex mutex;
};

}

#endif // THREAD_SAFE_LIST_H_INCLUDED
