#ifndef THREAD_SAFE_UNORDERED_SET_H_INCLUDED
#define THREAD_SAFE_UNORDERED_SET_H_INCLUDED

#include <unordered_set>
#include <mutex>

namespace thread_safe {

    template < class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class unordered_set {
    public:
        typedef typename std::unordered_set<Key, Compare, Allocator>::iterator iterator;
        typedef typename std::unordered_set<Key, Compare, Allocator>::const_iterator const_iterator;
        typedef typename std::unordered_set<Key, Compare, Allocator>::reverse_iterator reverse_iterator;
        typedef typename std::unordered_set<Key, Compare, Allocator>::const_reverse_iterator const_reverse_iterator;
        typedef typename std::unordered_set<Key, Compare, Allocator>::allocator_type allocator_type;
        typedef typename std::unordered_set<Key, Compare, Allocator>::size_type size_type;
        typedef typename std::unordered_set<Key, Compare, Allocator>::key_compare key_compare;
        typedef typename std::unordered_set<Key, Compare, Allocator>::value_compare value_compare;

        // Constructors
        explicit unordered_set(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : storage(comp, alloc) { }
        template <class InputIterator> unordered_set(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : storage(first, last, comp, alloc) { }
        unordered_set(const thread_safe::unordered_set<Key, Compare, Allocator>& x) : storage(x.storage) { }

        // Copy
        thread_safe::unordered_set<Key, Compare, Allocator>& operator=(const thread_safe::unordered_set<Key, Compare, Allocator>& x) { std::lock_guard<std::mutex> lock(mutex); std::lock_guard<std::mutex> lock2(x.mutex); storage = x.storage; return *this; }

        // Destructor
        ~unordered_set(void) { }

        // Iterators
        iterator begin(void) { std::lock_guard<std::mutex> lock(mutex); return storage.begin(); }
        const_iterator begin(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.begin(); }

        iterator end(void) { std::lock_guard<std::mutex> lock(mutex); return storage.end(); }
        const_iterator end(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.end(); }

        reverse_iterator rbegin(void) { std::lock_guard<std::mutex> lock(mutex); return storage.rbegin(); }
        const_reverse_iterator rbegin(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.rbegin(); }

        reverse_iterator rend(void) { std::lock_guard<std::mutex> lock(mutex); return storage.rend(); }
        const_reverse_iterator rend(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.rend(); }

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

        void swap(thread_safe::unordered_set<Key, Compare, Allocator>& x) { std::lock_guard<std::mutex> lock(mutex); std::lock_guard<std::mutex> lock2(x.mutex); storage.swap(x.storage); }

        void clear(void) { std::lock_guard<std::mutex> lock(mutex); storage.clear(); }

        // Observers
        key_compare key_comp(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.key_comp(); }
        value_compare value_comp(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.value_comp(); }

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
        std::unordered_set< Key, Compare, Allocator > storage;
        mutable std::mutex mutex;
    };

    template < class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class unordered_multiset {
    public:
        typedef typename std::unordered_multiset<Key, Compare, Allocator>::iterator iterator;
        typedef typename std::unordered_multiset<Key, Compare, Allocator>::const_iterator const_iterator;
        typedef typename std::unordered_multiset<Key, Compare, Allocator>::reverse_iterator reverse_iterator;
        typedef typename std::unordered_multiset<Key, Compare, Allocator>::const_reverse_iterator const_reverse_iterator;
        typedef typename std::unordered_multiset<Key, Compare, Allocator>::allocator_type allocator_type;
        typedef typename std::unordered_multiset<Key, Compare, Allocator>::size_type size_type;
        typedef typename std::unordered_multiset<Key, Compare, Allocator>::key_compare key_compare;
        typedef typename std::unordered_multiset<Key, Compare, Allocator>::value_compare value_compare;

        // Constructors
        explicit unordered_multiset(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : storage(comp, alloc) { }
        template <class InputIterator>unordered_multiset(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : storage(first, last, comp, alloc) { }
        unordered_multiset(const thread_safe::unordered_multiset<Key, Compare, Allocator>& x) : storage(x.storage) { }

        // Copy
        thread_safe::unordered_multiset<Key, Compare, Allocator>& operator=(const thread_safe::unordered_multiset<Key, Compare, Allocator>& x) { std::lock_guard<std::mutex> lock(mutex); std::lock_guard<std::mutex> lock2(x.mutex); storage = x.storage; return *this; }

        // Destructor
        ~unordered_multiset(void) { }

        // Iterators
        iterator begin(void) { std::lock_guard<std::mutex> lock(mutex); return storage.begin(); }
        const_iterator begin(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.begin(); }

        iterator end(void) { std::lock_guard<std::mutex> lock(mutex); return storage.end(); }
        const_iterator end(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.end(); }

        reverse_iterator rbegin(void) { std::lock_guard<std::mutex> lock(mutex); return storage.rbegin(); }
        const_reverse_iterator rbegin(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.rbegin(); }

        reverse_iterator rend(void) { std::lock_guard<std::mutex> lock(mutex); return storage.rend(); }
        const_reverse_iterator rend(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.rend(); }

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

        void swap(thread_safe::unordered_multiset<Key, Compare, Allocator>& x) { std::lock_guard<std::mutex> lock(mutex); std::lock_guard<std::mutex> lock2(x.mutex); storage.swap(x.storage); }

        void clear(void) { std::lock_guard<std::mutex> lock(mutex); storage.clear(); }

        // Observers
        key_compare key_comp(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.key_comp(); }
        value_compare value_comp(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.value_comp(); }

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
        std::unordered_multiset< Key, Compare, Allocator > storage;
        mutable std::mutex mutex;
    };

}

#endif // THREAD_SAFE_UNORDERED_SET_H_INCLUDED
