#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <algorithm>
#include <unordered_map>



template <class T, class U>
class Heap
{
    private:

        std::vector<T>  _v;
        size_t          _size;
        
        using Serializer = U (*)(const T&);
        Serializer  _serialize;
        std::unordered_map<U, size_t> _indexes;

        void    _heapify_up(size_t idx);
        void    _heapify_down(size_t idx);
        void    _makeHeap();

        size_t  _minChild(size_t idx);

    public:

        Heap(Serializer pt);
        template <typename InputIterator, typename = typename std::enable_if<
        std::is_convertible<typename std::iterator_traits<InputIterator>::value_type, T>::value
            >::type>
        Heap(InputIterator first, InputIterator last, Serializer pt);
        Heap(const Heap &other);
        ~Heap();
        Heap<T, U> &operator=(Heap<T, U> const &rhs);
        void    modify(size_t idx, T &new_value);

        size_t  getSize() const;
        const T       &operator[](size_t idx) const;
        void    printHeap() const;
        void    printIndexes() const;


        void    insert(const T &new_value);
        
        const T &peekHead() const;
        T       popHead();

        bool    getIndex(const U& serial_value, size_t &idx);

};

#endif