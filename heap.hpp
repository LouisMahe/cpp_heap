#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <algorithm>

template <class T>
class Heap
{
    private:

        std::vector<T>  _v;
        size_t          _size;

        void    _heapify_up(size_t idx);
        void    _heapify_down(size_t idx);
        void    _makeHeap();

        size_t  _minChild(size_t idx);

    public:

        Heap();
        template <typename InputIterator, typename = typename std::enable_if<
        std::is_convertible<typename std::iterator_traits<InputIterator>::value_type, T>::value
            >::type>
        Heap(InputIterator first, InputIterator last);
        Heap(const Heap &other);
        ~Heap();
        Heap<T> &operator=(Heap<T> const &rhs);
        void    modify(size_t idx, T &new_value);

        size_t  getSize() const;
        const T       &operator[](size_t idx) const;
        void    printHeap() const;


        void    insert(const T &new_value);
        
        const T &peekHead() const;
        T       popHead();


     

};




#endif