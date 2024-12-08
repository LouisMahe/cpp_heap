#include "heap.hpp"
#include "iostream"

template <class T, class U>
Heap<T, U>::Heap(Serializer pt) : _v(), _size(0), _serialize(pt), _indexes()
{}

template <class T, class U>
template <typename InputIterator, typename>
Heap<T, U>::Heap(InputIterator first, InputIterator last, Serializer pt) : _v(), _size(), _serialize(pt), _indexes()
{
    _v.insert(_v.begin(), first, last);
    _size = _v.size();
    std::cout << this->_size << std::endl;
    this->_makeHeap();
    for (size_t i = 0; i < this->_size; i++)
    {
        _indexes[_serialize(_v[i])] = i;
    }
}

template<class T, class U>
Heap<T, U>::Heap(const Heap<T, U> &other): _v(other._v), _size(other._size), _serialize(other._serialize), _indexes(other._indexes)
{}

template<class T, class U>
Heap<T, U>::~Heap()
{}

template<class T, class U>
Heap<T, U> &Heap<T, U>::operator=(Heap<T, U> const &rhs)
{
    if (this == &rhs)
        return *this;
    this->_v = rhs._v;
    this->_size = this->_v.size();
    this->_serialize = rhs._serialize;
    this->_indexes = rhs._indexes;
    return (*this);
}

template<class T, class U>
void    Heap<T, U>::printHeap() const
{
    for (auto it:this->_v)
    {
        std::cout << it << ", ";
    }
    std::cout << std::endl;
}


template<class T, class U>
const T   &Heap<T, U>::operator[](size_t idx) const
{
    return (this->_v[idx]);
}

template<class T, class U>
void    Heap<T, U>::_heapify_up(size_t idx)
{
    while(idx > 0)
    {
        if (this->_v[idx] < this->_v[(idx-1)/2])
        {
            _indexes[_serialize(_v[idx])] = (idx - 1)/2;
            _indexes[_serialize[_v[(idx-1)/2]]] = idx;
            std::swap(this->_v[idx], this->_v[(idx-1)/2]);
            idx = (idx-1)/2;
        }
        else
        {
            break;
        }
    }
}

template<class T, class U>
size_t  Heap<T, U>::_minChild(size_t idx)
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

template<class T, class U>
void    Heap<T, U>::_heapify_down(size_t idx)
{
    size_t  minc = this->_minChild(idx);
    if (this->_v[idx] > this->_v[minc])
    {
        _indexes[_serialize(_v[idx])] = minc;
        _indexes[_serialize(_v[minc])] = idx;
        
        std::swap(this->_v[idx], this->_v[minc]);
        this->_heapify_down(minc);
    }
}



template<class T, class U>
void    Heap<T, U>::_makeHeap()
{
    if (this->_size < 2)
        return;
    for (size_t i = ((this->_size - 1)/2); i>0; i--)
    {
        this->_heapify_down(i);
    }
    this->_heapify_down(0);
}


template<class T, class U>
void    Heap<T, U>::insert(const T &new_value)
{
    _indexes[_serialize(new_value)] = this->_size;
    this->_v.push_back(new_value);
    this->_size += 1;
    this->_heapify_up(this->_size-1);
}

template<class T, class U>
const T &Heap<T, U>::peekHead() const
{
   return (this->_v[0]);
}

template<class T, class U>
T   Heap<T, U>::popHead()
{
    if (this->_size > 1)
    {
        _indexes.erase(_serialize(_v[0]));
        _indexes[_serialize(_v[this->_size-1])] = 0;
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

//  Should the map erase the old value and create a new one ?
// if the serialisation of T is not changed it is not necessary
template<class T, class U>
void    Heap<T, U>::modify(size_t idx, T &new_value)
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

template<class T, class U>
void    Heap<T, U>::printIndexes() const
{
    for(auto it = _indexes.begin(); it != _indexes.end(); ++it)
    {
        std::cout << "Key: " << it->first << " ,index: " << it->second << std::endl;
    }
}


template<class T, class U>
bool    Heap<T, U>::getIndex(const U &serial_value, size_t &idx)
{
    
    if (auto search = _indexes.find(serial_value); search != _indexes.end())
    {
        idx = search->second;
        return (true);
    }
    return (false);

}