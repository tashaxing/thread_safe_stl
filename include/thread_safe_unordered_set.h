/*
Thread Safe Version STL in C++11
Copyright(c) 2021
Author: tashaxing
*/
#ifndef THREAD_SAFE_UNORDERED_SET_H_INCLUDED
#define THREAD_SAFE_UNORDERED_SET_H_INCLUDED

#include <unordered_set>
#include <mutex>

namespace thread_safe {

    template < class Key>
    class unordered_set {
    public:
        typedef typename std::unordered_set<Key>::iterator iterator;
        typedef typename std::unordered_set<Key>::const_iterator const_iterator;
        typedef typename std::unordered_set<Key>::allocator_type allocator_type;
        typedef typename std::unordered_set<Key>::size_type size_type;

        // Constructors
        unordered_set() = default;
        template <class InputIterator> unordered_set(InputIterator first, InputIterator last) : storage(first, last) { }
        unordered_set(const thread_safe::unordered_set<Key>& x) : storage(x.storage) { }

        // Copy
        thread_safe::unordered_set<Key>& operator=(const thread_safe::unordered_set<Key>& x) { std::lock_guard<std::mutex> lock(mutex); std::lock_guard<std::mutex> lock2(x.mutex); storage = x.storage; return *this; }

        // Destructor
        ~unordered_set(void) { }

        // Iterators
        iterator begin(void) { std::lock_guard<std::mutex> lock(mutex); return storage.begin(); }
        const_iterator begin(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.begin(); }

        iterator end(void) { std::lock_guard<std::mutex> lock(mutex); return storage.end(); }
        const_iterator end(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.end(); }

        // Capacity
        size_type size(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.size(); }

        size_type max_size(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.max_size(); }

        bool empty(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.empty(); }

        void reserve(size_type n) { std::lock_guard<std::mutex> lock(mutex); storage.reserve(n); }

        void rehash(size_type n) { std::lock_guard<std::mutex> lock(mutex); storage.rehash(n); }

        // Modifiers
        std::pair<iterator, bool> insert(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.insert(x); }
        iterator insert(iterator position, const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.insert(position, x); }
        template <class InputIterator> void insert(InputIterator first, InputIterator last) { std::lock_guard<std::mutex> lock(mutex); storage.insert(first, last); }

        void erase(iterator pos) { std::lock_guard<std::mutex> lock(mutex); storage.erase(pos); }
        size_type erase(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.erase(x); }
        void erase(iterator begin, iterator end) { std::lock_guard<std::mutex> lock(mutex); storage.erase(begin, end); }

        void swap(thread_safe::unordered_set<Key>& x) { std::lock_guard<std::mutex> lock(mutex); std::lock_guard<std::mutex> lock2(x.mutex); storage.swap(x.storage); }

        void clear(void) { std::lock_guard<std::mutex> lock(mutex); storage.clear(); }

        // Operations
        const_iterator find(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.find(x); }
        iterator find(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.find(x); }

        size_type count(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.count(x); }

        const_iterator lower_bound(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.lower_bound(x); }
        iterator lower_bound(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.lower_bound(x); }

        const_iterator upper_bound(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.upper_bound(x); }
        iterator upper_bound(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.upper_bound(x); }

        std::pair<const_iterator, const_iterator> equal_range(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.equal_range(x); }
        std::pair<iterator, iterator> equal_range(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.equal_range(x); }

        // Allocator
        allocator_type get_allocator(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.get_allocator(); }

    private:
        std::unordered_set< Key > storage;
        mutable std::mutex mutex;
    };

    template < class Key >
    class unordered_multiset {
    public:
        typedef typename std::unordered_multiset<Key>::iterator iterator;
        typedef typename std::unordered_multiset<Key>::const_iterator const_iterator;
        typedef typename std::unordered_multiset<Key>::allocator_type allocator_type;
        typedef typename std::unordered_multiset<Key>::size_type size_type;

        // Constructors
        unordered_multiset() = default;
        template <class InputIterator>unordered_multiset(InputIterator first, InputIterator last) : storage(first, last) { }
        unordered_multiset(const thread_safe::unordered_multiset<Key>& x) : storage(x.storage) { }

        // Copy
        thread_safe::unordered_multiset<Key>& operator=(const thread_safe::unordered_multiset<Key>& x) { std::lock_guard<std::mutex> lock(mutex); std::lock_guard<std::mutex> lock2(x.mutex); storage = x.storage; return *this; }

        // Destructor
        ~unordered_multiset(void) { }

        // Iterators
        iterator begin(void) { std::lock_guard<std::mutex> lock(mutex); return storage.begin(); }
        const_iterator begin(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.begin(); }

        iterator end(void) { std::lock_guard<std::mutex> lock(mutex); return storage.end(); }
        const_iterator end(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.end(); }

        // Capacity
        size_type size(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.size(); }

        size_type max_size(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.max_size(); }

        bool empty(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.empty(); }

        void reserve(size_type n) { std::lock_guard<std::mutex> lock(mutex); storage.reserve(n); }

        // Modifiers
        std::pair<iterator, bool> insert(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.insert(x); }
        iterator insert(iterator position, const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.insert(position, x); }
        template <class InputIterator> void insert(InputIterator first, InputIterator last) { std::lock_guard<std::mutex> lock(mutex); storage.insert(first, last); }

        void erase(iterator pos) { std::lock_guard<std::mutex> lock(mutex); storage.erase(pos); }
        size_type erase(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.erase(x); }
        void erase(iterator begin, iterator end) { std::lock_guard<std::mutex> lock(mutex); storage.erase(begin, end); }

        void swap(thread_safe::unordered_multiset<Key>& x) { std::lock_guard<std::mutex> lock(mutex); std::lock_guard<std::mutex> lock2(x.mutex); storage.swap(x.storage); }

        void clear(void) { std::lock_guard<std::mutex> lock(mutex); storage.clear(); }

        // Operations
        const_iterator find(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.find(x); }
        iterator find(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.find(x); }

        size_type count(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.count(x); }

        const_iterator lower_bound(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.lower_bound(x); }
        iterator lower_bound(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.lower_bound(x); }

        const_iterator upper_bound(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.upper_bound(x); }
        iterator upper_bound(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.upper_bound(x); }

        std::pair<const_iterator, const_iterator> equal_range(const Key& x) const { std::lock_guard<std::mutex> lock(mutex); return storage.equal_range(x); }
        std::pair<iterator, iterator> equal_range(const Key& x) { std::lock_guard<std::mutex> lock(mutex); return storage.equal_range(x); }

        // Allocator
        allocator_type get_allocator(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.get_allocator(); }

    private:
        std::unordered_multiset< Key > storage;
        mutable std::mutex mutex;
    };

}

#endif // THREAD_SAFE_UNORDERED_SET_H_INCLUDED
