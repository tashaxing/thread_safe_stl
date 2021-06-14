/*
Thread Safe Version STL in C++11
Copyright(c) 2021
Author: tashaxing
*/

#ifndef THREAD_SAFE_BITSET_H_INCLUDED
#define THREAD_SAFE_BITSET_H_INCLUDED

#include <bitset>
#include <mutex>

namespace thread_safe {

template <size_t N>
class bitset {
    template <size_t U> friend thread_safe::bitset<U> operator& (const thread_safe::bitset<U>& lhs, const thread_safe::bitset<U>& rhs);
    template <size_t U> friend thread_safe::bitset<U> operator| (const thread_safe::bitset<U>& lhs, const thread_safe::bitset<U>& rhs);
    template <size_t U> friend thread_safe::bitset<U> operator^ (const thread_safe::bitset<U>& lhs, const thread_safe::bitset<U>& rhs);

    template <class charT, class traits, size_t U> friend std::basic_istream<charT, traits> & operator>> ( std::basic_istream<charT,traits>& is, thread_safe::bitset<U>& rhs);
    template <class charT, class traits, size_t U> friend std::basic_ostream<charT, traits> & operator<< ( std::basic_ostream<charT,traits>& os, const thread_safe::bitset<U>& rhs);
public:
    // Constructors
    bitset( void ) { }
    bitset( unsigned long val ) : storage( val ) { }
    template< class charT, class traits, class Allocator>
    explicit bitset( const std::basic_string<charT, traits,Allocator>& str,
            typename std::basic_string<charT,traits,Allocator>::size_type pos = 0,
            typename std::basic_string<charT,traits,Allocator>::size_type n = std::basic_string<charT,traits,Allocator>::npos ) : storage( str, pos, n ) { }

    // Bit Access
    bool operator[]( size_t pos ) const { std::lock_guard<std::mutex> lock( mutex ); return storage[pos]; }
    bool & operator[]( size_t pos ) { std::lock_guard<std::mutex> lock( mutex ); return storage[pos]; }

    // Bitset operators
    thread_safe::bitset<N> & operator&=( const thread_safe::bitset<N> & rhs ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( rhs.mutex ); storage &= rhs.storage; return *this; }
    thread_safe::bitset<N> & operator|=( const thread_safe::bitset<N> & rhs ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( rhs.mutex ); storage |= rhs.storage; return *this; }
    thread_safe::bitset<N> & operator^=( const thread_safe::bitset<N> & rhs ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( rhs.mutex ); storage ^= rhs.storage; return *this; }
    thread_safe::bitset<N> & operator<<=( const thread_safe::bitset<N> & rhs ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( rhs.mutex ); storage <<= rhs.storage; return *this; }
    thread_safe::bitset<N> & operator>>=( const thread_safe::bitset<N> & rhs ) { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( rhs.mutex ); storage >>= rhs.storage; return *this; }
    thread_safe::bitset<N> operator~( void ) const { std::lock_guard<std::mutex> lock( mutex ); bitset<N> temp( *this ); temp.storage = ~temp.storage; return temp; }
    thread_safe::bitset<N> operator<<( size_t pos ) const { std::lock_guard<std::mutex> lock( mutex ); bitset<N> temp( *this ); temp.storage << pos; return temp; }
    thread_safe::bitset<N> operator>>( size_t pos ) const { std::lock_guard<std::mutex> lock( mutex ); bitset<N> temp( *this ); temp.storage >> pos; return temp; }
    bool operator==( const thread_safe::bitset<N>& rhs ) const { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( rhs.mutex ); return storage == rhs.storage; }
    bool operator!=( const thread_safe::bitset<N>& rhs ) const { std::lock_guard<std::mutex> lock( mutex ); std::lock_guard<std::mutex> lock2( rhs.mutex ); return storage != rhs.storage; }

    // Bit operations
    thread_safe::bitset<N> & set( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.set(); }
    thread_safe::bitset<N> & set( size_t pos, bool val = true ) { std::lock_guard<std::mutex> lock( mutex ); return storage.set( pos, true ); }

    thread_safe::bitset<N> & flip( void ) { std::lock_guard<std::mutex> lock( mutex ); return storage.flip(); }
    thread_safe::bitset<N> & flip( size_t pos ) { std::lock_guard<std::mutex> lock( mutex ); return storage.flip( pos ); }

    // Bitset operations
    unsigned long to_ulong( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.to_ulong(); }

    template < class charT, class traits, class Allocator>
        std::basic_string<charT, traits, Allocator> to_string( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.to_string(); }

    size_t count( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.count(); }

    size_t size( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.size(); }

    bool test( size_t pos ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.test( pos ); }

    bool any( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.any(); }

    bool none( void ) const { std::lock_guard<std::mutex> lock( mutex ); return storage.none(); }

private:
    std::bitset<N> storage;
    mutable std::mutex mutex;
};

template<size_t N>
thread_safe::bitset<N> operator& (const thread_safe::bitset<N>& lhs, const thread_safe::bitset<N>& rhs) {
    std::lock_guard<std::mutex> lock( lhs.mutex );
    std::lock_guard<std::mutex> lock2( rhs.mutex );
    bitset<N> temp;
    temp.storage = lhs.storage & rhs.storage;
    return temp;
}

template<size_t N>
thread_safe::bitset<N> operator| (const thread_safe::bitset<N>& lhs, const thread_safe::bitset<N>& rhs) {
    std::lock_guard<std::mutex> lock( lhs.mutex );
    std::lock_guard<std::mutex> lock2( rhs.mutex );
    bitset<N> temp;
    temp.storage = lhs.storage | rhs.storage;
    return temp;
}

template<size_t N>
thread_safe::bitset<N> operator^ (const thread_safe::bitset<N>& lhs, const thread_safe::bitset<N>& rhs) {
    std::lock_guard<std::mutex> lock( lhs.mutex );
    std::lock_guard<std::mutex> lock2( rhs.mutex );
    bitset<N> temp;
    temp.storage = lhs.storage ^ rhs.storage;
    return temp;
}

template <class charT, class traits, size_t N>
std::basic_istream<charT, traits> & operator>> ( std::basic_istream<charT,traits>& is, thread_safe::bitset<N>& rhs) {
    std::lock_guard<std::mutex> lock2( rhs.mutex );
    return is >> rhs.storage;
}

template <class charT, class traits, size_t N>
std::basic_ostream<charT, traits> & operator<< ( std::basic_ostream<charT,traits>& os, const thread_safe::bitset<N>& rhs) {
    std::lock_guard<std::mutex> lock2( rhs.mutex );
    return os << rhs.storage;
}

}

#endif // THREAD_SAFE_BITSET_H_INCLUDED
