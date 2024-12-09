#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>



template <class T, class U>
class Heap
{
    private:

        std::vector<T>  _v;
        size_t          _size;

        using compFunc = bool(*)(const T&, const T&);
        compFunc    _cp;

        using Serializer = U (*)(const T&);
        Serializer  _serialize;
        std::map<U, size_t> _indexes;

        void    _heapify_up(size_t idx);
        void    _heapify_down(size_t idx);
        void    _makeHeap();

        size_t  _minChild(size_t idx);

    public:

        Heap(Serializer pt, compFunc t_comp);
        template <typename InputIterator, typename = typename std::enable_if<
        std::is_convertible<typename std::iterator_traits<InputIterator>::value_type, T>::value
            >::type>
        Heap(InputIterator first, InputIterator last, Serializer pt, compFunc t_comp);
        Heap(const Heap &other);
        ~Heap();
        Heap<T, U> &operator=(Heap<T, U> const &rhs);
        using changeValue = void (*)(T old_value, T new_value);
        void    modify(size_t idx, T &new_value, changeValue swapper);

        size_t  getSize() const;
        const T       &operator[](size_t idx) const;
        void    printHeap() const;
        void    printIndexes() const;


        void    insert(const T &new_value);
        using freeT = void (*)(T&);
        void    deleteVec(freeT cleanVec);
        const T &peekHead() const;
        T       popHead();

        bool    getIndex(const U& serial_value, size_t &idx);

};

#endif


// TODO modify modify
