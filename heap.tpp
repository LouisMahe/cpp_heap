#include "heap.hpp"
#include "iostream"

template <class T>
Heap<T>::Heap() : _v(), _size(0)
{}

template <class T>
template <typename InputIterator, typename>
Heap<T>::Heap(InputIterator first, InputIterator last) : _v()
{
    _v.insert(_v.begin(), first, last);
    _size = _v.size();
    std::cout << this->_size << std::endl;
    this->_makeHeap();
}

template<class T>
Heap<T>::Heap(const Heap<T> &other): _v(other._v), _size(other._size)
{}

template<class T>
Heap<T>::~Heap()
{}

template<class T>
Heap<T> &Heap<T>::operator=(Heap<T> const &rhs)
{
    if (this == &rhs)
        return *this;
    this->_v = rhs._v;
    this->_size = this->_v.size();
    return (*this);
}

template<class T>
void    Heap<T>::printHeap() const
{
    for (auto it:this->_v)
    {
        std::cout << it << ", ";
    }
    std::cout << std::endl;
}


template<class T>
const T   &Heap<T>::operator[](size_t idx) const
{
    return (this->_v[idx]);
}

template<class T>
void    Heap<T>::_heapify_up(size_t idx)
{
    while(idx > 0)
    {
        if (this->_v[idx] < this->_v[(idx-1)/2])
        {
            std::swap(this->_v[idx], this->_v[(idx-1)/2]);
            idx = (idx-1)/2;
        }
        else
        {
            break;
        }
    }
}

template<class T>
size_t  Heap<T>::_minChild(size_t idx)
{
    size_t  left = 2*idx + 1;
    size_t  right = 2*idx + 2;
    
    if (left > this->_size-1)
        return (idx);
    else if (right > this->_size-1)
        return (left);
    else
    {
        return ((this->_v[left] > this->_v[right]) ? right : left);
    }
}

template<class T>
void    Heap<T>::_heapify_down(size_t idx)
{
    std::cout << "heap down " << idx << std::endl;
    size_t  minc = this->_minChild(idx);
    if (this->_v[idx] > this->_v[minc])
    {
        std::swap(this->_v[idx], this->_v[minc]);
        this->_heapify_down(minc);
    }
}



template<class T>
void    Heap<T>::_makeHeap()
{
    if (this->_size < 2)
        return;
    for (size_t i = ((this->_size - 1)/2); i>0; i--)
    {
        this->_heapify_down(i);
    }
    this->_heapify_down(0);
}


template<class T>
void    Heap<T>::insert(const T &new_value)
{
    this->_v.push_back(new_value);
    this->_size += 1;
    this->_heapify_up(this->_size-1);
}

template<class T>
const T &Heap<T>::peekHead() const
{
   return (this->_v[0]);
}

template<class T>
T   Heap<T>::popHead()
{
    if (this->_size > 1)
    {
        std::swap(this->_v[0], this->_v[this->_size-1]);
        T    head = this->_v.back();
        this->_v.pop_back();
        this->_size--;
        this->_heapify_down(0);
        return (head);
    }
    else
    {
        T    head = this->_v.back();
        this->_v.pop_back();
        this->_size = 0;
        return (head);
    }
}


template<class T>
void    Heap<T>::modify(size_t idx, T &new_value)
{
    if (this->_v[idx] > new_value)
    {
        this->_v[idx] = new_value;
        this->_heapify_up(idx);
    }
    else{
        this->_v[idx] = new_value;
        this->_heapify_down(idx);
    }
}